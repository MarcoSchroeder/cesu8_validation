#include <gtest/gtest.h>
#include "../cesu8.hpp"

#include <cstring>

struct Cesu8{
    enum  {
        CONTINUATION_BYTE = 0x8F,
        ASCII_BYTE = 0x41,
        TWO_BYTE_HEADER = 0xCF,
        THREE_BYTE_HEADER = 0xEF,
        ILLEGAL_BYTE = 0xF0,
        // Cesu8 6-byte code point (surrogate pair) byte 1-6
        SURROGATE_BYTE1 = 0xED,
        SURROGATE_BYTE2 = 0xA0,
        SURROGATE_BYTE3 = 0x8F,
        SURROGATE_BYTE4 = 0xED,
        SURROGATE_BYTE5 = 0xB0,
        SURROGATE_BYTE6 = 0x8F
    };
};

TEST(Cesu8Validation_Scalar, TooShort) {
  //Detect 'too short' code points, that is, multi-byte code points with not enough continuation bytes
    // Two-byte code point with missing continuation
    {
        unsigned char data[5];
        memset(data, Cesu8::ASCII_BYTE, 5);
        data[0] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 5));

    }
    // Three-byte code point with missing first and second continuation
    {
        unsigned char data[5];
        memset(data, Cesu8::ASCII_BYTE, 5);
        data[1] = Cesu8::THREE_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 5));
    }
    // Three-byte code point with missing second continuation
    {
        unsigned char data[5];
        memset(data, Cesu8::ASCII_BYTE, 5);
        data[2] = Cesu8::THREE_BYTE_HEADER;
        data[3] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 5));
    }
    // Two-byte code point with missing continuation before EOF
    {
        unsigned char data[10];
        memset(data, Cesu8::ASCII_BYTE, 10);
        data[9] = Cesu8::TWO_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 10));
    }
    // Three-byte code point with missing first and second continuation before EOF
    {
        unsigned char data[10];
        memset(data, Cesu8::ASCII_BYTE, 10);
        data[9] = Cesu8::THREE_BYTE_HEADER;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 10));
    }
    // Three-byte code point with missing second continuation before EOF
    {
        unsigned char data[10];
        memset(data, Cesu8::ASCII_BYTE, 10);
        data[8] = Cesu8::THREE_BYTE_HEADER;
        data[9] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 10));
    }
}

TEST(Cesu8Validation_Scalar, TooLong)
{
    //Detect 'too long' code points, that is, unexpected continuation bytes not part of a multi-byte code point
    {
        // First byte is continuation
        unsigned char data[1];
        data[0] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 1));
    }
    {
        // Continuation byte following ASCII byte
        unsigned char data[10];
        memset(data, Cesu8::ASCII_BYTE, 10);
        data[7] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 10));
    }
    {
        // Continuation byte following two-byte code point
        unsigned char data[15];
        memset(data, Cesu8::ASCII_BYTE, 15);
        data[12] = Cesu8::TWO_BYTE_HEADER;
        data[13] = Cesu8::CONTINUATION_BYTE;
        data[14] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 15));
    }
    {
        // Continuation byte following three-byte code point
        unsigned char data[15];
        memset(data, Cesu8::ASCII_BYTE, 15);
        data[11] = Cesu8::THREE_BYTE_HEADER;
        data[12] = Cesu8::CONTINUATION_BYTE;
        data[13] = Cesu8::CONTINUATION_BYTE;
        data[14] = Cesu8::CONTINUATION_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 15));
    }
}

TEST(Cesu8Validation_Scalar, IllegalHeader)
{
    //Detect bytes with illegal header bits, that is, with a 1111'xxxx pattern
    {
        // First byte is illegal
        unsigned char data[7];
        memset(data, Cesu8::ASCII_BYTE, 7);
        data[0] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 7));
    }
    {
        // Random byte is illegal
        unsigned char data[7];
        memset(data, Cesu8::ASCII_BYTE, 7);
        data[4] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 7));
    }
    {
        // Last byte is illegal
        unsigned char data[7];
        memset(data, Cesu8::ASCII_BYTE, 7);
        data[6] = Cesu8::ILLEGAL_BYTE;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 7));
    }
    {
        // All bytes are illegal
        unsigned char data[7];
        memset(data, Cesu8::ILLEGAL_BYTE, 7);
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 7));
    }
}

TEST(Cesu8Validation_Scalar, IncompleteSurrogate)
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
        unsigned char data[13];
        memset(data, Cesu8::ASCII_BYTE, 13);
        data[3] = Cesu8::SURROGATE_BYTE4;
        data[4] = Cesu8::SURROGATE_BYTE5;
        data[5] = Cesu8::SURROGATE_BYTE6;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 13));
    }
    {
        // Trailing surrogate missing
        unsigned char data[13];
        memset(data, Cesu8::ASCII_BYTE, 13);
        data[3] = Cesu8::SURROGATE_BYTE1;
        data[4] = Cesu8::SURROGATE_BYTE2;
        data[5] = Cesu8::SURROGATE_BYTE3;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 13));
    }
    {
        // The distance between the two three byte code points must be 3 bytes exactly, no bytes inbetween
        unsigned char data[13];
        memset(data, Cesu8::ASCII_BYTE, 13);
        data[0] = Cesu8::SURROGATE_BYTE1;
        data[1] = Cesu8::SURROGATE_BYTE2;
        data[2] = Cesu8::SURROGATE_BYTE3;
        data[4] = Cesu8::SURROGATE_BYTE4;
        data[5] = Cesu8::SURROGATE_BYTE5;
        data[6] = Cesu8::SURROGATE_BYTE6;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 13));
    }
}

TEST(Cesu8Validation_Scalar, Overlong)
{
    // Check value ranges

    // 1-byte code point (ASCII)
    {
        // Minimal value U+0000
        unsigned char data[1];
        data[0] = 0b0000'0000;
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 3));
    }
    {
        // Maxmimal value U+007F
        unsigned char data[1];
        data[0] = 0b0111'1111;
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 3));
    }
    {
        // Too large value U+0080 (should be detected as continuation byte)
        unsigned char data[1];
        data[0] = 0b1000'0000;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 1));
    }

    // 2-byte code point (U+0080 to U+07FF)
    {
        // Too small value U+007F
        unsigned char data[2];
        data[0] = 0b1100'0001;
        data[1] = 0b1011'1111;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 2));
    }
    {
        // Minimum value U+0080
        unsigned char data[2];
        data[0] = 0b1100'0010;
        data[1] = 0b1000'0000;
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 2));
    }
    {
        // Maximum value U+07FF
        unsigned char data[2];
        data[0] = 0b1101'1111;
        data[1] = 0b1011'1111;
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 2));
    }

    // 3-byte code point (U+800-U+D7FF and U+E000-U+FFFF)
    {
        // Too small value U+07FF
        unsigned char data[3];
        data[0] = 0b1110'0000;
        data[1] = 0b1001'1111;
        data[2] = 0b1011'1111;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 3));
    }
    {
        // Minimum value U+0800 to Maximum value U+D7FF

        // U+0800
        unsigned char data[3];
        data[0] = 0b1110'0000;
        data[1] = 0b1010'0000;
        data[2] = 0b1000'0000;
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 3));

        // U+D7FF
        data[0] = 0b1110'1101;
        data[1] = 0b1001'1111;
        data[2] = 0b1011'1111;
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 3));
    }
    {
        // Minimum value U+E000 to Maximum value U+FFFF

        // U+E000
        unsigned char data[3];
        data[0] = 0b1110'1110;
        data[1] = 0b1000'0000;
        data[2] = 0b1000'0000;
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 3));

        // U+FFFF
        data[0] = 0b1110'1111;
        data[1] = 0b1011'1111;
        data[2] = 0b1011'1111;
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 3));
    }
    {
        // U+D800 - U+DBFF and U+DC00 - U+DFFF is surrogate

        // U+D800
        unsigned char data[3];
        data[0] = 0b1110'1101;
        data[1] = 0b1010'0000;
        data[2] = 0b1000'0000;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 3));

        // U+DBFF
        data[0] = 0b1110'1101;
        data[1] = 0b1010'1111;
        data[2] = 0b1011'1111;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 3));

        // U+DC00
        data[0] = 0b1110'1101;
        data[1] = 0b1011'0000;
        data[2] = 0b1000'0000;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 3));

        // U+DFFF
        data[0] = 0b1110'1101;
        data[1] = 0b1011'1111;
        data[2] = 0b1011'1111;
        EXPECT_FALSE(cesu8::is_valid_cesu8_scalar(data, 3));
    }
}

TEST(Cesu8Validation_Scalar, ValidInput)
{
    // Recognize valid encoding
    {
        // ASCII
        unsigned char data[13];
        memset(data, Cesu8::ASCII_BYTE, 13);
        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 13));
    }
    {
        // All different code point lengths
        unsigned char data[13];
        memset(data, Cesu8::ASCII_BYTE, 13);
        data[0] = Cesu8::THREE_BYTE_HEADER;
        data[1] = Cesu8::CONTINUATION_BYTE;
        data[2] = Cesu8::CONTINUATION_BYTE;
        data[4] = Cesu8::SURROGATE_BYTE1;
        data[5] = Cesu8::SURROGATE_BYTE2;
        data[6] = Cesu8::SURROGATE_BYTE3;
        data[7] = Cesu8::SURROGATE_BYTE4;
        data[8] = Cesu8::SURROGATE_BYTE5;
        data[9] = Cesu8::SURROGATE_BYTE6;
        data[11] = Cesu8::TWO_BYTE_HEADER;
        data[12] = Cesu8::CONTINUATION_BYTE;

        EXPECT_TRUE(cesu8::is_valid_cesu8_scalar(data, 13));
    }
}
