// Copyright 2025 atikdd.t.me.

#include <massive_unsorted_table.h>
#include <gtest/gtest.h>
#include <string>

class MassiveUnsortedTableTest : public ::testing::Test {
 protected:
    TMassiveUnsortedTable<int, std::string> table;

    void SetUp() override {
        table.Insert(1, "One");
        table.Insert(2, "Two");
        table.Insert(3, "Three");
    }
};

TEST_F(MassiveUnsortedTableTest, InsertNewKeysReturnsTrue) {
    EXPECT_TRUE(table.Insert(4, "Four"));
    EXPECT_TRUE(table.Insert(5, "Five"));
}

TEST_F(MassiveUnsortedTableTest, InsertExistingKey) {
    EXPECT_THROW(table.Insert(1, "Another One"), std::invalid_argument);
    EXPECT_THROW(table.Insert(2, "Another Two"), std::invalid_argument);
}

TEST_F(MassiveUnsortedTableTest, FindExistingKeyReturnsValue) {
    EXPECT_EQ(table.Find(1), "One");
    EXPECT_EQ(table.Find(2), "Two");
    EXPECT_EQ(table.Find(3), "Three");
}

TEST_F(MassiveUnsortedTableTest, FindNonExistingKeyThrowsException) {
    EXPECT_THROW(table.Find(4), std::out_of_range);
    EXPECT_THROW(table.Find(99), std::out_of_range);
}

TEST_F(MassiveUnsortedTableTest, IsExistsReturnsTrueForExistingKeys) {
    EXPECT_TRUE(table.IsExists(1));
    EXPECT_TRUE(table.IsExists(2));
    EXPECT_TRUE(table.IsExists(3));
}

TEST_F(MassiveUnsortedTableTest, IsExistsReturnsFalseForNonExistingKeys) {
    EXPECT_FALSE(table.IsExists(4));
    EXPECT_FALSE(table.IsExists(99));
}

TEST_F(MassiveUnsortedTableTest, DeleteExistingKeyReturnsTrue) {
    EXPECT_TRUE(table.Delete(2));
    EXPECT_FALSE(table.IsExists(2));
    EXPECT_EQ(table.GetSize(), 2);
}

TEST_F(MassiveUnsortedTableTest, DeleteNonExistingKeyReturnsFalse) {
    EXPECT_THROW(table.Delete(4), std::out_of_range);
    EXPECT_THROW(table.Delete(99), std::out_of_range);
    EXPECT_EQ(table.GetSize(), 3);
}

TEST_F(MassiveUnsortedTableTest, GetSizeReturnsCorrectSize) {
    EXPECT_EQ(table.GetSize(), 3);
    table.Insert(4, "Four");
    EXPECT_EQ(table.GetSize(), 4);
    table.Delete(1);
    EXPECT_EQ(table.GetSize(), 3);
}

TEST_F(MassiveUnsortedTableTest, ClearEmptiesTheTable) {
    table.Clear();
    EXPECT_EQ(table.GetSize(), 0);
    EXPECT_FALSE(table.IsExists(1));
    EXPECT_FALSE(table.IsExists(2));
    EXPECT_FALSE(table.IsExists(3));
}

TEST_F(MassiveUnsortedTableTest, InsertAfterClearWorks) {
    table.Clear();
    EXPECT_TRUE(table.Insert(1, "One"));
    EXPECT_EQ(table.GetSize(), 1);
    EXPECT_TRUE(table.IsExists(1));
}

TEST_F(MassiveUnsortedTableTest, EmptyTableInitially) {
    TMassiveUnsortedTable<int, std::string> emptyTable;
    EXPECT_EQ(emptyTable.GetSize(), 0);
    EXPECT_FALSE(emptyTable.IsExists(1));
}

TEST_F(MassiveUnsortedTableTest, DeleteFromEmptyTableReturnsFalse) {
    TMassiveUnsortedTable<int, std::string> emptyTable;
    EXPECT_THROW(emptyTable.Delete(1), std::out_of_range);
}

TEST_F(MassiveUnsortedTableTest, FindInEmptyTableThrowsException) {
    TMassiveUnsortedTable<int, std::string> emptyTable;
    EXPECT_THROW(emptyTable.Find(1), std::out_of_range);
}

TEST_F(MassiveUnsortedTableTest, ClearEmptyTableDoesNothing) {
    TMassiveUnsortedTable<int, std::string> emptyTable;
    emptyTable.Clear();
    EXPECT_EQ(emptyTable.GetSize(), 0);
}
