#include "cesu8.hpp"
#include "cesu8_common.hpp"

#include <immintrin.h>

#include <cstdint>

using namespace cesu8::impl;

namespace cesu8 {

bool is_valid_cesu8_SSE(byte const* str, std::size_t len)
{
    static __m128i const table3 = _mm_setr_epi8(CESU8_IMPLEMENTATION_LOOKUPTABLE_3_VALUES);
    static __m128i const table2 = _mm_setr_epi8(CESU8_IMPLEMENTATION_LOOKUPTABLE_2_VALUES);
    static __m128i const table1_high = _mm_setr_epi8(CESU8_IMPLEMENTATION_LOOKUPTABLE_1HIGH_VALUES);
    static __m128i const table1_low = _mm_setr_epi8(CESU8_IMPLEMENTATION_LOOKUPTABLE_1LOW_VALUES);

    __m128i prev_bytes = _mm_setzero_si128(); // Zero values will be interpeted as preceding ascii in first loop iteration
    __m128i has_error = _mm_setzero_si128();
    __m128i prev_high_surrogates = _mm_setzero_si128();
    while (len >= 16) {
        // Load next bytes
        __m128i bytes3 = _mm_loadu_si128(reinterpret_cast<__m128i const *>(str));
        __m128i bytes2 = _mm_alignr_epi8(bytes3, prev_bytes, 15);
        __m128i bytes1 = _mm_alignr_epi8(bytes3, prev_bytes, 14);

        // Extract header bits by shifting entire register right by 4-bit and masking lowest 4 bits in each lane
        __m128i nibbles3 = _mm_and_si128(_mm_srli_epi16(bytes3, 4), _mm_set1_epi8(0x0F));
        __m128i nibbles2 = _mm_and_si128(_mm_srli_epi16(bytes2, 4), _mm_set1_epi8(0x0F));
        __m128i nibbles1_low = _mm_and_si128(bytes1, _mm_set1_epi8(0x0F));
        __m128i nibbles1_high = _mm_and_si128(_mm_srli_epi16(bytes1, 4), _mm_set1_epi8(0x0F));

        // Table lookup
        __m128i result3 = _mm_shuffle_epi8(table3, nibbles3);
        __m128i result2 = _mm_shuffle_epi8(table2, nibbles2);
        __m128i result1_low = _mm_shuffle_epi8(table1_low, nibbles1_low);
        __m128i result1_high = _mm_shuffle_epi8(table1_high, nibbles1_high);
        __m128i temp = _mm_and_si128(result2, _mm_and_si128(result1_high, result1_low));

        // Detect error conditions A) Too short, B) Too long, D) Overlong
        __m128i error_flags_abd = _mm_and_si128(temp, result3);

        // Detect error condition E) Invalid surrogate
        __m128i high_surrogates = _mm_and_si128(temp, _mm_set1_epi8(0x80));
        __m128i low_surrogates = _mm_and_si128(temp, _mm_set1_epi8(0x40));
        low_surrogates = _mm_slli_epi16(low_surrogates, 1);
        __m128i shifted_high_surrogates = _mm_alignr_epi8(high_surrogates, prev_high_surrogates, 13);
        __m128i error_flags_e = _mm_xor_si128(shifted_high_surrogates, low_surrogates);

        // Detect error condition C) Illegal header
        __m128i error_flags_c = _mm_cmpeq_epi8(_mm_set1_epi8(0xF), nibbles3);

        // Store error conditions
        has_error = _mm_or_si128(has_error, error_flags_abd);
        has_error = _mm_or_si128(has_error, error_flags_c); 
        has_error = _mm_or_si128(has_error, error_flags_e); 

        // Setup next iteration
        prev_high_surrogates = high_surrogates;
        prev_bytes = bytes3;
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
    uint32_t high_surrogates = _mm_movemask_epi8(prev_high_surrogates);
    high_surrogates &= 0xE000; // extract 3 msbs
    size_t offset = 0;
    if (high_surrogates == (1u << 13)) {
        offset = 5;
    }
    else if (high_surrogates == (1u << 14)) {
        offset = 4;
    }
    else if (high_surrogates == (1u << 15)) {
        offset = 3;
    }
    else if (is_c3(str[-2])) { // Checks surrogate pair as well
        offset = 2;
    }
    else if ((str[-1] & 0xC0) == 0xC0) { // Checks 2 and 3 byte header
            offset = 1;
    }
    return is_valid_cesu8_scalar(str-offset, len+offset);
}

} // namespace cesu8
