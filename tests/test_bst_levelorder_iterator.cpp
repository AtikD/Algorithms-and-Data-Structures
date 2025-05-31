// Copyright 2025 atikdd.ru

#include <bst.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

class BSTLevelOrderIteratorTest : public ::testing::Test {
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

TEST_F(BSTLevelOrderIteratorTest, EmptyTree) {
    TBinSearchTree<int> emptyTree;

    EXPECT_EQ(emptyTree.beginLevelOrder(), emptyTree.endLevelOrder());

    int count = 0;
    for (auto it = emptyTree.beginLevelOrder();
         it != emptyTree.endLevelOrder(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

TEST_F(BSTLevelOrderIteratorTest, SingleElementTree) {
    TBinSearchTree<int> singleTree;
    singleTree.insert(42);

    EXPECT_NE(singleTree.beginLevelOrder(), singleTree.endLevelOrder());

    auto it = singleTree.beginLevelOrder();
    EXPECT_EQ(*it, 42);

    EXPECT_EQ(it.level(), 0);

    ++it;
    EXPECT_EQ(it, singleTree.endLevelOrder());

    int count = 0;
    for (auto it = singleTree.beginLevelOrder();
         it != singleTree.endLevelOrder(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 1);
}

TEST_F(BSTLevelOrderIteratorTest, LevelOrderTraversal) {
    std::vector<int> values;
    std::vector<int> levels;

    for (auto it = tree.beginLevelOrder(); it != tree.endLevelOrder(); ++it) {
        values.push_back(*it);
        levels.push_back(it.level());
    }

    EXPECT_EQ(values.size(), 7);

    std::vector<int> expectedValues = {10, 5, 15, 3, 7, 12, 18};
    EXPECT_EQ(values, expectedValues);

    std::vector<int> expectedLevels = {0, 1, 1, 2, 2, 2, 2};
    EXPECT_EQ(levels, expectedLevels);
}

TEST_F(BSTLevelOrderIteratorTest, IteratorOperators) {
    auto it = tree.beginLevelOrder();

    EXPECT_EQ(*it, 10);
    EXPECT_EQ(it.level(), 0);

    auto it2 = ++it;
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(it.level(), 1);
    EXPECT_EQ(*it2, 5);

    auto it3 = it++;
    EXPECT_EQ(*it, 15);
    EXPECT_EQ(it.level(), 1);
    EXPECT_EQ(*it3, 5);

    EXPECT_NE(it, tree.endLevelOrder());

    auto it4 = it;
    EXPECT_EQ(it, it4);
}

TEST_F(BSTLevelOrderIteratorTest, DereferenceEndIteratorThrows) {
    auto endIt = tree.endLevelOrder();
    EXPECT_THROW(*endIt, std::out_of_range);
}
