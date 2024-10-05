// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include "../lib_pair/pair.h"

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

TEST(TPairTest, OutputOperator) {
  TPair<int, int> pair(1, 2);
  std::stringstream ss;
  ss << pair;
  EXPECT_EQ(ss.str(), "(1, 2)");
}
