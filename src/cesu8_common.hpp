#ifndef CESU8_VALIDATION_COMMON_HPP
#define CESU8_VALIDATION_COMMON_HPP

#define CESU8_IMPLEMENTATION_LOOKUPTABLE_1HIGH_VALUES \
    0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0xD, 0xD, 0xD, 0xD, 0x1D, 0xD, 0xE7, 0x0
#define CESU8_IMPLEMENTATION_LOOKUPTABLE_1LOW_VALUES                                    \
    0x3F, 0x1F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0xCF, \
        0x0F, 0x0F
#define CESU8_IMPLEMENTATION_LOOKUPTABLE_2_VALUES                                       \
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x3A, 0x3A, 0x9A, 0x5A, 0x11, 0x11, \
        0x11, 0x0
#define CESU8_IMPLEMENTATION_LOOKUPTABLE_3_VALUES                                       \
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3C, 0x3C, 0x3C, 0x3C, 0x33, 0x33, \
        0x33, 0x0

namespace cesu8::impl {

using byte = unsigned char;

constexpr bool is_c1(byte b) { return (b & 0x80) == 0; }
constexpr bool is_c2(byte b) { return (b & 0xE0) == 0xC0; }
constexpr bool is_c3(byte b) { return (b & 0xF0) == 0xE0; }
constexpr bool is_cb(byte b) { return (b & 0xC0) == 0x80; }

constexpr bool is_overlong_c2_cb(byte c2) { return c2 <= 0xC1; }
constexpr bool is_overlong_c3_cb_cb(byte c3, byte cb)
{
    return (c3 == 0xE0) && (cb <= 0x9F);
}

constexpr bool is_ed(byte b) { return b == 0xED; }
constexpr bool is_a_or_b(byte b) { return (b & 0xE0) == 0xA0; }
constexpr bool is_ed_a(byte b1, byte b2) { return is_ed(b1) && ((b2 & 0xF0) == 0xA0); }

constexpr bool is_ed_a_cb(byte b1, byte b2, byte b3)
{
    return is_ed_a(b1, b2) && is_cb(b3);
}

constexpr bool is_ed_b_cb(byte b1, byte b2, byte b3)
{
    return is_ed(b1) && ((b2 & 0xF0) == 0xB0) && (is_cb(b3));
}

} // namespace cesu8::impl

#endif //CESU8_VALIDATION_COMMON_HPP
