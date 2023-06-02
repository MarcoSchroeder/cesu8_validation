#ifndef CESU8_VALIDATION_HPP
#define CESU8_VALIDATION_HPP

#include <cstddef>

namespace cesu8 {

bool is_valid_cesu8_scalar(unsigned char const* str, std::size_t len);
bool is_valid_cesu8_SSE(unsigned char const* str, std::size_t len);
bool is_valid_cesu8_AVX(unsigned char const* str, std::size_t len);

} // namespace cesu8::impl

#endif //CESU8_VALIDATION_HPP
