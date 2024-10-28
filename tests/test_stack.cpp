// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include <stack.h>

TEST(StackTest, DefaultConstructor) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, TopAndCopyConstructor) {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    Stack<int> s2(s1);
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.top(), 2);
    s2.pop();
    EXPECT_EQ(s2.top(), 1);
    EXPECT_EQ(s1.top(), 2);
}

TEST(StackTest, AssignmentOperator) {
    Stack<int> s1;
    s1.push(3);
    s1.push(4);
    Stack<int> s2;
    s2 = s1;
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.top(), 4);
    s2.pop();
    EXPECT_EQ(s2.top(), 3);
    EXPECT_EQ(s1.top(), 4);
}

TEST(StackTest, TopEmptyStack) {
    Stack<int> s;
    EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(StackTest, PushAndTop) {
    Stack<int> s;
    s.push(5);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 5);
}

TEST(StackTest, MultiplePush) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, Pop) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.pop();
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 10);
}

TEST(StackTest, PopUntilEmpty) {
    Stack<int> s;
    s.push(1);
    s.pop();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
    EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(StackTest, Clear) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}
