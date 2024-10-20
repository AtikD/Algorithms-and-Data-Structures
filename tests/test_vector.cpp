// Copyright 2024 atikdd.t.me


#include <gtest/gtest.h>
#include "../lib_vector/vector.h"

TEST(TVectorTest, DefaultConstructor) {
    TVector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.get_start_index(), 0);
}

TEST(TVectorTest, SizeConstructor) {
    TVector<int> vec(5, 1);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.get_start_index(), 1);

    for (size_t i = 1; i < vec.get_start_index() + vec.size(); ++i) {
        EXPECT_EQ(vec[i], 0);
    }
}

TEST(TVectorTest, ArrayConstructor) {
    int arr[] = {1, 2, 3, 4, 5};
    TVector<int> vec(arr, 5, 0);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.get_start_index(), 0);
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], arr[i]);
    }
}

TEST(TVectorTest, CopyConstructor) {
    TVector<int> vec1(3, 0);
    vec1[0] = 10;
    vec1[1] = 20;
    vec1[2] = 30;

    TVector<int> vec2(vec1);
    EXPECT_EQ(vec2.size(), vec1.size());
    EXPECT_EQ(vec2.get_start_index(), vec1.get_start_index());
    EXPECT_EQ(vec2[0], 10);
    EXPECT_EQ(vec2[1], 20);
    EXPECT_EQ(vec2[2], 30);
}

TEST(TVectorTest, MoveConstructor) {
    TVector<int> vec1(3, 0);
    vec1[0] = 5;
    vec1[1] = 10;
    vec1[2] = 15;

    TVector<int> vec2(std::move(vec1));
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2[0], 5);
    EXPECT_EQ(vec2[1], 10);
    EXPECT_EQ(vec2[2], 15);
    EXPECT_EQ(vec1.size(), 0);
}
