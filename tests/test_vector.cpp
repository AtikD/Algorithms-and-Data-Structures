// Copyright 2024 atikdd.t.me


#include <gtest/gtest.h>
#include "../lib_vector/vector.h"

TEST(TVectorTest, DefaultConstructor) {
    TVector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.get_start_index(), 0);
}


