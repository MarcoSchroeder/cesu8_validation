#include "cesu8.hpp"
#include "cesu8_common.hpp"

#include <immintrin.h>

#include <cstdint>

using namespace cesu8::impl;

namespace cesu8 {

bool is_valid_cesu8_AVX(byte const* str, std::size_t len)
{
        static __m256i const lookup_table3 = _mm256_setr_epi8(
            CESU8_IMPLEMENTATION_LOOKUPTABLE_3_VALUES, CESU8_IMPLEMENTATION_LOOKUPTABLE_3_VALUES);
        static __m256i const lookup_table2 = _mm256_setr_epi8(
            CESU8_IMPLEMENTATION_LOOKUPTABLE_2_VALUES, CESU8_IMPLEMENTATION_LOOKUPTABLE_2_VALUES);
        static __m256i const lookup_table1_high = _mm256_setr_epi8(
            CESU8_IMPLEMENTATION_LOOKUPTABLE_1HIGH_VALUES,
            CESU8_IMPLEMENTATION_LOOKUPTABLE_1HIGH_VALUES);
        static __m256i const lookup_table1_low = _mm256_setr_epi8(
            CESU8_IMPLEMENTATION_LOOKUPTABLE_1LOW_VALUES,
            CESU8_IMPLEMENTATION_LOOKUPTABLE_1LOW_VALUES);

        __m256i prev_bytes =
            _mm256_setzero_si256(); // Zero values will be interpeted as preceding ascii in first loop iteration
        __m256i has_error            = _mm256_setzero_si256();
        __m256i prev_high_surrogates = _mm256_setzero_si256();
        while (len >= 32) {
                // Load next bytes
                __m256i bytes3 = _mm256_loadu_si256(reinterpret_cast<__m256i const*>(str));
                __m256i bytes2 = _mm256_alignr_epi8(
                    bytes3, _mm256_permute2x128_si256(prev_bytes, bytes3, 0x21), 15);
                __m256i bytes1 = _mm256_alignr_epi8(
                    bytes3, _mm256_permute2x128_si256(prev_bytes, bytes3, 0x21), 14);

                // Extract header bits by shifting entire register right by 4-bit and masking lowest 4 bits in each lane
                __m256i nibbles3 =
                    _mm256_and_si256(_mm256_srli_epi16(bytes3, 4), _mm256_set1_epi8(0x0F));
                __m256i nibbles2 =
                    _mm256_and_si256(_mm256_srli_epi16(bytes2, 4), _mm256_set1_epi8(0x0F));
                __m256i nibbles1_low = _mm256_and_si256(bytes1, _mm256_set1_epi8(0x0F));
                __m256i nibbles1_high =
                    _mm256_and_si256(_mm256_srli_epi16(bytes1, 4), _mm256_set1_epi8(0x0F));

                // Table lookup
                __m256i result3      = _mm256_shuffle_epi8(lookup_table3, nibbles3);
                __m256i result2      = _mm256_shuffle_epi8(lookup_table2, nibbles2);
                __m256i result1_low  = _mm256_shuffle_epi8(lookup_table1_low, nibbles1_low);
                __m256i result1_high = _mm256_shuffle_epi8(lookup_table1_high, nibbles1_high);
                __m256i temp =
                    _mm256_and_si256(result2, _mm256_and_si256(result1_high, result1_low));

                // Detect error conditions A) Too short, B) Too long, D) Overlong
                __m256i error_flags_abd = _mm256_and_si256(temp, result3);

                // Incomplete surrogates
                __m256i high_surrogates         = _mm256_and_si256(temp, _mm256_set1_epi8(0x80));
                __m256i low_surrogates          = _mm256_and_si256(temp, _mm256_set1_epi8(0x40));
                low_surrogates                  = _mm256_slli_epi16(low_surrogates, 1);
                __m256i shifted_high_surrogates = _mm256_alignr_epi8(
                    high_surrogates,
                    _mm256_permute2x128_si256(prev_high_surrogates, high_surrogates, 0x21),
                    13);
                __m256i error_flags_e = _mm256_xor_si256(shifted_high_surrogates, low_surrogates);

                // Illegal header
                __m256i error_flags_c = _mm256_cmpeq_epi8(_mm256_set1_epi8(0xF), nibbles3);

                // Store error conditions
                has_error = _mm256_or_si256(has_error, error_flags_abd);
                has_error = _mm256_or_si256(has_error, error_flags_c);
                has_error = _mm256_or_si256(has_error, error_flags_e);

                // Setup next iteration
                prev_high_surrogates = high_surrogates;
                prev_bytes           = bytes3;
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
        uint32_t high_surrogates = _mm256_movemask_epi8(prev_high_surrogates);
        high_surrogates &= 0xE0000000; // extract 3 msbs
        size_t offset = 0;
        if (high_surrogates == (1u << 29)) {
                offset = 5;
        }
        else if (high_surrogates == (1u << 30)) {
                offset = 4;
        }
        else if (high_surrogates == (1u << 31)) {
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
