// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include <string>
#include "../lib_queue/queue.h"

TEST(TQueueTest, DefaultConstructor) {
    TQueue<int> q;
    EXPECT_TRUE(q.is_empty());
    EXPECT_FALSE(q.is_full());
    EXPECT_EQ(q.get_top(), -1);
    EXPECT_EQ(q.get_back(), -1);
    EXPECT_EQ(q.capacity(), 10);
}

TEST(TQueueTest, CapacityConstructorValid) {
    TQueue<int> q(20);
    EXPECT_TRUE(q.is_empty());
    EXPECT_FALSE(q.is_full());
    EXPECT_EQ(q.capacity(), 20);
}

TEST(TQueueTest, CapacityConstructorInvalid) {
    EXPECT_THROW(TQueue<int> q(0), std::invalid_argument);
    EXPECT_THROW(TQueue<int> q(-5), std::invalid_argument);
}

TEST(TQueueTest, CopyConstructorEmptyQueue) {
    TQueue<int> q1;
    TQueue<int> q2(q1);
    EXPECT_TRUE(q2.is_empty());
    EXPECT_EQ(q2.capacity(), q1.capacity());
}

TEST(TQueueTest, CopyConstructorNonEmptyQueue) {
    TQueue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    TQueue<int> q2(q1);
    EXPECT_EQ(q2.size(), q1.size());
    EXPECT_EQ(q2.pop(), 1);
    EXPECT_EQ(q2.pop(), 2);
    EXPECT_EQ(q2.pop(), 3);
    EXPECT_TRUE(q2.is_empty());
}
