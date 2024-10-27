// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TListTest, Constructor_CreatesEmptyList) {
    TList<int> list;
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, IsEmpty_ReturnsFalse) {
    TList<int> list;
    list.push_back(1);
    EXPECT_FALSE(list.isEmpty());
}
