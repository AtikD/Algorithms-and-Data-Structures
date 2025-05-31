// Copyright 2025 atikdd.t.me

#include <gtest/gtest.h>
#include <max_heap.h>
#include <vector>
#include <algorithm>

class MaxHeapTest : public ::testing::Test {
 protected:
    MaxHeap<int> heap;

    void SetUp() override {
        heap.insert(5);
        heap.insert(3);
        heap.insert(8);
        heap.insert(1);
        heap.insert(7);
    }
};

TEST_F(MaxHeapTest, DefaultConstructor) {
    MaxHeap<int> emptyHeap;
    EXPECT_TRUE(emptyHeap.is_empty());
    EXPECT_EQ(emptyHeap.size(), 0);
}

TEST_F(MaxHeapTest, SizeConstructor) {
    MaxHeap<int> sizedHeap(10);
    EXPECT_TRUE(sizedHeap.is_empty());
    EXPECT_EQ(sizedHeap.size(), 0);
}

TEST_F(MaxHeapTest, ArrayConstructor) {
    int arr[] = {5, 3, 8, 1, 7};
    MaxHeap<int> heapFromArray(5, arr);

    EXPECT_EQ(heapFromArray.size(), 5);
    EXPECT_EQ(heapFromArray.top(), 8);

    EXPECT_EQ(heapFromArray.remove_top(), 8);
    EXPECT_EQ(heapFromArray.remove_top(), 7);
    EXPECT_EQ(heapFromArray.remove_top(), 5);
    EXPECT_EQ(heapFromArray.remove_top(), 3);
    EXPECT_EQ(heapFromArray.remove_top(), 1);
    EXPECT_TRUE(heapFromArray.is_empty());
}

TEST_F(MaxHeapTest, CopyConstructor) {
    MaxHeap<int> copy(heap);

    EXPECT_EQ(copy.size(), heap.size());
    EXPECT_EQ(copy.top(), heap.top());

    copy.remove_top();
    EXPECT_NE(copy.size(), heap.size());
}

TEST_F(MaxHeapTest, Insert) {
    EXPECT_EQ(heap.size(), 5);

    heap.insert(10);
    EXPECT_EQ(heap.size(), 6);
    EXPECT_EQ(heap.top(), 10);

    heap.insert(4);
    EXPECT_EQ(heap.size(), 7);
    EXPECT_EQ(heap.top(), 10);
}

TEST_F(MaxHeapTest, IsEmpty) {
    EXPECT_FALSE(heap.is_empty());

    MaxHeap<int> emptyHeap;
    EXPECT_TRUE(emptyHeap.is_empty());

    while (!heap.is_empty()) {
        heap.remove_top();
    }
    EXPECT_TRUE(heap.is_empty());
}

TEST_F(MaxHeapTest, Size) {
    EXPECT_EQ(heap.size(), 5);

    heap.insert(10);
    EXPECT_EQ(heap.size(), 6);

    heap.remove_top();
    EXPECT_EQ(heap.size(), 5);
}

TEST_F(MaxHeapTest, Top) {
    EXPECT_EQ(heap.top(), 8);

    heap.insert(10);
    EXPECT_EQ(heap.top(), 10);

    EXPECT_EQ(heap.size(), 6);
}

TEST_F(MaxHeapTest, RemoveTop) {
    EXPECT_EQ(heap.remove_top(), 8);
    EXPECT_EQ(heap.remove_top(), 7);
    EXPECT_EQ(heap.remove_top(), 5);
    EXPECT_EQ(heap.remove_top(), 3);
    EXPECT_EQ(heap.remove_top(), 1);

    EXPECT_TRUE(heap.is_empty());
}

TEST_F(MaxHeapTest, Emplace) {
    heap.emplace(2, 10);
    EXPECT_EQ(heap.top(), 10);

    EXPECT_EQ(heap.size(), 5);
}

TEST_F(MaxHeapTest, Clear) {
    heap.clear();
    EXPECT_TRUE(heap.is_empty());
    EXPECT_EQ(heap.size(), 0);
}

TEST_F(MaxHeapTest, IndexOperator) {
    EXPECT_NO_THROW(heap[0]);
    EXPECT_NO_THROW(heap[4]);

    EXPECT_THROW(heap[5], std::out_of_range);
}

TEST_F(MaxHeapTest, EmptyHeapOperations) {
    MaxHeap<int> emptyHeap;

    EXPECT_THROW(emptyHeap.top(), std::out_of_range);
    EXPECT_THROW(emptyHeap.remove_top(), std::out_of_range);
    EXPECT_THROW(emptyHeap.emplace(0, 10), std::out_of_range);
    EXPECT_THROW(emptyHeap[0], std::out_of_range);
}

TEST_F(MaxHeapTest, LargeHeap) {
    MaxHeap<int> largeHeap;
    const int size = 1000;

    for (int i = 0; i < size; i++) {
        largeHeap.insert(i);
    }

    EXPECT_EQ(largeHeap.size(), size);
    EXPECT_EQ(largeHeap.top(), size - 1);

    for (int i = size - 1; i >= 0; i--) {
        EXPECT_EQ(largeHeap.remove_top(), i);
    }

    EXPECT_TRUE(largeHeap.is_empty());
}

TEST_F(MaxHeapTest, HeapSort) {
    int arr[] = {5, 3, 8, 1, 7};
    const int size = 5;

    MaxHeap<int> sortHeap(size, arr);

    for (int i = size - 1; i >= 0; i--) {
        arr[i] = sortHeap.remove_top();
    }

    for (int i = 1; i < size; i++) {
        EXPECT_LE(arr[i-1], arr[i]);
    }
}

TEST_F(MaxHeapTest, EmplaceSiftDown) {
    MaxHeap<int> testHeap;
    testHeap.insert(10);
    testHeap.insert(8);
    testHeap.insert(9);
    testHeap.insert(5);
    testHeap.insert(6);

    testHeap.emplace(0, 4);

    EXPECT_EQ(testHeap.top(), 9);

    int topValue = testHeap.remove_top();
    EXPECT_EQ(topValue, 9);
    EXPECT_EQ(testHeap.top(), 8);

    std::vector<int> expected = {8, 6, 5, 4};
    for (size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(testHeap.remove_top(), expected[i]);
    }
}

TEST_F(MaxHeapTest, EmplaceOutOfRange) {
    EXPECT_THROW(heap.emplace(heap.size(), 10), std::out_of_range);
    EXPECT_THROW(heap.emplace(heap.size() + 5, 10), std::out_of_range);
}

TEST_F(MaxHeapTest, TopOnEmptyHeap) {
    MaxHeap<int> emptyHeap;
    EXPECT_THROW(emptyHeap.top(), std::out_of_range);
}

TEST_F(MaxHeapTest, RemoveTopOnEmptyHeap) {
    MaxHeap<int> emptyHeap;
    EXPECT_THROW(emptyHeap.remove_top(), std::out_of_range);
}

TEST(HeapAssignmentTest, MaxHeapAssignment) {
    MaxHeap<int> heap1;
    heap1.insert(5);
    heap1.insert(3);
    heap1.insert(8);

    MaxHeap<int> heap2;
    heap2 = heap1;

    EXPECT_EQ(heap2.size(), heap1.size());
    EXPECT_EQ(heap2.top(), heap1.top());

    heap1.insert(10);
    EXPECT_NE(heap2.size(), heap1.size());

    EXPECT_EQ(heap1.top(), 10);
    EXPECT_EQ(heap2.top(), 8);
}
