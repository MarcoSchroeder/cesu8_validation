#include "cesu8.hpp"
#include "cesu8_common.hpp"

#include <immintrin.h>

#include <cassert>
#include <cstdint>

using namespace cesu8::impl;

namespace cesu8 {

__m512i x_mm512_alignrvar_epi32(const __m512i hi, const __m512i lo, int shift)
{
        switch (shift) {
                case 0:
                        return lo;
                        break;
                case 1:
                        return _mm512_alignr_epi32(hi, lo, 1);
                        break;
                case 2:
                        return _mm512_alignr_epi32(hi, lo, 2);
                        break;
                case 3:
                        return _mm512_alignr_epi32(hi, lo, 3);
                        break;
                case 4:
                        return _mm512_alignr_epi32(hi, lo, 4);
                        break;
                case 5:
                        return _mm512_alignr_epi32(hi, lo, 5);
                        break;
                case 6:
                        return _mm512_alignr_epi32(hi, lo, 6);
                        break;
                case 7:
                        return _mm512_alignr_epi32(hi, lo, 7);
                        break;
                case 8:
                        return _mm512_alignr_epi32(hi, lo, 8);
                        break;
                case 9:
                        return _mm512_alignr_epi32(hi, lo, 9);
                        break;
                case 10:
                        return _mm512_alignr_epi32(hi, lo, 10);
                        break;
                case 11:
                        return _mm512_alignr_epi32(hi, lo, 11);
                        break;
                case 12:
                        return _mm512_alignr_epi32(hi, lo, 12);
                        break;
                case 13:
                        return _mm512_alignr_epi32(hi, lo, 13);
                        break;
                case 14:
                        return _mm512_alignr_epi32(hi, lo, 14);
                        break;
                case 15:
                        return _mm512_alignr_epi32(hi, lo, 15);
                        break;
                case 16:
                        return hi;
                        break;
                default:
                        assert(false);
        }
}

__m512i x_mm512_alignr_epi8(const __m512i hi, const __m512i lo, unsigned shift)
{
        assert(shift < 64);

        const int s32 = shift / 4; // shift amount in 32-bit words
        const int s8  = shift % 4; // shift amount within 32-bit word

        if (s8 == 0) {
                return x_mm512_alignrvar_epi32(hi, lo, s32);
        }
        else {
                const __m512i L = x_mm512_alignrvar_epi32(hi, lo, s32);
                const __m512i H = x_mm512_alignrvar_epi32(hi, lo, s32 + 1);

                return _mm512_or_si512(
                    _mm512_srli_epi32(L, s8 * 8), _mm512_slli_epi32(H, (4 - s8) * 8));
        }
}

static __m512i avx512_push_last_byte_of_a_to_b(__m512i a, __m512i b)
{
        //   __m512i indexes = _mm512_set_epi8(0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39, 0x38, 0x37,
        //                                     0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x2F,
        //                                     0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29, 0x28, 0x27,
        //                                     0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 0x1F,
        //                                     0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17,
        //                                     0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F,
        //                                     0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x07,
        //                                     0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x7F);

        //   return _mm512_permutex2var_epi8(b, indexes, a);
        //return indexes;
        return x_mm512_alignr_epi8(a, b, 63);
}

static __m512i avx512_push_last_2bytes_of_a_to_b(__m512i a, __m512i b)
{
        //   __m512i indexes = _mm512_set_epi64(0x3D3C3B3A39383736, 0x3534333231302F2E,
        //                                      0x2D2C2B2A29282726, 0x2524232221201F1E,
        //                                      0x1D1C1B1A19181716, 0x1514131211100F0E,
        //                                      0x0D0C0B0A09080706, 0x0504030201007F7E);
        //   //return _mm512_permutex2var_epi8(b, indexes, a);
        //   return indexes;
        return x_mm512_alignr_epi8(a, b, 62);
}

static __m512i avx512_push_last_3bytes_of_a_to_b(__m512i a, __m512i b)
{
        //   __m512i indexes = _mm512_set_epi64(0x3C3B3A3938373635, 0x34333231302F2E2D,
        //                                      0x2C2B2A2928272625, 0x24232221201F1E1D,
        //                                      0x1C1B1A1918171615, 0x14131211100F0E0D,
        //                                      0x0C0B0A0908070605, 0x04030201007F7E7D);
        //   //return _mm512_permutex2var_epi8(b, indexes, a);
        //   return indexes;
        return x_mm512_alignr_epi8(a, b, 61);
}

bool is_valid_cesu8_AVX512(byte const* str, std::size_t len)
{
        static __m512i const lookup_table3 =
            _mm512_setr4_epi32(0x33333333, 0x33333333, 0x3C3C3C3C, 0x00333333);
        static __m512i const lookup_table2 =
            _mm512_setr4_epi32(0x14141414, 0x14141414, 0x5A9A3A3A, 0x00111111);
        static __m512i const lookup_table1_high =
            _mm512_setr4_epi32(0x05050505, 0x05050505, 0x0D0D0D0D, 0x00E70D1D);
        static __m512i const lookup_table1_low =
            _mm512_setr4_epi32(0x0F0F1F3F, 0x0F0F0F0F, 0x0F0F0F0F, 0x0F0FCF0F);

        __m512i prev_bytes =
            _mm512_setzero_si512(); // Zero values will be interpeted as preceding ascii in first loop iteration
        __m512i   has_error            = _mm512_setzero_si512();
        __m512i   prev_high_surrogates = _mm512_setzero_si512();
        __mmask64 has_error_header     = 0;
        while (len >= 64) {
                // Load next bytes
                __m512i bytes3 = _mm512_loadu_si512(reinterpret_cast<__m512i const*>(str));
                __m512i bytes2 = avx512_push_last_byte_of_a_to_b(bytes3, prev_bytes);
                __m512i bytes1 = avx512_push_last_2bytes_of_a_to_b(bytes3, prev_bytes);

                // Extract header bits by shifting entire register right by 4-bit and masking lowest 4 bits in each lane
                __m512i nibbles3 =
                    _mm512_and_si512(_mm512_srli_epi16(bytes3, 4), _mm512_set1_epi8(0x0F));
                __m512i nibbles2 =
                    _mm512_and_si512(_mm512_srli_epi16(bytes2, 4), _mm512_set1_epi8(0x0F));
                __m512i nibbles1_low = _mm512_and_si512(bytes1, _mm512_set1_epi8(0x0F));
                __m512i nibbles1_high =
                    _mm512_and_si512(_mm512_srli_epi16(bytes1, 4), _mm512_set1_epi8(0x0F));

                // Table lookup
                __m512i result3      = _mm512_shuffle_epi8(lookup_table3, nibbles3);
                __m512i result2      = _mm512_shuffle_epi8(lookup_table2, nibbles2);
                __m512i result1_low  = _mm512_shuffle_epi8(lookup_table1_low, nibbles1_low);
                __m512i result1_high = _mm512_shuffle_epi8(lookup_table1_high, nibbles1_high);
                __m512i temp =
                    _mm512_and_si512(result2, _mm512_and_si512(result1_high, result1_low));

                // Detect error conditions A) Too short, B) Too long, D) Overlong
                __m512i error_flags_abd = _mm512_and_si512(temp, result3);

                // Incomplete surrogates
                __m512i high_surrogates = _mm512_and_si512(temp, _mm512_set1_epi8(0x80));
                __m512i low_surrogates  = _mm512_and_si512(temp, _mm512_set1_epi8(0x40));
                low_surrogates          = _mm512_slli_epi16(low_surrogates, 1);
                __m512i shifted_high_surrogates =
                    avx512_push_last_3bytes_of_a_to_b(high_surrogates, prev_high_surrogates);
                __m512i error_flags_e = _mm512_xor_si512(shifted_high_surrogates, low_surrogates);

                // Illegal header
                has_error_header = _kor_mask64(
                    has_error_header, _mm512_cmpeq_epi8_mask(_mm512_set1_epi8(0xF), nibbles3));

                // Store error conditions
                has_error = _mm512_or_si512(has_error, error_flags_abd);
                has_error = _mm512_or_si512(has_error, error_flags_e);

                // Setup next iteration
                prev_high_surrogates = high_surrogates;
                prev_bytes           = bytes3;
                str += 64;
                len -= 64;
        }

        int has_error_ = _mm512_reduce_or_epi32(has_error);
        if (has_error_ || has_error_header) {
                return false;
        }

        /*
    The AVX validation iterates the string with a step size of 32. Remaining bytes have to be validated using
    the non-SIMD algorithm. The last bytes processed by the AVX validation may contain the start of a multi-byte
    code point which extends into the remaining bytes. The non-SIMD algorithm can not start validation in the middle
    of a code point, so str/len must potentially be adjusted to the last completly validated code point
    */

        // Value error must not be considered only structural as we start revalidation anyways
        size_t offset = 0;
        if (is_ed_a_cb(str[-5], str[-4], str[-3])) {
                offset = 5;
        }
        else if (is_ed_a_cb(str[-4], str[-3], str[-2])) {
                offset = 4;
        }
        else if (is_ed_a_cb(str[-3], str[-2], str[-1])) {
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
