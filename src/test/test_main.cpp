#include <gtest/gtest.h>

#include "test_AVX2.cpp"
#include "test_AVX512.cpp"
#include "test_SSE.cpp"
#include "test_scalar.cpp"
#include "test_stats.cpp"

int main(int argc, char** argv)
{
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}