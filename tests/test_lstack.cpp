// Copyright 2024 atikdd.t.me

#include <lstack.h>
#include <gtest/gtest.h>


TEST(LStackTest, empty_InitiallyTrue) {
    LStack<int> stack;
    EXPECT_TRUE(stack.empty());
}

TEST(LStackTest, empty_AfterPushFalse) {
    LStack<int> stack;
    stack.push(42);
    EXPECT_FALSE(stack.empty());
}

TEST(LStackTest, Push_AddsElementToStack) {
    LStack<int> stack;
    stack.push(10);
    EXPECT_EQ(stack.top(), 10);
}

TEST(LStackTest, Push_SecondElementBecomesTop) {
    LStack<int> stack;
    stack.push(10);
    stack.push(20);
    EXPECT_EQ(stack.top(), 20);
}

TEST(LStackTest, Pop_RemovesTopElement) {
    LStack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.pop();
    EXPECT_EQ(stack.top(), 10);
}

TEST(LStackTest, Pop_EmptyAfterLastPop) {
    LStack<int> stack;
    stack.push(10);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(LStackTest, Pop_ThrowsIfEmpty) {
    LStack<int> stack;
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(LStackTest, Top_ReturnsTopElement) {
    LStack<int> stack;
    stack.push(42);
    EXPECT_EQ(stack.top(), 42);
}

TEST(LStackTest, Top_ThrowsIfEmpty) {
    LStack<int> stack;
    EXPECT_THROW(stack.top(), std::out_of_range);
}

