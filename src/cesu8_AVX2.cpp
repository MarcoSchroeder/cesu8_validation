#include "simd_hguards.hpp"

#include "cesu8.hpp"
#include "cesu8_common.hpp"

#include <immintrin.h>

#include <cstdint>

#ifdef CESU8_VALIDATION_AVX_IMPLEMENTATION

using namespace cesu8::impl;

namespace cesu8 {

static __m256i extract_high_nibbles(__m256i a)
{
    __m256i low_nibble_mask = _mm256_set1_epi8(0x0F);
    __m256i a_shifted       = _mm256_srli_epi16(a, 4);
    __m256i high_nibbles    = _mm256_and_si256(a_shifted, low_nibble_mask);
    return high_nibbles;
}

template<std::uint8_t nr_bytes>
static __m256i shift_right_bytewise(__m256i shift, __m256i insert)
{
    __m256i permuted = _mm256_permute2x128_si256(insert, shift, 0x21);
    __m256i shifted  = _mm256_alignr_epi8(shift, permuted, 16 - nr_bytes);
    return shifted;
}

bool is_valid_cesu8_AVX2(byte const* str, std::size_t len)
{
    // clang-format off
    static __m256i const table3 = _mm256_setr_epi8(
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, // 0|xxx'xxxx (C1)
        0x3C, 0x3C, 0x3C, 0x3C,                         // 10|xx'xxxx (CB)
        0x33, 0x33,                                     // 110|x'xxxx (C2)
        0x33,                                           // 1110|'xxxx (C3)
        0x0,                                            // 1111'xxxx (Illegal header)
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, // 0|xxx'xxxx (C1)
        0x3C, 0x3C, 0x3C, 0x3C,                         // 10|xx'xxxx (CB)
        0x33, 0x33,                                     // 110|x'xxxx (C2)
        0x33,                                           // 1110|'xxxx (C3)
        0x0                                             // 1111'xxxx (Illegal header)
    );
    static __m256i const table2 = _mm256_setr_epi8(
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, // 0|xxx'xxxx (C1)
        0x3A, 0x3A, 0x9A, 0x5A,                         // 10|xx'xxxx (CB)
        0x11, 0x11,                                     // 110|x'xxxx (C2)
        0x11,                                           // 1110|'xxxx (C3)
        0x0,                                            // 1111'xxxx (Illegal header)
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, // 0|xxx'xxxx (C1)
        0x3A, 0x3A, 0x9A, 0x5A,                         // 10|xx'xxxx (CB)
        0x11, 0x11,                                     // 110|x'xxxx (C2)
        0x11,                                           // 1110|'xxxx (C3)
        0x0                                             // 1111'xxxx (Illegal header)
    );
    static __m256i const table1_hi = _mm256_setr_epi8(
        0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5,         // 0|xxx'xxxx (C1)
        0xD, 0xD, 0xD, 0xD,                             // 10|xx'xxxx (CB)
        0x1D, 0xD,                                      // 110|x'xxxx (C2)
        0xE7,                                           // 1110|'xxxx (C3)
        0x0,                                            // 1111'xxxx (Illegal header)
        0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5,         // 0|xxx'xxxx (C1)
        0xD, 0xD, 0xD, 0xD,                             // 10|xx'xxxx (CB)
        0x1D, 0xD,                                      // 110|x'xxxx (C2)
        0xE7,                                           // 1110|'xxxx (C3)
        0x0                                             // 1111'xxxx (Illegal header)
    );
    static __m256i const table1_lo = _mm256_setr_epi8(
        0x3F, 0x1F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, // 0|xxx'xxxx (C1)
        0x0F, 0x0F, 0x0F, 0x0F,                         // 10|xx'xxxx (CB)
        0x0F, 0xCF,                                     // 110|x'xxxx (C2)
        0x0F,                                           // 1110|'xxxx (C3)
        0x0F,                                           // 1111'xxxx (Illegal header)
        0x3F, 0x1F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, // 0|xxx'xxxx (C1)
        0x0F, 0x0F, 0x0F, 0x0F,                         // 10|xx'xxxx (CB)
        0x0F, 0xCF,                                     // 110|x'xxxx (C2)
        0x0F,                                           // 1110|'xxxx (C3)
        0x0F                                            // 1111'xxxx (Illegal header)
    );
    // clang-format on

    __m256i prev_bytes         = _mm256_setzero_si256();
    __m256i has_error          = _mm256_setzero_si256();
    __m256i prev_hi_surrogates = _mm256_setzero_si256();
    while (len >= 32) {
        // Load next bytes
        __m256i bytes3 = _mm256_loadu_si256(reinterpret_cast<__m256i const*>(str));
        __m256i bytes2 = shift_right_bytewise<1>(bytes3, prev_bytes);
        __m256i bytes1 = shift_right_bytewise<2>(bytes3, prev_bytes);

        // Extract header bits
        __m256i nibbles3    = extract_high_nibbles(bytes3);
        __m256i nibbles2    = extract_high_nibbles(bytes2);
        __m256i nibbles1_hi = extract_high_nibbles(bytes1);
        __m256i nibbles1_lo = _mm256_and_si256(bytes1, _mm256_set1_epi8(0x0F));

        // Table lookup
        __m256i result3    = _mm256_shuffle_epi8(table3, nibbles3);
        __m256i result2    = _mm256_shuffle_epi8(table2, nibbles2);
        __m256i result1_hi = _mm256_shuffle_epi8(table1_hi, nibbles1_hi);
        __m256i result1_lo = _mm256_shuffle_epi8(table1_lo, nibbles1_lo);

        // Detect error conditions A) Too short, B) Too long, D) Overlong
        __m256i tmp = _mm256_and_si256(result2, _mm256_and_si256(result1_hi, result1_lo));
        __m256i errors_abd = _mm256_and_si256(tmp, result3);

        // Detect error condition E) Incomplete surrogate
        __m256i hi_surrogates = _mm256_and_si256(tmp, _mm256_set1_epi8(0x80));
        __m256i lo_surrogates = _mm256_and_si256(tmp, _mm256_set1_epi8(0x40));
        lo_surrogates         = _mm256_slli_epi16(lo_surrogates, 1);
        __m256i shifted_hi_surrogates =
            shift_right_bytewise<3>(hi_surrogates, prev_hi_surrogates);
        __m256i errors_e = _mm256_xor_si256(shifted_hi_surrogates, lo_surrogates);

        // Detect error condition C) Illegal header
        __m256i errors_c = _mm256_cmpeq_epi8(_mm256_set1_epi8(0xF), nibbles3);

        // Store error conditions
        has_error = _mm256_or_si256(has_error, errors_abd);
        has_error = _mm256_or_si256(has_error, errors_c);
        has_error = _mm256_or_si256(has_error, errors_e);

        // Setup next iteration
        prev_hi_surrogates = hi_surrogates;
        prev_bytes         = bytes3;
        str += 32;
        len -= 32;
    }

    if (!_mm256_testz_si256(has_error, has_error)) {
        return false;
    }

    /*
    The AVX validation iterates the string with a step size of 32. Remaining bytes have to be validated using
    the non-SIMD algorithm. The last bytes processed by the AVX validation may contain the start of a multi-byte
    code point which extends into the remaining bytes. The non-SIMD algorithm can not start validation in the middle
    of a code point, so str/len must potentially be adjusted to the last completly validated code point
    */

    // Value error must not be considered only structural as we start revalidation anyways
    uint32_t hi_surrogates = _mm256_movemask_epi8(prev_hi_surrogates);
    hi_surrogates &= 0xE0000000; // extract 3 msbs
    size_t offset = 0;
    if (hi_surrogates == (1u << 29)) {
        offset = 5;
    }
    else if (hi_surrogates == (1u << 30)) {
        offset = 4;
    }
    else if (hi_surrogates == (1u << 31)) {
        offset = 3;
    }
    else if (is_cu3(str[-2])) { // Checks surrogate pair as well
        offset = 2;
    }
    else if ((str[-1] & 0xC0) == 0xC0) { // Checks 2 and 3 byte header
        offset = 1;
    }
    return is_valid_cesu8_scalar(str - offset, len + offset);
}

} // namespace cesu8

#endif // #ifdef CESU8_VALIDATION_AVX_IMPLEMENTATION
