// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include <string>
#include <pair.h>

TEST(TPairTest, DefaultConstructor) {
  TPair<int, double> pair;
  EXPECT_EQ(pair.first(), 0);
  EXPECT_EQ(pair.second(), 0.0);
}

TEST(TPairTest, ParameterizedConstructor) {
  TPair<int, std::string> pair(42, "Answer");
  EXPECT_EQ(pair.first(), 42);
  EXPECT_EQ(pair.second(), "Answer");
}

TEST(TPairTest, CopyConstructor) {
  TPair<int, char> pair1(1, 'a');
  TPair<int, char> pair2(pair1);
  EXPECT_EQ(pair2.first(), 1);
  EXPECT_EQ(pair2.second(), 'a');
}

TEST(TPairTest, AssignmentOperator) {
  TPair<int, int> pair1(10, 20);
  TPair<int, int> pair2;
  pair2 = pair1;
  EXPECT_EQ(pair2.first(), 10);
  EXPECT_EQ(pair2.second(), 20);
}

TEST(TPairTest, EqualityOperator) {
  TPair<int, int> pair1(5, 5);
  TPair<int, int> pair2(5, 5);
  EXPECT_TRUE(pair1 == pair2);
}

TEST(TPairTest, Setters) {
  TPair<std::string, std::string> pair;
  pair.set_first("Hello");
  pair.set_second("World");
  EXPECT_EQ(pair.first(), "Hello");
  EXPECT_EQ(pair.second(), "World");
}

TEST(TPairComparisonTest, EqualityOperator) {
    TPair<int, std::string> pair1(5, "Five");
    TPair<int, std::string> pair2(5, "Another Five");
    TPair<int, std::string> pair3(10, "Ten");

    // Равенство определяется только по первому элементу (ключу)
    EXPECT_TRUE(pair1 == pair2);
    EXPECT_FALSE(pair1 == pair3);
}

TEST(TPairComparisonTest, LessThanOperator) {
    TPair<int, std::string> pair1(5, "Five");
    TPair<int, std::string> pair2(10, "Ten");
    TPair<int, std::string> pair3(5, "Another Five");

    EXPECT_TRUE(pair1 < pair2);
    EXPECT_FALSE(pair2 < pair1);
    EXPECT_FALSE(pair1 < pair3);  // Равные ключи
    EXPECT_FALSE(pair3 < pair1);  // Равные ключи
}

TEST(TPairComparisonTest, GreaterThanOperator) {
    TPair<int, std::string> pair1(5, "Five");
    TPair<int, std::string> pair2(10, "Ten");
    TPair<int, std::string> pair3(5, "Another Five");

    EXPECT_FALSE(pair1 > pair2);
    EXPECT_TRUE(pair2 > pair1);
    EXPECT_FALSE(pair1 > pair3);  // Равные ключи
    EXPECT_FALSE(pair3 > pair1);  // Равные ключи
}

TEST(TPairComparisonTest, LessOrEqualOperator) {
    TPair<int, std::string> pair1(5, "Five");
    TPair<int, std::string> pair2(10, "Ten");
    TPair<int, std::string> pair3(5, "Another Five");

    EXPECT_TRUE(pair1 <= pair2);
    EXPECT_FALSE(pair2 <= pair1);
    EXPECT_TRUE(pair1 <= pair3);  // Равные ключи
    EXPECT_TRUE(pair3 <= pair1);  // Равные ключи
}

TEST(TPairComparisonTest, GreaterOrEqualOperator) {
    TPair<int, std::string> pair1(5, "Five");
    TPair<int, std::string> pair2(10, "Ten");
    TPair<int, std::string> pair3(5, "Another Five");

    EXPECT_FALSE(pair1 >= pair2);
    EXPECT_TRUE(pair2 >= pair1);
    EXPECT_TRUE(pair1 >= pair3);  // Равные ключи
    EXPECT_TRUE(pair3 >= pair1);  // Равные ключи
}
