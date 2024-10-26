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


TEST(TVectorTest, CopyAssignmentOperator) {
    TVector<int> vec1(2, 0);
    vec1[0] = 1;
    vec1[1] = 2;

    TVector<int> vec2;
    vec2 = vec1;
    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
}

TEST(TVectorTest, AdditionOperator) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(3, 0);
    vec1[0] = 1;
    vec1[1] = 2;
    vec1[2] = 3;
    vec2[0] = 4;
    vec2[1] = 5;
    vec2[2] = 6;

    TVector<int> result = vec1 + vec2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
}

TEST(TVectorTest, AdditionOperatorDifferentSize) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(2, 0);
    EXPECT_THROW(vec1 + vec2, std::logic_error);
}

TEST(TVectorTest, SubtractionOperator) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(3, 0);
    vec1[0] = 5;
    vec1[1] = 7;
    vec1[2] = 9;
    vec2[0] = 1;
    vec2[1] = 2;
    vec2[2] = 3;

    TVector<int> result = vec1 - vec2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 4);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 6);
}

TEST(TVectorTest, ScalarProductOperator) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(3, 0);
    vec1[0] = 1;
    vec1[1] = 2;
    vec1[2] = 3;
    vec2[0] = 4;
    vec2[1] = 5;
    vec2[2] = 6;

    int result = vec1 * vec2;
    EXPECT_EQ(result, 32);  // 1*4 + 2*5 + 3*6 = 32
}

TEST(TVectorTest, AdditionAssignmentOperator) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(3, 0);
    vec1[0] = 1;
    vec1[1] = 2;
    vec1[2] = 3;
    vec2[0] = 4;
    vec2[1] = 5;
    vec2[2] = 6;

    vec1 += vec2;
    EXPECT_EQ(vec1[0], 5);
    EXPECT_EQ(vec1[1], 7);
    EXPECT_EQ(vec1[2], 9);
}

TEST(TVectorTest, SubtractionAssignmentOperator) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(3, 0);
    vec1[0] = 5;
    vec1[1] = 7;
    vec1[2] = 9;
    vec2[0] = 1;
    vec2[1] = 2;
    vec2[2] = 3;

    vec1 -= vec2;
    EXPECT_EQ(vec1[0], 4);
    EXPECT_EQ(vec1[1], 5);
    EXPECT_EQ(vec1[2], 6);
}

TEST(TVectorTest, EqualityOperator) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(3, 0);
    for (size_t i = 0; i < 3; ++i) {
        vec1[i] = static_cast<int>(i);
        vec2[i] = static_cast<int>(i);
    }
    EXPECT_TRUE(vec1 == vec2);

    vec2[2] = 10;
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_TRUE(vec1 != vec2);
}

TEST(TVectorTest, EqualityOperatorDifferentSize) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(4, 0);
    EXPECT_FALSE(vec1 == vec2);
}

TEST(TVectorTest, ScalarMultiplication) {
    TVector<int> vec(3, 0);
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    TVector<int> result = vec * 2;
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 6);

    vec *= 3;
    EXPECT_EQ(vec[0], 3);
    EXPECT_EQ(vec[1], 6);
    EXPECT_EQ(vec[2], 9);
}

TEST(TVectorTest, SizeAndStartIndexMethods) {
    TVector<int> vec(5, 2);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.get_start_index(), 2);

    vec.set_start_index(0);
    EXPECT_EQ(vec.get_start_index(), 0);
}

TEST(TVectorTest, ResizeMethod) {
    TVector<int> vec(3, 0);
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    vec.resize(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[3], 0);
    EXPECT_EQ(vec[4], 0);

    vec.resize(2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(TVectorTest, ClearMethod) {
    TVector<int> vec(3, 0);
    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;

    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.get_start_index(), 0);
}

TEST(TVectorTest, PrintMethod) {
    TVector<int> vec(3, 0);
    vec[0] = 5;
    vec[1] = 10;
    vec[2] = 15;

    std::stringstream ss;
    vec.print(ss);
    EXPECT_EQ(ss.str(), "{ 5, 10, 15 }");
}

TEST(TVectorTest, OperationsWithDifferentSizes) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(4, 0);
    EXPECT_THROW(vec1 + vec2, std::logic_error);
    EXPECT_THROW(vec1 - vec2, std::logic_error);
    EXPECT_THROW(vec1 * vec2, std::logic_error);
}

TEST(TVectorTest, OperationsWithDifferentStartIndices) {
    TVector<int> vec1(3, 0);
    TVector<int> vec2(3, 1);
    EXPECT_THROW(vec1 + vec2, std::logic_error);
}

TEST(TVectorTest, AccessOperator_OutOfRange) {
    TVector<int> vec(3, 0);
    EXPECT_THROW(vec[-1], std::out_of_range);
    EXPECT_THROW(vec[3], std::out_of_range);
}

TEST(TVectorTest, AccessOperator) {
    TVector<int> vec(2, 0);
    vec[0] = 5;
    vec[1] = 10;
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 10);
}
