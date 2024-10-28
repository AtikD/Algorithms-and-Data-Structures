// Copyright 2024 atikdd.t.me

#include <queue.h>
#include <massive.h>
#include <gtest/gtest.h>
#include <string>


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

TEST(TQueueTest, MassiveConstructor) {
    TMassive<int> massive;
    massive.push_back(1);
    massive.push_back(2);
    massive.push_back(3);

    TQueue<int> q(massive);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.capacity(), 3);

    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    EXPECT_TRUE(q.is_empty());
}

TEST(TQueueTest, MassiveConstructorEmpty) {
    TMassive<int> massive;
    TQueue<int> q(massive);
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.capacity(), 0);
}

TEST(TQueueTest, PushSuccess) {
    TQueue<int> q;
    q.push(10);
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.get_top(), 0);
    EXPECT_EQ(q.get_back(), 0);
    EXPECT_EQ(q.size(), 1);
}

TEST(TQueueTest, PushOverflow) {
    TQueue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);
    EXPECT_THROW(q.push(4), std::overflow_error);
}

TEST(TQueueTest, PopSuccess) {
    TQueue<int> q;
    q.push(10);
    q.push(20);
    int val = q.pop();
    EXPECT_EQ(val, 10);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.get_top(), 1);
    EXPECT_EQ(q.get_back(), 1);
}

TEST(TQueueTest, PopUnderflow) {
    TQueue<int> q;
    EXPECT_THROW(q.pop(), std::underflow_error);
}

TEST(TQueueTest, IsEmptyInitially) {
    TQueue<int> q;
    EXPECT_TRUE(q.is_empty());
}

TEST(TQueueTest, IsEmptyAfterPushPop) {
    TQueue<int> q;
    q.push(1);
    q.pop();
    EXPECT_TRUE(q.is_empty());
}

TEST(TQueueTest, IsFullAfterPushes) {
    TQueue<int> q(2);
    q.push(1);
    q.push(2);
    EXPECT_TRUE(q.is_full());
}

TEST(TQueueTest, IsNotFullAfterPop) {
    TQueue<int> q(2);
    q.push(1);
    q.push(2);
    q.pop();
    EXPECT_FALSE(q.is_full());
}

TEST(TQueueTest, ClearQueue) {
    TQueue<int> q;
    q.push(1);
    q.push(2);
    q.clear();
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.get_top(), -1);
    EXPECT_EQ(q.get_back(), -1);
}

TEST(TQueueTest, CycleShift) {
    TQueue<int> q(5);

    // Заполняем очередь
    for (int i = 0; i < 5; ++i) {
        q.push(i + 1);
    }
    EXPECT_TRUE(q.is_full());

    // Удаляем два элемента
    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);

    // Добавляем два элемента, чтобы вызвать циклический переход
    q.push(6);
    q.push(7);
    EXPECT_TRUE(q.is_full());

    // Проверяем состояние очереди
    EXPECT_EQ(q.get_top(), 2);
    EXPECT_EQ(q.get_back(), 1);

    // Проверяем элементы в очереди
    EXPECT_EQ(q.pop(), 3);
    EXPECT_EQ(q.pop(), 4);
    EXPECT_EQ(q.pop(), 5);
    EXPECT_EQ(q.pop(), 6);
    EXPECT_EQ(q.pop(), 7);
    EXPECT_TRUE(q.is_empty());
}
