#include "../simd_hguards.hpp"

#include "../cesu8.hpp"
#include "test_common.hpp"

#include <gtest/gtest.h>

#include <cstring>

#ifdef CESU8_VALIDATION_SSE_IMPLEMENTATION

TEST(Cesu8Validation_SSE, TooShort)
{
    //Detect 'too short' code points, that is, multi-byte code points with not enough continuation bytes
    {
        // Two-byte code point with missing continuation
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = Cesu8::TWO_BYTE_HEADER;
        in_iteration[1] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[15] = Cesu8::TWO_BYTE_HEADER;
        cross_iteration[16] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = Cesu8::TWO_BYTE_HEADER;
        remainder[18] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Three-byte code point with missing first and second continuation
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[1] = Cesu8::THREE_BYTE_HEADER;
        in_iteration[2] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[15] = Cesu8::THREE_BYTE_HEADER;
        cross_iteration[16] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = Cesu8::THREE_BYTE_HEADER;
        remainder[18] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Three-byte code point with missing second continuation
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[2] = Cesu8::THREE_BYTE_HEADER;
        in_iteration[3] = Cesu8::CONTINUATION_BYTE;
        in_iteration[4] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[14] = Cesu8::THREE_BYTE_HEADER;
        cross_iteration[15] = Cesu8::CONTINUATION_BYTE;
        cross_iteration[16] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = Cesu8::THREE_BYTE_HEADER;
        remainder[18] = Cesu8::CONTINUATION_BYTE;
        remainder[19] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Three-byte code point with missing first and second continuation before EOF
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[15] = Cesu8::THREE_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char remainder[18];
        memset(remainder, Cesu8::ASCII_BYTE, 18);
        remainder[17] = Cesu8::THREE_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 18));
    }
}

TEST(Cesu8Validation_SSE, TooLong)
{
    //Detect 'too long' code points, that is, unexpected continuation bytes not part of a multi-byte code point
    {
        // First byte is continuation
        unsigned char data[17];
        data[0] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(data, 17));
    }
    {
        // Continuation byte following ASCII byte
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[10] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[16] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Continuation byte following two-byte code point
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[6] = Cesu8::TWO_BYTE_HEADER;
        in_iteration[7] = Cesu8::CONTINUATION_BYTE;
        in_iteration[8] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[14] = Cesu8::TWO_BYTE_HEADER;
        cross_iteration[15] = Cesu8::CONTINUATION_BYTE;
        cross_iteration[16] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = Cesu8::TWO_BYTE_HEADER;
        remainder[18] = Cesu8::CONTINUATION_BYTE;
        remainder[19] = Cesu8::CONTINUATION_BYTE;
    }
    {
        // Continuation byte following three-byte code point
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[6] = Cesu8::THREE_BYTE_HEADER;
        in_iteration[7] = Cesu8::CONTINUATION_BYTE;
        in_iteration[8] = Cesu8::CONTINUATION_BYTE;
        in_iteration[9] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[14] = Cesu8::THREE_BYTE_HEADER;
        cross_iteration[15] = Cesu8::CONTINUATION_BYTE;
        cross_iteration[16] = Cesu8::CONTINUATION_BYTE;
        cross_iteration[17] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[21];
        memset(remainder, Cesu8::ASCII_BYTE, 21);
        remainder[17] = Cesu8::THREE_BYTE_HEADER;
        remainder[18] = Cesu8::CONTINUATION_BYTE;
        remainder[19] = Cesu8::CONTINUATION_BYTE;
        remainder[20] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 21));
    }
}

TEST(Cesu8Validation_SSE, IllegalHeader)
{
    //Detect bytes with illegal header bits, that is, with a 1111'xxxx pattern
    {
        // First byte is illegal
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[15] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[16] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Random byte is illegal
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[11] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[15] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[18] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Last byte is illegal
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[13] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[19] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // All bytes are illegal
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ILLEGAL_BYTE, 16);
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));
    }
}

TEST(Cesu8Validation_SSE, IncompleteSurrogate)
{
    /*
    Detect incomplete surrogate pairs. Surrogate pairs are two consecutive three-byte code points
    that are to be interpreted as single 6-byte code point:

    surrogate pair: B1-B2-B3-B4-B5-B6

    B1/B4 are three-byte headers with a specific value. B2/B5 are continuation bytes with a specific value.
    Surrogate pairs are recognized by the B1-B2/B4-B5 byte sequences. B3/B6 are regulat continuation bytes.
    A missing B3/B6 is therefore detected as incomplete 3-byte code point (compare 'tooShort' test cases)
    and not considered here.
    */
    {
        // Leading surrogate missing
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[8]  = Cesu8::SURROGATE_BYTE4;
        in_iteration[9]  = Cesu8::SURROGATE_BYTE5;
        in_iteration[10] = Cesu8::SURROGATE_BYTE6;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[15] = Cesu8::SURROGATE_BYTE4;
        cross_iteration[16] = Cesu8::SURROGATE_BYTE5;
        cross_iteration[17] = Cesu8::SURROGATE_BYTE6;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[25];
        memset(remainder, Cesu8::ASCII_BYTE, 25);
        remainder[19] = Cesu8::SURROGATE_BYTE4;
        remainder[20] = Cesu8::SURROGATE_BYTE5;
        remainder[21] = Cesu8::SURROGATE_BYTE6;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 25));
    }
    {
        // Trailing surrogate missing
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[5] = Cesu8::SURROGATE_BYTE1;
        in_iteration[6] = Cesu8::SURROGATE_BYTE2;
        in_iteration[7] = Cesu8::SURROGATE_BYTE3;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[14] = Cesu8::SURROGATE_BYTE1;
        cross_iteration[15] = Cesu8::SURROGATE_BYTE2;
        cross_iteration[16] = Cesu8::SURROGATE_BYTE3;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[25];
        memset(remainder, Cesu8::ASCII_BYTE, 25);
        remainder[19] = Cesu8::SURROGATE_BYTE1;
        remainder[20] = Cesu8::SURROGATE_BYTE2;
        remainder[21] = Cesu8::SURROGATE_BYTE3;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 25));
    }
    {
        // The distance between the two three byte code points must be 3 bytes exactly, no bytes inbetween
        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[5]  = Cesu8::SURROGATE_BYTE1;
        in_iteration[6]  = Cesu8::SURROGATE_BYTE2;
        in_iteration[7]  = Cesu8::SURROGATE_BYTE3;
        in_iteration[9]  = Cesu8::SURROGATE_BYTE4;
        in_iteration[10] = Cesu8::SURROGATE_BYTE5;
        in_iteration[11] = Cesu8::SURROGATE_BYTE6;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[35];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 35);
        cross_iteration[14] = Cesu8::SURROGATE_BYTE1;
        cross_iteration[15] = Cesu8::SURROGATE_BYTE2;
        cross_iteration[16] = Cesu8::SURROGATE_BYTE3;
        cross_iteration[18] = Cesu8::SURROGATE_BYTE4;
        cross_iteration[19] = Cesu8::SURROGATE_BYTE5;
        cross_iteration[20] = Cesu8::SURROGATE_BYTE6;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 35));

        unsigned char remainder[25];
        memset(remainder, Cesu8::ASCII_BYTE, 25);
        remainder[16] = Cesu8::SURROGATE_BYTE1;
        remainder[17] = Cesu8::SURROGATE_BYTE2;
        remainder[18] = Cesu8::SURROGATE_BYTE3;
        remainder[20] = Cesu8::SURROGATE_BYTE4;
        remainder[21] = Cesu8::SURROGATE_BYTE5;
        remainder[22] = Cesu8::SURROGATE_BYTE6;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 25));
    }
}

TEST(Cesu8Validation_SSE, Overlong)
{
    // Check value ranges

    // 1-byte code point (ASCII)
    {
        // Minimal value U+0000
        unsigned char data[20];
        memset(data, 0x0, 20);
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 20));
    }
    {
        // Maxmimal value U+007F
        unsigned char data[20];
        memset(data, 0b0111'1111, 20);
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 20));
    }
    {
        // Too large value U+0080 (should be detected as continuation byte)
        unsigned char in_iteration_remainder[20];
        memset(in_iteration_remainder, Cesu8::ASCII_BYTE, 20);
        in_iteration_remainder[5]  = 0b1000'0000;
        in_iteration_remainder[17] = 0b1000'0000;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration_remainder, 16));
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration_remainder, 20));
    }

    // 2-byte code point (U+0080 to U+07FF)
    {
        // Too small value U+007F
        unsigned char b1 = 0b1100'0001;
        unsigned char b2 = 0b1011'1111;

        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1;
        in_iteration[1] = b2;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[32];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1;
        cross_iteration[16] = b2;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1;
        remainder[18] = b2;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Minimum value U+0080
        unsigned char b1 = 0b1100'0010;
        unsigned char b2 = 0b1000'0000;

        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1;
        in_iteration[1] = b2;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[32];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1;
        cross_iteration[16] = b2;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1;
        remainder[18] = b2;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Maximum value U+07FF
        unsigned char b1 = 0b1101'1111;
        unsigned char b2 = 0b1011'1111;

        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1;
        in_iteration[1] = b2;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[32];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1;
        cross_iteration[16] = b2;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1;
        remainder[18] = b2;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }

    // 3-byte code point (U+800-U+D7FF and U+E000-U+FFFF)
    {
        // Too small value U+07FF
        unsigned char b1 = 0b1110'0000;
        unsigned char b2 = 0b1001'1111;
        unsigned char b3 = 0b1011'1111;

        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1;
        in_iteration[1] = b2;
        in_iteration[2] = b3;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[32];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1;
        cross_iteration[16] = b2;
        cross_iteration[17] = b3;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1;
        remainder[18] = b2;
        remainder[19] = b3;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Minimum value U+0800 to Maximum value U+D7FF
        // U+0800
        unsigned char b1_0800 = 0b1110'0000;
        unsigned char b2_0800 = 0b1010'0000;
        unsigned char b3_0800 = 0b1000'0000;

        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1_0800;
        in_iteration[1] = b2_0800;
        in_iteration[2] = b3_0800;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[32];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1_0800;
        cross_iteration[16] = b2_0800;
        cross_iteration[17] = b3_0800;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1_0800;
        remainder[18] = b2_0800;
        remainder[19] = b3_0800;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(remainder, 20));

        // U+D7FF
        unsigned char b1_d7ff = 0b1110'1101;
        unsigned char b2_d7ff = 0b1001'1111;
        unsigned char b3_d7ff = 0b1011'1111;

        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1_d7ff;
        in_iteration[1] = b2_d7ff;
        in_iteration[2] = b3_d7ff;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1_d7ff;
        cross_iteration[16] = b2_d7ff;
        cross_iteration[17] = b3_d7ff;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1_d7ff;
        remainder[18] = b2_d7ff;
        remainder[19] = b3_d7ff;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // Minimum value U+E000 to Maximum value U+FFFF
        // U+E000
        unsigned char b1_e000 = 0b1110'1110;
        unsigned char b2_e000 = 0b1000'0000;
        unsigned char b3_e000 = 0b1000'0000;

        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1_e000;
        in_iteration[1] = b2_e000;
        in_iteration[2] = b3_e000;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[32];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1_e000;
        cross_iteration[16] = b2_e000;
        cross_iteration[17] = b3_e000;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1_e000;
        remainder[18] = b2_e000;
        remainder[19] = b3_e000;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(remainder, 20));

        // U+FFFF
        unsigned char b1_ffff = 0b1110'1111;
        unsigned char b2_ffff = 0b1011'1111;
        unsigned char b3_ffff = 0b1011'1111;

        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1_ffff;
        in_iteration[1] = b2_ffff;
        in_iteration[2] = b3_ffff;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1_ffff;
        cross_iteration[16] = b2_ffff;
        cross_iteration[17] = b3_ffff;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1_ffff;
        remainder[18] = b2_ffff;
        remainder[19] = b3_ffff;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
    {
        // U+D800 - U+DBFF and U+DC00 - U+DFFF is surrogate
        // U+D800
        unsigned char b1_d800 = 0b1110'1101;
        unsigned char b2_d800 = 0b1010'0000;
        unsigned char b3_d800 = 0b1000'0000;

        unsigned char in_iteration[16];
        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1_d800;
        in_iteration[1] = b2_d800;
        in_iteration[2] = b3_d800;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        unsigned char cross_iteration[32];
        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1_d800;
        cross_iteration[16] = b2_d800;
        cross_iteration[17] = b3_d800;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        unsigned char remainder[20];
        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1_d800;
        remainder[18] = b2_d800;
        remainder[19] = b3_d800;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));

        // U+DBFF
        unsigned char b1_dbff = 0b1110'1101;
        unsigned char b2_dbff = 0b1010'1111;
        unsigned char b3_dbff = 0b1011'1111;

        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1_dbff;
        in_iteration[1] = b2_dbff;
        in_iteration[2] = b3_dbff;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1_dbff;
        cross_iteration[16] = b2_dbff;
        cross_iteration[17] = b3_dbff;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1_dbff;
        remainder[18] = b2_dbff;
        remainder[19] = b3_dbff;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));

        // U+DC00
        unsigned char b1_dc00 = 0b1110'1101;
        unsigned char b2_dc00 = 0b1011'0000;
        unsigned char b3_dc00 = 0b1000'0000;

        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1_dc00;
        in_iteration[1] = b2_dc00;
        in_iteration[2] = b3_dc00;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1_dc00;
        cross_iteration[16] = b2_dc00;
        cross_iteration[17] = b3_dc00;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1_dc00;
        remainder[18] = b2_dc00;
        remainder[19] = b3_dc00;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));

        // U+DFFF
        unsigned char b1_dfff = 0b1110'1101;
        unsigned char b2_dfff = 0b1011'1111;
        unsigned char b3_dfff = 0b1011'1111;

        memset(in_iteration, Cesu8::ASCII_BYTE, 16);
        in_iteration[0] = b1_dfff;
        in_iteration[1] = b2_dfff;
        in_iteration[2] = b3_dfff;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(in_iteration, 16));

        memset(cross_iteration, Cesu8::ASCII_BYTE, 32);
        cross_iteration[15] = b1_dfff;
        cross_iteration[16] = b2_dfff;
        cross_iteration[17] = b3_dfff;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(cross_iteration, 32));

        memset(remainder, Cesu8::ASCII_BYTE, 20);
        remainder[17] = b1_dfff;
        remainder[18] = b2_dfff;
        remainder[19] = b3_dfff;
        EXPECT_FALSE(cesu8::is_valid_cesu8_SSE(remainder, 20));
    }
}

TEST(Cesu8Validation_SSE, ValidInput)
{
    // Recognize valid encoding
    {
        // ASCII
        unsigned char data[40];
        memset(data, Cesu8::ASCII_BYTE, 40);
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 40));
    }
    {
        // All different code point lengths (INcluding surrogate pair)
        unsigned char data[45];
        memset(data, Cesu8::ASCII_BYTE, 45);

        // In iteration
        data[0]  = Cesu8::THREE_BYTE_HEADER;
        data[1]  = Cesu8::CONTINUATION_BYTE;
        data[2]  = Cesu8::CONTINUATION_BYTE;
        data[4]  = Cesu8::SURROGATE_BYTE1;
        data[5]  = Cesu8::SURROGATE_BYTE2;
        data[6]  = Cesu8::SURROGATE_BYTE3;
        data[7]  = Cesu8::SURROGATE_BYTE4;
        data[8]  = Cesu8::SURROGATE_BYTE5;
        data[9]  = Cesu8::SURROGATE_BYTE6;
        data[10] = Cesu8::TWO_BYTE_HEADER;
        data[11] = Cesu8::CONTINUATION_BYTE;

        // Cross iteration
        data[14] = Cesu8::THREE_BYTE_HEADER;
        data[15] = Cesu8::CONTINUATION_BYTE;
        data[16] = Cesu8::CONTINUATION_BYTE;

        // Remainder
        data[33] = Cesu8::THREE_BYTE_HEADER;
        data[34] = Cesu8::CONTINUATION_BYTE;
        data[35] = Cesu8::CONTINUATION_BYTE;
        data[36] = Cesu8::TWO_BYTE_HEADER;
        data[37] = Cesu8::CONTINUATION_BYTE;
        data[38] = Cesu8::SURROGATE_BYTE1;
        data[39] = Cesu8::SURROGATE_BYTE2;
        data[40] = Cesu8::SURROGATE_BYTE3;
        data[41] = Cesu8::SURROGATE_BYTE4;
        data[42] = Cesu8::SURROGATE_BYTE5;
        data[43] = Cesu8::SURROGATE_BYTE6;

        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 45));
    }
}

TEST(Cesu8Validation_SSE, ValidInputContinuationInRemainder)
{
    // Recognize valid encoding with continuation bytes in remainder
    {
        // Two-byte code point with continuation in remainder
        unsigned char data[22];
        memset(data, Cesu8::ASCII_BYTE, 22);
        data[15] = Cesu8::TWO_BYTE_HEADER;
        data[16] = Cesu8::CONTINUATION_BYTE;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 22));
    }
    {
        // Three-byte code point with first and second continuation in remainder
        unsigned char data[22];
        memset(data, Cesu8::ASCII_BYTE, 22);
        data[15] = Cesu8::THREE_BYTE_HEADER;
        data[16] = Cesu8::CONTINUATION_BYTE;
        data[17] = Cesu8::CONTINUATION_BYTE;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 22));
    }
    {
        // Three-byte code point with second continuation in remainder
        unsigned char data[22];
        memset(data, Cesu8::ASCII_BYTE, 22);
        data[14] = Cesu8::THREE_BYTE_HEADER;
        data[15] = Cesu8::CONTINUATION_BYTE;
        data[16] = Cesu8::CONTINUATION_BYTE;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 22));
    }
    {
        // Surrogate pair (six-byte code point with last five bytes in remainder)
        unsigned char data[22];
        memset(data, Cesu8::ASCII_BYTE, 22);
        data[15] = Cesu8::SURROGATE_BYTE1;
        data[16] = Cesu8::SURROGATE_BYTE2;
        data[17] = Cesu8::SURROGATE_BYTE3;
        data[18] = Cesu8::SURROGATE_BYTE4;
        data[19] = Cesu8::SURROGATE_BYTE5;
        data[20] = Cesu8::SURROGATE_BYTE6;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 22));
    }
    {
        // Surrogate pair (six-byte code point with last four bytes in remainder)
        unsigned char data[22];
        memset(data, Cesu8::ASCII_BYTE, 22);
        data[14] = Cesu8::SURROGATE_BYTE1;
        data[15] = Cesu8::SURROGATE_BYTE2;
        data[16] = Cesu8::SURROGATE_BYTE3;
        data[17] = Cesu8::SURROGATE_BYTE4;
        data[18] = Cesu8::SURROGATE_BYTE5;
        data[19] = Cesu8::SURROGATE_BYTE6;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 22));
    }
    {
        // Surrogate pair (six-byte code point with last three bytes in remainder)
        unsigned char data[22];
        memset(data, Cesu8::ASCII_BYTE, 22);
        data[13] = Cesu8::SURROGATE_BYTE1;
        data[14] = Cesu8::SURROGATE_BYTE2;
        data[15] = Cesu8::SURROGATE_BYTE3;
        data[16] = Cesu8::SURROGATE_BYTE4;
        data[17] = Cesu8::SURROGATE_BYTE5;
        data[18] = Cesu8::SURROGATE_BYTE6;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 22));
    }
    {
        // Surrogate pair (six-byte code point with last two bytes in remainder)
        unsigned char data[22];
        memset(data, Cesu8::ASCII_BYTE, 22);
        data[12] = Cesu8::SURROGATE_BYTE1;
        data[13] = Cesu8::SURROGATE_BYTE2;
        data[14] = Cesu8::SURROGATE_BYTE3;
        data[15] = Cesu8::SURROGATE_BYTE4;
        data[16] = Cesu8::SURROGATE_BYTE5;
        data[17] = Cesu8::SURROGATE_BYTE6;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 22));
    }
    {
        // Surrogate pair (six-byte code point with last byte in remainder)
        unsigned char data[22];
        memset(data, Cesu8::ASCII_BYTE, 22);
        data[11] = Cesu8::SURROGATE_BYTE1;
        data[12] = Cesu8::SURROGATE_BYTE2;
        data[13] = Cesu8::SURROGATE_BYTE3;
        data[14] = Cesu8::SURROGATE_BYTE4;
        data[15] = Cesu8::SURROGATE_BYTE5;
        data[16] = Cesu8::SURROGATE_BYTE6;
        EXPECT_TRUE(cesu8::is_valid_cesu8_SSE(data, 22));
    }
}

#endif // #ifdef CESU8_VALIDATION_SSE_IMPLEMENTATION
