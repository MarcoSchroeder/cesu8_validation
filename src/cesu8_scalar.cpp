#include "cesu8.hpp"
#include "cesu8_common.hpp"

using namespace cesu8::impl;

namespace cesu8 {

bool is_valid_cesu8_scalar(byte const* str, std::size_t len)
{
    while (len > 0) {
        // 1-unit encoded code point
        if (is_c1(*str)) {
            ++str;
            --len;
        }
        // 2-unit encoded code point
        else if (is_c2(*str)) {
            if (len < 2) {
                return false;
            }
            if (!is_cb(str[1])) {
                return false;
            }
            if (is_overlong_c2_cb(*str)) {
                return false;
            }
            str += 2;
            len -= 2;
        }
        else if (is_c3(*str)) {
            if (len < 3) {
                return false;
            }
            // 3-unit encoded code point
            if (!is_ed(*str) || !is_a_or_b(str[1])) {
                if (!is_cb(str[1])) {
                    return false;
                }
                if (!is_cb(str[2])) {
                    return false;
                }
                if (is_overlong_c3_cb_cb(*str, str[1])) {
                    return false;
                }
                str += 3;
                len -= 3;
            }
            // Surrogate pair
            else if (is_ed_a(*str, str[1])) {
                if (len < 6) {
                    return false;
                }
                if (!is_cb(str[2])) {
                    return false;
                }
                // Trailing surrogate
                if (!is_ed_b_cb(str[3], str[4], str[5])) {
                    return false;
                }
                str += 6;
                len -= 6;
            }
            else { // Must be lone trailing surrogate
                return false;
            }
        }
        else { // Must be illegal header or continuation byte
            return false;
        }
    }

    return true;
}

} // namespace cesu8
