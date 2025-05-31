// Copyright 2025 atikdd.ru

#include <bst.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <string>
#include <vector>


class BSTInOrderIteratorTest : public ::testing::Test {
 protected:
    TBinSearchTree<int> tree;

    void SetUp() override {
        //       10
        //      /  \
        //     5    15
        //    / \   / \
        //   3   7 12  18

        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(3);
        tree.insert(7);
        tree.insert(12);
        tree.insert(18);
    }
};

TEST(BSTInOrderIteratorEmptyTest, EmptyTree) {
    TBinSearchTree<int> emptyTree;
    EXPECT_EQ(emptyTree.beginInOrder(), emptyTree.endInOrder());
    EXPECT_EQ(emptyTree.begin(), emptyTree.end());

    int count = 0;
    for (auto it = emptyTree.beginInOrder();
         it != emptyTree.endInOrder(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

TEST_F(BSTInOrderIteratorTest, SingleElementTree) {
    TBinSearchTree<int> singleTree;
    singleTree.insert(42);

    EXPECT_NE(singleTree.beginInOrder(), singleTree.endInOrder());

    auto it = singleTree.beginInOrder();
    EXPECT_EQ(*it, 42);

    ++it;
    EXPECT_EQ(it, singleTree.endInOrder());

    int count = 0;
    for (auto it = singleTree.beginInOrder();
         it != singleTree.endInOrder(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 1);
}

TEST_F(BSTInOrderIteratorTest, OrderedTraversal) {
    std::vector<int> inOrderValues;
    for (auto it = tree.beginInOrder(); it != tree.endInOrder(); ++it) {
        inOrderValues.push_back(*it);
    }

    EXPECT_EQ(inOrderValues.size(), 7);

    std::vector<int> expectedValues = {3, 5, 7, 10, 12, 15, 18};
    EXPECT_EQ(inOrderValues, expectedValues);

    std::vector<int> sortedValues = inOrderValues;
    std::sort(sortedValues.begin(), sortedValues.end());
    EXPECT_EQ(inOrderValues, sortedValues);
}

TEST_F(BSTInOrderIteratorTest, IteratorOperators) {
    auto it = tree.beginInOrder();

    EXPECT_EQ(*it, 3);

    auto it2 = ++it;
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(*it2, 5);

    auto it3 = it++;
    EXPECT_EQ(*it, 7);
    EXPECT_EQ(*it3, 5);

    EXPECT_NE(it, tree.endInOrder());

    auto it4 = it;
    EXPECT_EQ(it, it4);
}

TEST_F(BSTInOrderIteratorTest, ForRangeLoop) {
    std::vector<int> values;

    for (const auto& value : tree) {
        values.push_back(value);
    }

    EXPECT_EQ(values.size(), 7);
    std::vector<int> expectedValues = {3, 5, 7, 10, 12, 15, 18};
    EXPECT_EQ(values, expectedValues);
}

TEST_F(BSTInOrderIteratorTest, TraversalAfterModification) {
    tree.insert(1);
    tree.insert(20);

    std::vector<int> values;
    for (auto it = tree.beginInOrder(); it != tree.endInOrder(); ++it) {
        values.push_back(*it);
    }

    EXPECT_EQ(values.size(), 9);
    std::vector<int> expectedValues = {1, 3, 5, 7, 10, 12, 15, 18, 20};
    EXPECT_EQ(values, expectedValues);

    tree.remove(10);

    values.clear();
    for (auto it = tree.beginInOrder(); it != tree.endInOrder(); ++it) {
        values.push_back(*it);
    }

    EXPECT_EQ(values.size(), 8);
    expectedValues = {1, 3, 5, 7, 12, 15, 18, 20};
    EXPECT_EQ(values, expectedValues);
}

TEST_F(BSTInOrderIteratorTest, DereferenceEndIteratorThrows) {
    auto endIt = tree.endInOrder();
    EXPECT_THROW(*endIt, std::out_of_range);
}
