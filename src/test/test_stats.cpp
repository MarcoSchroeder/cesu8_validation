#include "../tools/cesu8_stats.hpp"
#include "test_common.hpp"
#include <gtest/gtest.h>

TEST(Cesu8Validation_Stats, CountCodepoints)
{
        unsigned char data[12];
        data[0]  = Cesu8::ASCII_BYTE;
        data[1]  = Cesu8::TWO_BYTE_HEADER;
        data[2]  = Cesu8::CONTINUATION_BYTE;
        data[3]  = Cesu8::THREE_BYTE_HEADER;
        data[4]  = Cesu8::CONTINUATION_BYTE;
        data[5]  = Cesu8::CONTINUATION_BYTE;
        data[6]  = Cesu8::SURROGATE_BYTE1;
        data[7]  = Cesu8::SURROGATE_BYTE2;
        data[8]  = Cesu8::SURROGATE_BYTE3;
        data[9]  = Cesu8::SURROGATE_BYTE4;
        data[10] = Cesu8::SURROGATE_BYTE5;
        data[11] = Cesu8::SURROGATE_BYTE6;

        Cesu8Stats stats = validate_and_collect_stats(data, 12);
        EXPECT_EQ(stats.nr_codepoints, 4);
        EXPECT_EQ(stats.nr_c1, 1);
        EXPECT_EQ(stats.nr_c2, 1);
        EXPECT_EQ(stats.nr_c1, 1);
        EXPECT_EQ(stats.nr_surrogate, 1);

        data[2] = Cesu8::ASCII_BYTE;
        EXPECT_THROW(validate_and_collect_stats(data, 12), std::runtime_error);
}