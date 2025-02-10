// Copyright 2025 atikdd.t.me

#include <gtest/gtest.h>
#include <dsu.h>
#include <iostream>

TEST(DSUTest, FindSuccessful) {
    DSU a(3);
    EXPECT_EQ(a.find(1), 1);
    EXPECT_EQ(a.find(2), 2);
    EXPECT_EQ(a.find(3), 3);
}

TEST(DSUTest, FindOutOfRange) {
    DSU a(3);
    EXPECT_THROW(a.find(10), std::logic_error);
    EXPECT_THROW(a.find(-1), std::logic_error);
}