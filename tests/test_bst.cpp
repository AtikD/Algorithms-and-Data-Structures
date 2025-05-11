// Copyright 2025 atikdd.ru

#include <bst.h>
#include <gtest/gtest.h>
#include <string>
#include <algorithm>


class BSTTest : public ::testing::Test {
 protected:
    TBinSearchTree<int> tree;

    void SetUp() override {
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        tree.insert(20);
        tree.insert(40);
        tree.insert(60);
        tree.insert(80);
    }
};

TEST_F(BSTTest, InitiallyEmpty) {
    TBinSearchTree<int> emptyTree;
    EXPECT_TRUE(emptyTree.isEmpty());
}

TEST_F(BSTTest, InitialSizeIsZero) {
    TBinSearchTree<int> emptyTree;
    EXPECT_EQ(emptyTree.size(), 0);
}

TEST_F(BSTTest, SizeAfterInsertions) {
    EXPECT_EQ(tree.size(), 7);
}

TEST_F(BSTTest, NotEmptyAfterInsertions) {
    EXPECT_FALSE(tree.isEmpty());
}

TEST_F(BSTTest, InsertNewElementReturnsTrue) {
    EXPECT_TRUE(tree.insert(90));
}

TEST_F(BSTTest, SizeIncreasesAfterNewInsertion) {
    size_t oldSize = tree.size();
    tree.insert(90);
    EXPECT_EQ(tree.size(), oldSize + 1);
}

TEST_F(BSTTest, InsertExistingElementReturnsFalse) {
    EXPECT_FALSE(tree.insert(50));
}

TEST_F(BSTTest, SizeUnchangedAfterDuplicateInsertion) {
    size_t oldSize = tree.size();
    tree.insert(50);
    EXPECT_EQ(tree.size(), oldSize);
}

TEST_F(BSTTest, ContainsInsertedElement) {
    EXPECT_TRUE(tree.contains(50));
}

TEST_F(BSTTest, ContainsSecondElement) {
    EXPECT_TRUE(tree.contains(30));
}

TEST_F(BSTTest, ContainsLastElement) {
    EXPECT_TRUE(tree.contains(70));
}

TEST_F(BSTTest, DoesNotContainNonInsertedElement) {
    EXPECT_FALSE(tree.contains(10));
}

TEST_F(BSTTest, FindReturnsNonNullptrForExistingElement) {
    EXPECT_NE(tree.find(50), nullptr);
}

TEST_F(BSTTest, FindReturnsCorrectValueForExistingElement) {
    EXPECT_EQ(*(tree.find(50)), 50);
}

TEST_F(BSTTest, FindReturnsNullptrForNonExistingElement) {
    EXPECT_EQ(tree.find(10), nullptr);
}

TEST_F(BSTTest, RemoveLeafNodeReturnsTrue) {
    EXPECT_TRUE(tree.remove(20));
}

TEST_F(BSTTest, SizeDecreasesAfterRemoval) {
    size_t oldSize = tree.size();
    tree.remove(20);
    EXPECT_EQ(tree.size(), oldSize - 1);
}

TEST_F(BSTTest, RemovedElementNoLongerExists) {
    tree.remove(20);
    EXPECT_FALSE(tree.contains(20));
}

TEST_F(BSTTest, RemoveNodeWithOneChildReturnsTrue) {
    tree.insert(15);
    EXPECT_TRUE(tree.remove(20));
}

TEST_F(BSTTest, AfterRemovingNodeWithOneChildChildStillExists) {
    tree.insert(15);
    tree.remove(20);
    EXPECT_TRUE(tree.contains(15));
}

TEST_F(BSTTest, RemoveNodeWithTwoChildrenReturnsTrue) {
    EXPECT_TRUE(tree.remove(30));
}

TEST_F(BSTTest, AfterRemovingNodeWithTwoChildrenChildrenStillExist) {
    tree.remove(30);
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(40));
}

TEST_F(BSTTest, RemoveRootReturnsTrue) {
    EXPECT_TRUE(tree.remove(50));
}

TEST_F(BSTTest, AfterRemovingRootTreeIsStillValid) {
    tree.remove(50);
    EXPECT_TRUE(tree.contains(30));
    EXPECT_TRUE(tree.contains(70));
}

TEST_F(BSTTest, RemoveNonExistingElementReturnsFalse) {
    EXPECT_FALSE(tree.remove(100));
}

TEST_F(BSTTest, SizeUnchangedAfterFailedRemoval) {
    size_t oldSize = tree.size();
    tree.remove(100);
    EXPECT_EQ(tree.size(), oldSize);
}

TEST_F(BSTTest, ClearMakesTreeEmpty) {
    tree.clear();
    EXPECT_TRUE(tree.isEmpty());
}

TEST_F(BSTTest, ClearMakesSizeZero) {
    tree.clear();
    EXPECT_EQ(tree.size(), 0);
}

TEST_F(BSTTest, AfterClearElementsNoLongerExist) {
    tree.clear();
    EXPECT_FALSE(tree.contains(50));
}

TEST_F(BSTTest, CopyConstructorCreatesTreeOfSameSize) {
    TBinSearchTree<int> copy(tree);
    EXPECT_EQ(copy.size(), tree.size());
}

TEST_F(BSTTest, CopyConstructorCopiesAllElements) {
    TBinSearchTree<int> copy(tree);
    EXPECT_TRUE(copy.contains(50));
    EXPECT_TRUE(copy.contains(30));
    EXPECT_TRUE(copy.contains(70));
}

TEST_F(BSTTest, ModificationsDoNotAffectCopy) {
    TBinSearchTree<int> copy(tree);
    tree.remove(50);
    EXPECT_FALSE(tree.contains(50));
    EXPECT_TRUE(copy.contains(50));
}
