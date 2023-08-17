#include "simd_hguards.hpp"

#include "cesu8.hpp"
#include "cesu8_common.hpp"

#include <immintrin.h>

#include <cstdint>

#ifdef CESU8_VALIDATION_AVX512_IMPLEMENTATION

using namespace cesu8::impl;

namespace cesu8 {

static __m512i extract_high_nibbles(__m512i a)
{
    __m512i low_nibble_mask = _mm512_set1_epi8(0x0F);
    __m512i a_shifted       = _mm512_srli_epi16(a, 4);
    __m512i high_nibbles    = _mm512_and_si512(a_shifted, low_nibble_mask);
    return high_nibbles;
}

template<std::uint8_t nr_bytes>
static __m512i shift_right_bytewise(__m512i shift, __m512i insert)
{
    __m512i          tmp1           = _mm512_alignr_epi32(shift, insert, 15);
    constexpr size_t bits_to_shift1 = ((64 - nr_bytes) % 4) * 8;
    tmp1                            = _mm512_srli_epi32(tmp1, bits_to_shift1);
    constexpr size_t bits_to_shift2 = (4 - ((64 - nr_bytes) % 4)) * 8;
    __m512i          tmp2           = _mm512_slli_epi32(shift, bits_to_shift2);
    __m512i          shifted        = _mm512_or_si512(tmp1, tmp2);
    return shifted;
}

bool is_valid_cesu8_AVX512(byte const* str, std::size_t len)
{
    static __m512i const table3 =
        _mm512_setr4_epi32(0x33333333, 0x33333333, 0x3C3C3C3C, 0x00333333);
    static __m512i const table2 =
        _mm512_setr4_epi32(0x14141414, 0x14141414, 0x5A9A3A3A, 0x00111111);
    static __m512i const table1_hi =
        _mm512_setr4_epi32(0x05050505, 0x05050505, 0x0D0D0D0D, 0x00E70D1D);
    static __m512i const table1_lo =
        _mm512_setr4_epi32(0x0F0F1F3F, 0x0F0F0F0F, 0x0F0F0F0F, 0x0F0FCF0F);

    __m512i   prev_bytes         = _mm512_setzero_si512();
    __m512i   has_error_abde     = _mm512_setzero_si512();
    __m512i   prev_hi_surrogates = _mm512_setzero_si512();
    __mmask64 has_error_c        = 0;
    while (len >= 64) {
        // Load next bytes
        __m512i bytes3 = _mm512_loadu_si512(reinterpret_cast<__m512i const*>(str));
        __m512i bytes2 = shift_right_bytewise<1>(bytes3, prev_bytes);
        __m512i bytes1 = shift_right_bytewise<2>(bytes3, prev_bytes);

        // Extract header bits
        __m512i nibbles3    = extract_high_nibbles(bytes3);
        __m512i nibbles2    = extract_high_nibbles(bytes2);
        __m512i nibbles1_hi = extract_high_nibbles(bytes1);
        __m512i nibbles1_lo = _mm512_and_si512(bytes1, _mm512_set1_epi8(0x0F));

        // Table lookup
        __m512i result3    = _mm512_shuffle_epi8(table3, nibbles3);
        __m512i result2    = _mm512_shuffle_epi8(table2, nibbles2);
        __m512i result1_hi = _mm512_shuffle_epi8(table1_hi, nibbles1_hi);
        __m512i result1_lo = _mm512_shuffle_epi8(table1_lo, nibbles1_lo);

        // Detect error conditions A) Too short, B) Too long, D) Overlong
        __m512i tmp = _mm512_and_si512(result2, _mm512_and_si512(result1_hi, result1_lo));
        __m512i errors_abd = _mm512_and_si512(tmp, result3);

        // Detect error condition E) Incomplete surrogate
        __m512i hi_surrogates = _mm512_and_si512(tmp, _mm512_set1_epi8(0x80));
        __m512i lo_surrogates = _mm512_and_si512(tmp, _mm512_set1_epi8(0x40));
        lo_surrogates         = _mm512_slli_epi16(lo_surrogates, 1);
        __m512i shifted_hi_surrogates =
            shift_right_bytewise<3>(hi_surrogates, prev_hi_surrogates);
        __m512i errors_e = _mm512_xor_si512(shifted_hi_surrogates, lo_surrogates);

        // Detect error condition C) Illegal header
        __mmask64 errors_c = _mm512_cmpeq_epi8_mask(_mm512_set1_epi8(0xF), nibbles3);
        has_error_c        = _kor_mask64(has_error_c, errors_c);

        // Store error conditions
        has_error_abde = _mm512_or_si512(has_error_abde, errors_abd);
        has_error_abde = _mm512_or_si512(has_error_abde, errors_e);

        // Setup next iteration
        prev_hi_surrogates = hi_surrogates;
        prev_bytes         = bytes3;
        str += 64;
        len -= 64;
    }

    int has_error_abde_ = _mm512_reduce_or_epi32(has_error_abde);
    if (has_error_abde_ || has_error_c) {
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

#endif // #ifdef CESU8_VALIDATION_AVX512_IMPLEMENTATION
