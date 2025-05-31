// Copyright 2025 atikdd.t.me

#include <gtest/gtest.h>
#include <hash_chained.h>
#include <massive.h>
#include <pair.h>
#include <string>

class HashTableChainedTest : public ::testing::Test {
 protected:
    THashTableChained<int, std::string> table;

    void SetUp() override {
        table.Insert(1, "One");
        table.Insert(2, "Two");
        table.Insert(3, "Three");
    }
};

TEST_F(HashTableChainedTest, InsertNewKeysReturnsTrue) {
    EXPECT_TRUE(table.Insert(4, "Four"));
    EXPECT_TRUE(table.Insert(5, "Five"));
}

TEST_F(HashTableChainedTest, InsertExistingKeyThrows) {
    EXPECT_THROW(table.Insert(1, "Another One"), std::logic_error);
    EXPECT_THROW(table.Insert(2, "Another Two"), std::logic_error);
}

TEST_F(HashTableChainedTest, FindExistingKeyReturnsValue) {
    EXPECT_EQ(table.Find(1), "One");
    EXPECT_EQ(table.Find(2), "Two");
    EXPECT_EQ(table.Find(3), "Three");
}

TEST_F(HashTableChainedTest, FindNonExistingKeyThrows) {
    EXPECT_THROW(table.Find(4), std::out_of_range);
    EXPECT_THROW(table.Find(99), std::out_of_range);
}

TEST_F(HashTableChainedTest, DeleteExistingKeyReturnsTrue) {
    EXPECT_TRUE(table.Delete(2));
    EXPECT_THROW(table.Find(2), std::out_of_range);
    EXPECT_EQ(table.count(), 2);
}

TEST_F(HashTableChainedTest, DeleteNonExistingKeyThrows) {
    EXPECT_THROW(table.Delete(4), std::out_of_range);
}

TEST_F(HashTableChainedTest, countReturnsCorrectSize) {
    EXPECT_EQ(table.count(), 3);
    table.Insert(4, "Four");
    EXPECT_EQ(table.count(), 4);
    table.Delete(1);
    EXPECT_EQ(table.count(), 3);
}

TEST_F(HashTableChainedTest, ClearEmptiesTheTable) {
    table.Clear();
    EXPECT_EQ(table.count(), 0);
}

TEST_F(HashTableChainedTest, InsertAfterClearWorks) {
    table.Clear();
    EXPECT_TRUE(table.Insert(1, "One"));
    EXPECT_EQ(table.count(), 1);
    EXPECT_NO_THROW(table.Find(1));
}

TEST_F(HashTableChainedTest, EmptyTableInitially) {
    THashTableChained<int, std::string> emptyTable;
    EXPECT_EQ(emptyTable.count(), 0);
}

TEST_F(HashTableChainedTest, ConstructorWithSize) {
    THashTableChained<int, std::string> sizedTable(200);
    EXPECT_EQ(sizedTable.count(), 0);
    sizedTable.Insert(1, "One");
    EXPECT_EQ(sizedTable.count(), 1);
    EXPECT_NO_THROW(sizedTable.Find(1));
}

TEST_F(HashTableChainedTest, ConstructorWithInvalidSize) {
    THashTableChained<int, std::string> empty(0);
    EXPECT_EQ(empty.size(), 101);
}

TEST_F(HashTableChainedTest, ConstructorWithNegativeSize) {
    THashTableChained<int, std::string> negative_size(-5);
    EXPECT_EQ(negative_size.size(), 101);
}

TEST_F(HashTableChainedTest, CopyConstructor) {
    THashTableChained<int, std::string> copyT(table);
    EXPECT_EQ(copyT.count(), 3);
    EXPECT_NO_THROW(copyT.Find(1));
    EXPECT_NO_THROW(copyT.Find(2));
    EXPECT_NO_THROW(copyT.Find(3));
    EXPECT_EQ(copyT.Find(1), "One");
}

TEST_F(HashTableChainedTest, HandleCollisions) {
    THashTableChained<std::string, std::string> smallTable(20);

    smallTable.Insert("ned", "One");
    smallTable.Insert("pol", "Six");

    EXPECT_EQ(smallTable.count(), 2);
    EXPECT_EQ(smallTable.Find("ned"), "One");
    EXPECT_EQ(smallTable.Find("pol"), "Six");
}

TEST_F(HashTableChainedTest, StringKeysWork) {
    THashTableChained<std::string, int> stringTable;

    stringTable.Insert("one", 1);
    stringTable.Insert("two", 2);
    stringTable.Insert("three", 3);

    EXPECT_EQ(stringTable.count(), 3);
    EXPECT_NO_THROW(stringTable.Find("one"));
    EXPECT_NO_THROW(stringTable.Find("two"));
    EXPECT_NO_THROW(stringTable.Find("three"));
    EXPECT_EQ(stringTable.Find("one"), 1);
    EXPECT_EQ(stringTable.Find("two"), 2);
    EXPECT_EQ(stringTable.Find("three"), 3);
}

TEST_F(HashTableChainedTest, DeletedKeyCanBeReinserted) {
    table.Delete(2);
    EXPECT_THROW(table.Find(2), std::out_of_range);

    EXPECT_TRUE(table.Insert(2, "New Two"));
    EXPECT_EQ(table.Find(2), "New Two");
}

TEST_F(HashTableChainedTest, InsertManyElements) {
    THashTableChained<int, int> largeTable(50);

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(largeTable.Insert(i, i * 10));
    }

    EXPECT_EQ(largeTable.count(), 100);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(largeTable.Find(i), i * 10);
    }
}

TEST_F(HashTableChainedTest, MergeSuccesful) {
    THashTableChained<std::string, int> hashOp1;
    hashOp1.Insert("lampshade", 1);
    hashOp1.Insert("cinema", 2);
    hashOp1.Insert("airplane", 3);
    hashOp1.Insert("person", 4);

    THashTableChained<std::string, int> hashOp2;
    hashOp2.Insert("cinema", 15);
    hashOp2.Insert("music", 16);
    hashOp2.Insert("airplane", 17);

    EXPECT_TRUE(hashOp1.Insert(hashOp2));
    EXPECT_EQ(hashOp1.Find("lampshade"), 1);
    EXPECT_EQ(hashOp1.Find("cinema"), 2);
    EXPECT_EQ(hashOp1.Find("airplane"), 3);
    EXPECT_EQ(hashOp1.Find("person"), 4);
    EXPECT_EQ(hashOp1.Find("music"), 16);
}
