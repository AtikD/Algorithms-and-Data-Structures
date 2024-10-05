#include <gtest/gtest.h>
#include "easy_example.h"

TEST(DivisionTest, NegativeNumbers) {
    EXPECT_FLOAT_EQ(division(-10, 2), -5.0f);
}

TEST(DivisionTest, ZeroNumerator) {
    EXPECT_FLOAT_EQ(division(0, 5), 0.0f);
}
