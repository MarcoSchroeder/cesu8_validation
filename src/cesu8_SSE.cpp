#include "cesu8.hpp"
#include "cesu8_common.hpp"

#include <immintrin.h>

#include <cstdint>

using namespace cesu8::impl;

namespace cesu8 {

static __m128i extract_high_nibbles(__m128i a)
{
    __m128i low_nibble_mask = _mm_set1_epi8(0x0F);
    __m128i a_shifted       = _mm_srli_epi16(a, 4);
    __m128i high_nibbles    = _mm_and_si128(a_shifted, low_nibble_mask);
    return high_nibbles;
}

static __m128i extract_low_nibbles(__m128i a)
{
    __m128i low_nibble_mask = _mm_set1_epi8(0x0F);
    __m128i low_nibbles     = _mm_and_si128(a, low_nibble_mask);
    return low_nibbles;
}

bool is_valid_cesu8_SSE(byte const* str, std::size_t len)
{
    // clang-format off
    static __m128i const table3 = _mm_setr_epi8(
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, // 0|xxx'xxxx (C1)
        0x3C, 0x3C, 0x3C, 0x3C,                         // 10|xx'xxxx (CB)
        0x33, 0x33,                                     // 110|x'xxxx (C2)
        0x33,                                           // 1110|'xxxx (C3)
        0x0                                             // 1111'xxxx (Illegal header)
    );
    static __m128i const table2 = _mm_setr_epi8(
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, // 0|xxx'xxxx (C1)
        0x3A, 0x3A, 0x9A, 0x5A,                         // 10|xx'xxxx (CB)
        0x11, 0x11,                                     // 110|x'xxxx (C2)
        0x11,                                           // 1110|'xxxx (C3)
        0x0                                             // 1111'xxxx (Illegal header)
    );
    static __m128i const table1_hi = _mm_setr_epi8(
        0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5,
        0xD, 0xD, 0xD, 0xD,
        0x1D, 0xD,
        0xE7,
        0x0
    );
    static __m128i const table1_lo = _mm_setr_epi8(
        0x3F, 0x1F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
        0x0F, 0x0F, 0x0F, 0x0F,
        0x0F, 0xCF,
        0x0F,
        0x0F
    );
    // clang-format on

    __m128i prev_bytes         = _mm_setzero_si128();
    __m128i has_error          = _mm_setzero_si128();
    __m128i prev_hi_surrogates = _mm_setzero_si128();
    while (len >= 16) {
        // Load next bytes
        __m128i bytes3 = _mm_loadu_si128(reinterpret_cast<__m128i const*>(str));
        __m128i bytes2 = _mm_alignr_epi8(bytes3, prev_bytes, 15);
        __m128i bytes1 = _mm_alignr_epi8(bytes3, prev_bytes, 14);

        // Extract header bits
        __m128i nibbles3    = extract_high_nibbles(bytes3);
        __m128i nibbles2    = extract_high_nibbles(bytes2);
        __m128i nibbles1_lo = extract_low_nibbles(bytes1);
        __m128i nibbles1_hi = extract_high_nibbles(bytes1);

        // Table lookup
        __m128i result3    = _mm_shuffle_epi8(table3, nibbles3);
        __m128i result2    = _mm_shuffle_epi8(table2, nibbles2);
        __m128i result1_lo = _mm_shuffle_epi8(table1_lo, nibbles1_lo);
        __m128i result1_hi = _mm_shuffle_epi8(table1_hi, nibbles1_hi);

        // Detect error conditions A) Too short, B) Too long, D) Overlong
        __m128i temp = _mm_and_si128(result2, _mm_and_si128(result1_hi, result1_lo));
        __m128i errors_abd = _mm_and_si128(temp, result3);

        // Detect error condition E) Incomplete surrogate
        __m128i hi_surrogates = _mm_and_si128(temp, _mm_set1_epi8(0x80));
        __m128i lo_surrogates = _mm_and_si128(temp, _mm_set1_epi8(0x40));
        lo_surrogates         = _mm_slli_epi16(lo_surrogates, 1);
        __m128i shifted_hi_surrogates =
            _mm_alignr_epi8(hi_surrogates, prev_hi_surrogates, 13);
        __m128i errors_e = _mm_xor_si128(shifted_hi_surrogates, lo_surrogates);

        // Detect error condition C) Illegal header
        __m128i errors_c = _mm_cmpeq_epi8(_mm_set1_epi8(0xF), nibbles3);

        // Store error conditions
        has_error = _mm_or_si128(has_error, errors_abd);
        has_error = _mm_or_si128(has_error, errors_c);
        has_error = _mm_or_si128(has_error, errors_e);

        // Setup next iteration
        prev_hi_surrogates = hi_surrogates;
        prev_bytes         = bytes3;
        str += 16;
        len -= 16;
    }

    if (!_mm_testz_si128(has_error, has_error)) {
        return false;
    }

    /*
    The SSE validation iterates the string with a step size of 16. Remaining bytes have to be validated using
    the non-SIMD algorithm. The last bytes processed by the SSE validation may contain the start of a multi-byte
    code point which extends into the remaining bytes. The non-SIMD algorithm can not start validation in the middle
    of a code point, so str/len must potentially be adjusted to the last completly validated code point
    */

    // Value error must not be considered only structural as we start revalidation anyways
    uint32_t hi_surrogates = _mm_movemask_epi8(prev_hi_surrogates);
    hi_surrogates &= 0xE000; // extract 3 msbs
    size_t offset = 0;
    if (hi_surrogates == (1u << 13)) {
        offset = 5;
    }
    else if (hi_surrogates == (1u << 14)) {
        offset = 4;
    }
    else if (hi_surrogates == (1u << 15)) {
        offset = 3;
    }
    else if (is_c3(str[-2])) { // Checks surrogate pair as well
        offset = 2;
    }
    else if ((str[-1] & 0xC0) == 0xC0) { // Checks 2 and 3 byte header
        offset = 1;
    }
    return is_valid_cesu8_scalar(str - offset, len + offset);
}

} // namespace cesu8
