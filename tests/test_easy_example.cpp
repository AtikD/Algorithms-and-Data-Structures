// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include "easy_example.h"

TEST(DivisionTest, PositiveNumbers) {
    EXPECT_FLOAT_EQ(division(10, 2), 5.0f);
}

TEST(DivisionTest, DivisionByZero) {
    EXPECT_THROW(division(10, 0), std::invalid_argument);
}
