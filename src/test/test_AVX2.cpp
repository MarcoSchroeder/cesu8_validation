#include "../cesu8.hpp"
#include "test_common.hpp"
#include <gtest/gtest.h>

#include <cstring>

TEST(Cesu8Validation_AVX2, TooShort)
{
        //Detect 'too short' code points, that is, multi-byte code points with not enough continuation bytes
        {
                // Two-byte code point with missing continuation
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = Cesu8::TWO_BYTE_HEADER;
                in_iteration[1] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[70];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 70);
                cross_iteration[31] = Cesu8::TWO_BYTE_HEADER;
                cross_iteration[32] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 70));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[17] = Cesu8::TWO_BYTE_HEADER;
                remainder[18] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Three-byte code point with missing first and second continuation
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[1] = Cesu8::THREE_BYTE_HEADER;
                in_iteration[2] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[70];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 70);
                cross_iteration[31] = Cesu8::THREE_BYTE_HEADER;
                cross_iteration[32] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 70));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[35] = Cesu8::THREE_BYTE_HEADER;
                remainder[36] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Three-byte code point with missing second continuation
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[2] = Cesu8::THREE_BYTE_HEADER;
                in_iteration[3] = Cesu8::CONTINUATION_BYTE;
                in_iteration[4] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[70];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 70);
                cross_iteration[30] = Cesu8::THREE_BYTE_HEADER;
                cross_iteration[31] = Cesu8::CONTINUATION_BYTE;
                cross_iteration[32] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 70));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[34] = Cesu8::THREE_BYTE_HEADER;
                remainder[35] = Cesu8::CONTINUATION_BYTE;
                remainder[36] = Cesu8::TWO_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Three-byte code point with missing first and second continuation before EOF
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[15] = Cesu8::THREE_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[36] = Cesu8::THREE_BYTE_HEADER;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
}

TEST(Cesu8Validation_AVX2, TooLong)
{
        //Detect 'too long' code points, that is, unexpected continuation bytes not part of a multi-byte code point
        {
                // First byte is continuation
                unsigned char data[32];
                data[0] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(data, 32));
        }
        {
                // Continuation byte following ASCII byte
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[10] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[32] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[70];
                memset(remainder, Cesu8::ASCII_BYTE, 70);
                remainder[67] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 70));
        }
        {
                // Continuation byte following two-byte code point
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[6] = Cesu8::TWO_BYTE_HEADER;
                in_iteration[7] = Cesu8::CONTINUATION_BYTE;
                in_iteration[8] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = Cesu8::TWO_BYTE_HEADER;
                cross_iteration[32] = Cesu8::CONTINUATION_BYTE;
                cross_iteration[33] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[35] = Cesu8::TWO_BYTE_HEADER;
                remainder[36] = Cesu8::CONTINUATION_BYTE;
                remainder[37] = Cesu8::CONTINUATION_BYTE;
        }
        {
                // Continuation byte following three-byte code point
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[6] = Cesu8::THREE_BYTE_HEADER;
                in_iteration[7] = Cesu8::CONTINUATION_BYTE;
                in_iteration[8] = Cesu8::CONTINUATION_BYTE;
                in_iteration[9] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[30] = Cesu8::THREE_BYTE_HEADER;
                cross_iteration[31] = Cesu8::CONTINUATION_BYTE;
                cross_iteration[32] = Cesu8::CONTINUATION_BYTE;
                cross_iteration[33] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = Cesu8::THREE_BYTE_HEADER;
                remainder[34] = Cesu8::CONTINUATION_BYTE;
                remainder[35] = Cesu8::CONTINUATION_BYTE;
                remainder[36] = Cesu8::CONTINUATION_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
}

TEST(Cesu8Validation_AVX2, IllegalHeader)
{
        //Detect bytes with illegal header bits, that is, with a 1111'xxxx pattern
        {
                // First byte is illegal
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = Cesu8::ILLEGAL_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = Cesu8::ILLEGAL_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[70];
                memset(remainder, Cesu8::ASCII_BYTE, 70);
                remainder[67] = Cesu8::ILLEGAL_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 70));
        }
        {
                // Random byte is illegal
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[11] = Cesu8::ILLEGAL_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = Cesu8::ILLEGAL_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[35] = Cesu8::ILLEGAL_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Last byte is illegal
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[13] = Cesu8::ILLEGAL_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = Cesu8::ILLEGAL_BYTE;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // All bytes are illegal
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ILLEGAL_BYTE, 32);
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));
        }
}

TEST(Cesu8Validation_AVX2, IncompleteSurrogate)
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
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[8]  = Cesu8::SURROGATE_BYTE4;
                in_iteration[9]  = Cesu8::SURROGATE_BYTE5;
                in_iteration[10] = Cesu8::SURROGATE_BYTE6;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[30] = Cesu8::SURROGATE_BYTE4;
                cross_iteration[31] = Cesu8::SURROGATE_BYTE5;
                cross_iteration[32] = Cesu8::SURROGATE_BYTE6;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[35] = Cesu8::SURROGATE_BYTE4;
                remainder[36] = Cesu8::SURROGATE_BYTE5;
                remainder[37] = Cesu8::SURROGATE_BYTE6;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Trailing surrogate missing
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[5] = Cesu8::SURROGATE_BYTE1;
                in_iteration[6] = Cesu8::SURROGATE_BYTE2;
                in_iteration[7] = Cesu8::SURROGATE_BYTE3;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[30] = Cesu8::SURROGATE_BYTE1;
                cross_iteration[31] = Cesu8::SURROGATE_BYTE2;
                cross_iteration[32] = Cesu8::SURROGATE_BYTE3;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = Cesu8::SURROGATE_BYTE1;
                remainder[34] = Cesu8::SURROGATE_BYTE2;
                remainder[35] = Cesu8::SURROGATE_BYTE3;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // The distance between the two three byte code points must be 3 bytes exactly, no bytes inbetween
                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[5]  = Cesu8::SURROGATE_BYTE1;
                in_iteration[6]  = Cesu8::SURROGATE_BYTE2;
                in_iteration[7]  = Cesu8::SURROGATE_BYTE3;
                in_iteration[9]  = Cesu8::SURROGATE_BYTE4;
                in_iteration[10] = Cesu8::SURROGATE_BYTE5;
                in_iteration[11] = Cesu8::SURROGATE_BYTE6;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[30] = Cesu8::SURROGATE_BYTE1;
                cross_iteration[31] = Cesu8::SURROGATE_BYTE2;
                cross_iteration[32] = Cesu8::SURROGATE_BYTE3;
                cross_iteration[34] = Cesu8::SURROGATE_BYTE4;
                cross_iteration[35] = Cesu8::SURROGATE_BYTE5;
                cross_iteration[36] = Cesu8::SURROGATE_BYTE6;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = Cesu8::SURROGATE_BYTE1;
                remainder[34] = Cesu8::SURROGATE_BYTE2;
                remainder[35] = Cesu8::SURROGATE_BYTE3;
                remainder[37] = Cesu8::SURROGATE_BYTE4;
                remainder[38] = Cesu8::SURROGATE_BYTE5;
                remainder[39] = Cesu8::SURROGATE_BYTE6;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
}

TEST(Cesu8Validation_AVX2, Overlong)
{
        // Check value ranges

        // 1-byte code point (ASCII)
        {
                // Minimal value U+0000
                unsigned char data[32];
                memset(data, 0x0, 32);
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 32));
        }
        {
                // Maxmimal value U+007F
                unsigned char data[32];
                memset(data, 0b0111'1111, 32);
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 32));
        }
        {
                // Too large value U+0080 (should be detected as continuation byte)
                unsigned char in_iteration_remainder[40];
                memset(in_iteration_remainder, Cesu8::ASCII_BYTE, 40);
                in_iteration_remainder[5]  = 0b1000'0000;
                in_iteration_remainder[35] = 0b1000'0000;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration_remainder, 32));
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration_remainder, 40));
        }

        // 2-byte code point (U+0080 to U+07FF)
        {
                // Too small value U+007F
                unsigned char b1 = 0b1100'0001;
                unsigned char b2 = 0b1011'1111;

                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1;
                in_iteration[1] = b2;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = b1;
                cross_iteration[32] = b2;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[36] = b1;
                remainder[37] = b2;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Minimum value U+0080
                unsigned char b1 = 0b1100'0010;
                unsigned char b2 = 0b1000'0000;

                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1;
                in_iteration[1] = b2;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = b1;
                cross_iteration[32] = b2;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = b1;
                remainder[34] = b2;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Maximum value U+07FF
                unsigned char b1 = 0b1101'1111;
                unsigned char b2 = 0b1011'1111;

                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1;
                in_iteration[1] = b2;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = b1;
                cross_iteration[32] = b2;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[37] = b1;
                remainder[38] = b2;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }

        // 3-byte code point (U+800-U+D7FF and U+E000-U+FFFF)
        {
                // Too small value U+07FF
                unsigned char b1 = 0b1110'0000;
                unsigned char b2 = 0b1001'1111;
                unsigned char b3 = 0b1011'1111;

                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1;
                in_iteration[1] = b2;
                in_iteration[2] = b3;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[30] = b1;
                cross_iteration[31] = b2;
                cross_iteration[32] = b3;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[34] = b1;
                remainder[35] = b2;
                remainder[36] = b3;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Minimum value U+0800 to Maximum value U+D7FF
                // U+0800
                unsigned char b1_0800 = 0b1110'0000;
                unsigned char b2_0800 = 0b1010'0000;
                unsigned char b3_0800 = 0b1000'0000;

                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1_0800;
                in_iteration[1] = b2_0800;
                in_iteration[2] = b3_0800;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = b1_0800;
                cross_iteration[32] = b2_0800;
                cross_iteration[33] = b3_0800;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[34] = b1_0800;
                remainder[35] = b2_0800;
                remainder[36] = b3_0800;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(remainder, 40));

                // U+D7FF
                unsigned char b1_d7ff = 0b1110'1101;
                unsigned char b2_d7ff = 0b1001'1111;
                unsigned char b3_d7ff = 0b1011'1111;

                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1_d7ff;
                in_iteration[1] = b2_d7ff;
                in_iteration[2] = b3_d7ff;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = b1_d7ff;
                cross_iteration[32] = b2_d7ff;
                cross_iteration[33] = b3_d7ff;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = b1_d7ff;
                remainder[34] = b2_d7ff;
                remainder[35] = b3_d7ff;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // Minimum value U+E000 to Maximum value U+FFFF
                // U+E000
                unsigned char b1_e000 = 0b1110'1110;
                unsigned char b2_e000 = 0b1000'0000;
                unsigned char b3_e000 = 0b1000'0000;

                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1_e000;
                in_iteration[1] = b2_e000;
                in_iteration[2] = b3_e000;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = b1_e000;
                cross_iteration[32] = b2_e000;
                cross_iteration[33] = b3_e000;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = b1_e000;
                remainder[34] = b2_e000;
                remainder[35] = b3_e000;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(remainder, 40));

                // U+FFFF
                unsigned char b1_ffff = 0b1110'1111;
                unsigned char b2_ffff = 0b1011'1111;
                unsigned char b3_ffff = 0b1011'1111;

                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1_ffff;
                in_iteration[1] = b2_ffff;
                in_iteration[2] = b3_ffff;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[30] = b1_ffff;
                cross_iteration[31] = b2_ffff;
                cross_iteration[32] = b3_ffff;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[35] = b1_ffff;
                remainder[36] = b2_ffff;
                remainder[37] = b3_ffff;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
        {
                // U+D800 - U+DBFF and U+DC00 - U+DFFF is surrogate
                // U+D800
                unsigned char b1_d800 = 0b1110'1101;
                unsigned char b2_d800 = 0b1010'0000;
                unsigned char b3_d800 = 0b1000'0000;

                unsigned char in_iteration[32];
                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1_d800;
                in_iteration[1] = b2_d800;
                in_iteration[2] = b3_d800;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                unsigned char cross_iteration[64];
                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[30] = b1_d800;
                cross_iteration[31] = b2_d800;
                cross_iteration[32] = b3_d800;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                unsigned char remainder[40];
                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[34] = b1_d800;
                remainder[35] = b2_d800;
                remainder[36] = b3_d800;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));

                // U+DBFF
                unsigned char b1_dbff = 0b1110'1101;
                unsigned char b2_dbff = 0b1010'1111;
                unsigned char b3_dbff = 0b1011'1111;

                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1_dbff;
                in_iteration[1] = b2_dbff;
                in_iteration[2] = b3_dbff;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = b1_dbff;
                cross_iteration[32] = b2_dbff;
                cross_iteration[33] = b3_dbff;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = b1_dbff;
                remainder[34] = b2_dbff;
                remainder[35] = b3_dbff;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));

                // U+DC00
                unsigned char b1_dc00 = 0b1110'1101;
                unsigned char b2_dc00 = 0b1011'0000;
                unsigned char b3_dc00 = 0b1000'0000;

                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1_dc00;
                in_iteration[1] = b2_dc00;
                in_iteration[2] = b3_dc00;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[30] = b1_dc00;
                cross_iteration[31] = b2_dc00;
                cross_iteration[32] = b3_dc00;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[32] = b1_dc00;
                remainder[33] = b2_dc00;
                remainder[34] = b3_dc00;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));

                // U+DFFF
                unsigned char b1_dfff = 0b1110'1101;
                unsigned char b2_dfff = 0b1011'1111;
                unsigned char b3_dfff = 0b1011'1111;

                memset(in_iteration, Cesu8::ASCII_BYTE, 32);
                in_iteration[0] = b1_dfff;
                in_iteration[1] = b2_dfff;
                in_iteration[2] = b3_dfff;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(in_iteration, 32));

                memset(cross_iteration, Cesu8::ASCII_BYTE, 64);
                cross_iteration[31] = b1_dfff;
                cross_iteration[32] = b2_dfff;
                cross_iteration[33] = b3_dfff;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(cross_iteration, 64));

                memset(remainder, Cesu8::ASCII_BYTE, 40);
                remainder[33] = b1_dfff;
                remainder[34] = b2_dfff;
                remainder[35] = b3_dfff;
                EXPECT_FALSE(cesu8::is_valid_cesu8_AVX2(remainder, 40));
        }
}

TEST(Cesu8Validation_AVX2, ValidInput)
{
        // Recognize valid encoding
        {
                // ASCII
                unsigned char data[70];
                memset(data, Cesu8::ASCII_BYTE, 70);
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 70));
        }
        {
                // All different code point lengths (INcluding surrogate pair)
                unsigned char data[85];
                memset(data, Cesu8::ASCII_BYTE, 85);

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
                data[31] = Cesu8::THREE_BYTE_HEADER;
                data[32] = Cesu8::CONTINUATION_BYTE;
                data[33] = Cesu8::CONTINUATION_BYTE;

                // Remainder
                data[70] = Cesu8::THREE_BYTE_HEADER;
                data[71] = Cesu8::CONTINUATION_BYTE;
                data[72] = Cesu8::CONTINUATION_BYTE;
                data[73] = Cesu8::TWO_BYTE_HEADER;
                data[74] = Cesu8::CONTINUATION_BYTE;
                data[75] = Cesu8::SURROGATE_BYTE1;
                data[76] = Cesu8::SURROGATE_BYTE2;
                data[77] = Cesu8::SURROGATE_BYTE3;
                data[78] = Cesu8::SURROGATE_BYTE4;
                data[79] = Cesu8::SURROGATE_BYTE5;
                data[80] = Cesu8::SURROGATE_BYTE6;

                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 85));
        }
}

TEST(Cesu8Validation_AVX2, ValidInputContinuationInRemainder)
{
        // Recognize valid encoding with continuation bytes in remainder
        // {
        //     // Two-byte code point with continuation in remainder
        //     unsigned char data[40];
        //     memset(data, Cesu8::ASCII_BYTE, 40);
        //     data[31] = Cesu8::TWO_BYTE_HEADER;
        //     data[32] = Cesu8::CONTINUATION_BYTE;
        //     EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 40));
        // }
        // {
        //     // Three-byte code point with first and second continuation in remainder
        //     unsigned char data[40];
        //     memset(data, Cesu8::ASCII_BYTE, 40);
        //     data[31] = Cesu8::THREE_BYTE_HEADER;
        //     data[32] = Cesu8::CONTINUATION_BYTE;
        //     data[33] = Cesu8::CONTINUATION_BYTE;
        //     EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 40));
        // }
        // {
        //     // Three-byte code point with second continuation in remainder
        //     unsigned char data[40];
        //     memset(data, Cesu8::ASCII_BYTE, 40);
        //     data[30] = Cesu8::THREE_BYTE_HEADER;
        //     data[31] = Cesu8::CONTINUATION_BYTE;
        //     data[32] = Cesu8::CONTINUATION_BYTE;
        //     EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 40));
        // }
        // {
        //     // Surrogate pair (six-byte code point with last five bytes in remainder)
        //     unsigned char data[40];
        //     memset(data, Cesu8::ASCII_BYTE, 40);
        //     data[31] = Cesu8::SURROGATE_BYTE1;
        //     data[32] = Cesu8::SURROGATE_BYTE2;
        //     data[33] = Cesu8::SURROGATE_BYTE3;
        //     data[34] = Cesu8::SURROGATE_BYTE4;
        //     data[35] = Cesu8::SURROGATE_BYTE5;
        //     data[36] = Cesu8::SURROGATE_BYTE6;
        //     EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 40));
        // }
        // {
        //     // Surrogate pair (six-byte code point with last four bytes in remainder)
        //     unsigned char data[40];
        //     memset(data, Cesu8::ASCII_BYTE, 40);
        //     data[30] = Cesu8::SURROGATE_BYTE1;
        //     data[31] = Cesu8::SURROGATE_BYTE2;
        //     data[32] = Cesu8::SURROGATE_BYTE3;
        //     data[33] = Cesu8::SURROGATE_BYTE4;
        //     data[34] = Cesu8::SURROGATE_BYTE5;
        //     data[35] = Cesu8::SURROGATE_BYTE6;
        //     EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 40));
        // }
        {
                // Surrogate pair (six-byte code point with last three bytes in remainder)
                unsigned char data[40];
                memset(data, Cesu8::ASCII_BYTE, 40);
                data[29] = Cesu8::SURROGATE_BYTE1;
                data[30] = Cesu8::SURROGATE_BYTE2;
                data[31] = Cesu8::SURROGATE_BYTE3;
                data[32] = Cesu8::SURROGATE_BYTE4;
                data[33] = Cesu8::SURROGATE_BYTE5;
                data[34] = Cesu8::SURROGATE_BYTE6;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 40));
        }
        {
                // Surrogate pair (six-byte code point with last two bytes in remainder)
                unsigned char data[40];
                memset(data, Cesu8::ASCII_BYTE, 40);
                data[28] = Cesu8::SURROGATE_BYTE1;
                data[29] = Cesu8::SURROGATE_BYTE2;
                data[30] = Cesu8::SURROGATE_BYTE3;
                data[31] = Cesu8::SURROGATE_BYTE4;
                data[32] = Cesu8::SURROGATE_BYTE5;
                data[33] = Cesu8::SURROGATE_BYTE6;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 40));
        }
        {
                // Surrogate pair (six-byte code point with last byte in remainder)
                unsigned char data[40];
                memset(data, Cesu8::ASCII_BYTE, 40);
                data[27] = Cesu8::SURROGATE_BYTE1;
                data[28] = Cesu8::SURROGATE_BYTE2;
                data[29] = Cesu8::SURROGATE_BYTE3;
                data[30] = Cesu8::SURROGATE_BYTE4;
                data[31] = Cesu8::SURROGATE_BYTE5;
                data[32] = Cesu8::SURROGATE_BYTE6;
                EXPECT_TRUE(cesu8::is_valid_cesu8_AVX2(data, 40));
        }
}
