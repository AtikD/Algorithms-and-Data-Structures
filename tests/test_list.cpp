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

TEST(TListTest, PushBack) {
    TList<int> list;
    list.push_back(10);
    EXPECT_EQ(list.find(10)->getValue(), 10);
}

TEST(TListTest, PushFront) {
    TList<int> list;
    list.push_front(5);
    EXPECT_EQ(list.find(5)->getValue(), 5);
}
