#pragma once
#ifndef CESU_STATS_HPP
#define CESU_STATS_HPP

#include "../cesu8.hpp"
#include "../cesu8_common.hpp"

#include <stdexcept>

using namespace cesu8;
using namespace cesu8::impl;

struct Cesu8Stats
{
    int nr_codepoints = 0;
    int nr_c1 = 0;
    int nr_c2 = 0;
    int nr_c3 = 0;
    int nr_surrogate = 0;
};

Cesu8Stats validate_and_collect_stats(byte const* str, std::size_t len)
{
    if(!is_valid_cesu8_scalar(str, len)) {
        throw std::runtime_error("invalid cesu8");
    }

    Cesu8Stats stats;
    while (len > 0)
    {
        if(is_c1(*str)) { // 1-byte codepoint
            ++str;
            --len;
            ++stats.nr_c1;
        }
        else if(is_c2(*str)) { // 2-byte codepoint
            str += 2;
            len -= 2;
            ++stats.nr_c2;
        }
        else if(is_c3(*str)) { 
            if( !is_ed(*str) || !is_a_or_b(str[1]) ) { // 3-byte codepoint
                str += 3;
                len -= 3;
                ++stats.nr_c3;
            }
            else if(is_ed_a(*str, str[1])) { // 6-byte codepoint
                str += 6;
                len -= 6;
                ++stats.nr_surrogate;
            }
        }
        ++stats.nr_codepoints;
    }

    return stats;
}

#endif // #ifndef CESU_STATS_HPP
