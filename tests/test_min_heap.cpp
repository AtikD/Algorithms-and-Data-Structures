// Copyright 2025 atikdd.t.me

#include <gtest/gtest.h>
#include <min_heap.h>
#include <vector>
#include <algorithm>


class MinHeapTest : public ::testing::Test {
 protected:
    MinHeap<int> heap;

    void SetUp() override {
        heap.insert(5);
        heap.insert(3);
        heap.insert(8);
        heap.insert(1);
        heap.insert(7);
    }
};

TEST_F(MinHeapTest, DefaultConstructor) {
    MinHeap<int> emptyHeap;
    EXPECT_TRUE(emptyHeap.is_empty());
    EXPECT_EQ(emptyHeap.size(), 0);
}

TEST_F(MinHeapTest, SizeConstructor) {
    MinHeap<int> sizedHeap(10);
    EXPECT_TRUE(sizedHeap.is_empty());
    EXPECT_EQ(sizedHeap.size(), 0);
}

TEST_F(MinHeapTest, ArrayConstructor) {
    int arr[] = {5, 3, 8, 1, 7};
    MinHeap<int> heapFromArray(5, arr);

    EXPECT_EQ(heapFromArray.size(), 5);
    EXPECT_EQ(heapFromArray.top(), 1);

    EXPECT_EQ(heapFromArray.remove_top(), 1);
    EXPECT_EQ(heapFromArray.remove_top(), 3);
    EXPECT_EQ(heapFromArray.remove_top(), 5);
    EXPECT_EQ(heapFromArray.remove_top(), 7);
    EXPECT_EQ(heapFromArray.remove_top(), 8);
    EXPECT_TRUE(heapFromArray.is_empty());
}

TEST_F(MinHeapTest, CopyConstructor) {
    MinHeap<int> copy(heap);

    EXPECT_EQ(copy.size(), heap.size());
    EXPECT_EQ(copy.top(), heap.top());
}

TEST_F(MinHeapTest, Insert) {
    EXPECT_EQ(heap.size(), 5);

    heap.insert(0);
    EXPECT_EQ(heap.size(), 6);
    EXPECT_EQ(heap.top(), 0);

    heap.insert(4);
    EXPECT_EQ(heap.size(), 7);
    EXPECT_EQ(heap.top(), 0);
}

TEST_F(MinHeapTest, IsEmpty) {
    EXPECT_FALSE(heap.is_empty());

    MinHeap<int> emptyHeap;
    EXPECT_TRUE(emptyHeap.is_empty());

    while (!heap.is_empty()) {
        heap.remove_top();
    }
    EXPECT_TRUE(heap.is_empty());
}

TEST_F(MinHeapTest, Size) {
    EXPECT_EQ(heap.size(), 5);

    heap.insert(0);
    EXPECT_EQ(heap.size(), 6);

    heap.remove_top();
    EXPECT_EQ(heap.size(), 5);
}

TEST_F(MinHeapTest, Top) {
    EXPECT_EQ(heap.top(), 1);

    heap.insert(0);
    EXPECT_EQ(heap.top(), 0);
}

TEST_F(MinHeapTest, RemoveTop) {
    EXPECT_EQ(heap.remove_top(), 1);
    EXPECT_EQ(heap.remove_top(), 3);
    EXPECT_EQ(heap.remove_top(), 5);
    EXPECT_EQ(heap.remove_top(), 7);
    EXPECT_EQ(heap.remove_top(), 8);

    EXPECT_TRUE(heap.is_empty());
}

TEST_F(MinHeapTest, Emplace) {
    heap.emplace(2, 0);
    EXPECT_EQ(heap.top(), 0);

    EXPECT_EQ(heap.size(), 5);
}

TEST_F(MinHeapTest, Clear) {
    heap.clear();
    EXPECT_TRUE(heap.is_empty());
    EXPECT_EQ(heap.size(), 0);
}

TEST_F(MinHeapTest, IndexOperator) {
    EXPECT_EQ(heap[0], 1);
    EXPECT_EQ(heap[4], 7);

    EXPECT_THROW(heap[5], std::out_of_range);
}

TEST_F(MinHeapTest, EmptyHeapOperations) {
    MinHeap<int> emptyHeap;

    EXPECT_THROW(emptyHeap.top(), std::out_of_range);
    EXPECT_THROW(emptyHeap.remove_top(), std::out_of_range);
    EXPECT_THROW(emptyHeap.emplace(0, 10), std::out_of_range);
    EXPECT_THROW(emptyHeap[0], std::out_of_range);
}
TEST_F(MinHeapTest, EmplaceOutOfRange) {
    EXPECT_THROW(heap.emplace(heap.size(), 10), std::out_of_range);
    EXPECT_THROW(heap.emplace(heap.size() + 5, 10), std::out_of_range);
}
TEST_F(MinHeapTest, LargeHeap) {
    MinHeap<int> largeHeap;
    const int size = 1000;

    for (int i = 0; i < size; i++) {
        largeHeap.insert(i);
    }

    EXPECT_EQ(largeHeap.size(), size);
    EXPECT_EQ(largeHeap.top(), 0);

    for (int i = 0; i < size; i++) {
        EXPECT_EQ(largeHeap.remove_top(), i);
    }

    EXPECT_TRUE(largeHeap.is_empty());
}

TEST_F(MinHeapTest, HeapSort) {
    int arr[] = {5, 3, 8, 1, 7};
    const int size = 5;

    MinHeap<int> sortHeap(size, arr);

    for (int i = 0; i < size; i++) {
        arr[i] = sortHeap.remove_top();
    }

    for (int i = 1; i < size; i++) {
        EXPECT_LE(arr[i-1], arr[i]);
    }
}


