#pragma once
#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

struct Cesu8 {
        enum {
                CONTINUATION_BYTE = 0x8F,
                ASCII_BYTE        = 0x41,
                TWO_BYTE_HEADER   = 0xCF,
                THREE_BYTE_HEADER = 0xEF,
                ILLEGAL_BYTE      = 0xF0,
                // Cesu8 6-byte code point (surrogate pair) byte 1-6
                SURROGATE_BYTE1 = 0xED,
                SURROGATE_BYTE2 = 0xA0,
                SURROGATE_BYTE3 = 0x8F,
                SURROGATE_BYTE4 = 0xED,
                SURROGATE_BYTE5 = 0xB0,
                SURROGATE_BYTE6 = 0x8F
        };
};

#endif // #ifndef TEST_COMMON_HPP
