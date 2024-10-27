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
