#include "cesu8.hpp"
#include "cesu8_common.hpp"

using namespace cesu8::impl;

namespace cesu8 {

bool is_valid_cesu8_scalar(byte const* str, std::size_t len)
{
        while (len > 0) {
                if (is_c1(*str)) { // 1-byte codepoint
                        ++str;
                        --len;
                }
                else if (is_c2(*str)) { // 2-byte codepoint
                        if (len < 2) {
                                return false;
                        }
                        if (!is_c0(str[1])) {
                                return false;
                        }
                        if (is_overlong_c2(*str)) {
                                return false;
                        }
                        str += 2;
                        len -= 2;
                }
                else if (is_c3(*str)) {
                        if (len < 3) {
                                return false;
                        }
                        if (!is_ed(*str) || !is_a_or_b(str[1])) { // 3-byte codepoint
                                if (!is_c0(str[1])) {
                                        return false;
                                }
                                if (!is_c0(str[2])) {
                                        return false;
                                }
                                if (is_overlong_c3(*str, str[1])) {
                                        return false;
                                }
                                str += 3;
                                len -= 3;
                        }
                        else if (is_ed_a(*str, str[1])) { // 6-byte codepoint
                                if (len < 6) {
                                        return false;
                                }
                                if (!is_c0(str[2])) {
                                        return false;
                                }
                                if (!is_ed_b_c0(str[3], str[4], str[5])) {
                                        return false;
                                }
                                str += 6;
                                len -= 6;
                        }
                        else { // Must be trailing surrogate
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
