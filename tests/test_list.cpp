// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include <list.h>
#include <algorithm>

TEST(TListTest, Constructor_CreatesEmptyList) {
    TList<int> list;
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, IsEmpty_ReturnsFalse) {
    TList<int> list;
    list.push_back(1);
    EXPECT_FALSE(list.isEmpty());
}

TEST(TListTest, PushBack) {
    TList<int> list;
    list.push_back(10);
    EXPECT_EQ(list.find(10)->getValue(), 10);
}

TEST(TListTest, PushFront) {
    TList<int> list;
    list.push_front(5);
    EXPECT_EQ(list.find(5)->getValue(), 5);
}

TEST(TListTest, InsertAt_PositionZero) {
    TList<int> list;
    list.push_back(1);
    list.insert_at(0, 0);
    EXPECT_EQ(list.front(), 0);
}

TEST(TListTest, InsertAt_InsertsAtCorrectPosition) {
    TList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert_at(1, 2);
    TNode<int>* node = list.getNodeAt(1);
    EXPECT_EQ(node->getValue(), 2);
}

TEST(TListTest, InsertAt_ThrowsException_WhenPositionOutOfRange) {
    TList<int> list;
    list.push_back(1);
    EXPECT_THROW(list.insert_at(5, 2), std::out_of_range);
}

TEST(TListTest, Find_ReturnsNode_WhenValueExists) {
    TList<int> list;
    list.push_back(10);
    TNode<int>* node = list.find(10);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->getValue(), 10);
}

TEST(TListTest, Find_ReturnsNullptr_WhenValueNotFound) {
    TList<int> list;
    list.push_back(10);
    TNode<int>* node = list.find(20);
    EXPECT_EQ(node, nullptr);
}

TEST(TListTest, PopBack_Successful) {
    TList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();
    EXPECT_EQ(list.find(20), nullptr);
}

TEST(TListTest, PopBack_OneElementList) {
    TList<int> list;
    list.push_back(10);
    list.pop_back();
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, PopBack_ThrowsException_WhenListIsEmpty) {
    TList<int> list;
    EXPECT_THROW(list.pop_back(), std::out_of_range);
}

TEST(TListTest, PopFront_RemovesFirstElement) {
    TList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_front();
    EXPECT_EQ(list.find(10), nullptr);
}

TEST(TListTest, PopFront_ThrowsException_WhenListIsEmpty) {
    TList<int> list;
    EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(TListTest, RemoveAt_RemovesElementAtPosition) {
    TList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.remove_at(1);
    EXPECT_EQ(list.find(20), nullptr);
}

TEST(TListTest, RemoveAt_ThrowsException_WhenPositionOutOfRange) {
    TList<int> list;
    list.push_back(10);
    EXPECT_THROW(list.remove_at(5), std::out_of_range);
}

TEST(TListTest, ReplaceAt_ReplacesValueAtPosition) {
    TList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.replace_at(1, 30);
    EXPECT_EQ(list.find(30)->getValue(), 30);
}

TEST(TListTest, ReplaceAt_ThrowsException_WhenPositionOutOfRange) {
    TList<int> list;
    EXPECT_THROW(list.replace_at(2, 30), std::out_of_range);
}

TEST(TListTest, CopyConstructor_CreatesCorrectCopy) {
    TList<int> original;
    original.push_back(10);
    original.push_back(20);
    TList<int> copy(original);
    EXPECT_EQ(copy.find(10)->getValue(), 10);
    EXPECT_EQ(copy.find(20)->getValue(), 20);
}

TEST(TListTest, Remove_DeletesSpecifiedNode) {
    TList<int> list;
    list.push_back(10);
    list.push_back(20);
    TNode<int>* node = list.find(10);
    list.remove(node);
    EXPECT_EQ(list.find(10), nullptr);
}

TEST(TListTest, Remove_ThrowsException_WhenNodeIsNullptr) {
    TList<int> list;
    EXPECT_THROW(list.remove(nullptr), std::invalid_argument);
}

TEST(TListTest, Replace_UpdatesNodeValue) {
    TList<int> list;
    list.push_back(10);
    TNode<int>* node = list.find(10);
    list.replace(node, 20);
    EXPECT_EQ(node->getValue(), 20);
}

TEST(TListTest, Replace_ThrowsException_WhenNodeIsNullptr) {
    TList<int> list;
    EXPECT_THROW(list.replace(nullptr, 20), std::invalid_argument);
}
