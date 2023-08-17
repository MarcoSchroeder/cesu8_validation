#ifndef CESU8_VALIDATION_HPP
#define CESU8_VALIDATION_HPP

#include "simd_hguards.hpp"

#include <cstddef>
namespace cesu8 {

bool is_valid_cesu8_scalar(unsigned char const* str, std::size_t len);

#ifdef CESU8_VALIDATION_SSE_IMPLEMENTATION
bool is_valid_cesu8_SSE(unsigned char const* str, std::size_t len);
#endif

#ifdef CESU8_VALIDATION_AVX_IMPLEMENTATION
bool is_valid_cesu8_AVX2(unsigned char const* str, std::size_t len);
#endif

#ifdef CESU8_VALIDATION_AVX512_IMPLEMENTATION
bool is_valid_cesu8_AVX512(unsigned char const* str, std::size_t len);
#endif

} // namespace cesu8

#endif //CESU8_VALIDATION_HPP
