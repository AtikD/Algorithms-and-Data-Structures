// Copyright 2025 atikdd.t.me

#include <massive_sorted_table.h>
#include <gtest/gtest.h>
#include <string>

class MassiveSortedTableTest : public ::testing::Test {
 protected:
    TMassiveSortedTable<int, std::string> table;

    void SetUp() override {
        table.Insert(3, "Three");
        table.Insert(1, "One");
        table.Insert(2, "Two");
    }
};

TEST_F(MassiveSortedTableTest, InsertNewKeysReturnsTrue) {
    EXPECT_TRUE(table.Insert(4, "Four"));
    EXPECT_TRUE(table.Insert(5, "Five"));
}

TEST_F(MassiveSortedTableTest, InsertExistingKeyReturnsFalse) {
    EXPECT_FALSE(table.Insert(1, "Another One"));
    EXPECT_FALSE(table.Insert(2, "Another Two"));
}

TEST_F(MassiveSortedTableTest, FindExistingKeyReturnsValue) {
    EXPECT_EQ(table.Find(1), "One");
    EXPECT_EQ(table.Find(2), "Two");
    EXPECT_EQ(table.Find(3), "Three");
}

TEST_F(MassiveSortedTableTest, FindNonExistingKeyThrowsException) {
    EXPECT_THROW(table.Find(4), std::runtime_error);
    EXPECT_THROW(table.Find(99), std::runtime_error);
}

TEST_F(MassiveSortedTableTest, IsExistsReturnsTrueForExistingKeys) {
    EXPECT_TRUE(table.IsExists(1));
    EXPECT_TRUE(table.IsExists(2));
    EXPECT_TRUE(table.IsExists(3));
}

TEST_F(MassiveSortedTableTest, IsExistsReturnsFalseForNonExistingKeys) {
    EXPECT_FALSE(table.IsExists(4));
    EXPECT_FALSE(table.IsExists(99));
}

TEST_F(MassiveSortedTableTest, DeleteExistingKeyReturnsTrue) {
    EXPECT_TRUE(table.Delete(2));
    EXPECT_FALSE(table.IsExists(2));
    EXPECT_EQ(table.GetSize(), 2);
}

TEST_F(MassiveSortedTableTest, DeleteNonExistingKeyReturnsFalse) {
    EXPECT_FALSE(table.Delete(4));
    EXPECT_FALSE(table.Delete(99));
    EXPECT_EQ(table.GetSize(), 3);
}

TEST_F(MassiveSortedTableTest, GetSizeReturnsCorrectSize) {
    EXPECT_EQ(table.GetSize(), 3);
    table.Insert(4, "Four");
    EXPECT_EQ(table.GetSize(), 4);
    table.Delete(1);
    EXPECT_EQ(table.GetSize(), 3);
}

TEST_F(MassiveSortedTableTest, ClearEmptiesTheTable) {
    table.Clear();
    EXPECT_EQ(table.GetSize(), 0);
    EXPECT_FALSE(table.IsExists(1));
    EXPECT_FALSE(table.IsExists(2));
    EXPECT_FALSE(table.IsExists(3));
}

TEST_F(MassiveSortedTableTest, InsertAfterClearWorks) {
    table.Clear();
    EXPECT_TRUE(table.Insert(1, "One"));
    EXPECT_EQ(table.GetSize(), 1);
    EXPECT_TRUE(table.IsExists(1));
}

TEST_F(MassiveSortedTableTest, EmptyTableInitially) {
    TMassiveSortedTable<int, std::string> emptyTable;
    EXPECT_EQ(emptyTable.GetSize(), 0);
    EXPECT_FALSE(emptyTable.IsExists(1));
}

TEST_F(MassiveSortedTableTest, DeleteFromEmptyTableReturnsFalse) {
    TMassiveSortedTable<int, std::string> emptyTable;
    EXPECT_FALSE(emptyTable.Delete(1));
}

TEST_F(MassiveSortedTableTest, FindInEmptyTableThrowsException) {
    TMassiveSortedTable<int, std::string> emptyTable;
    EXPECT_THROW(emptyTable.Find(1), std::runtime_error);
}

TEST_F(MassiveSortedTableTest, ClearEmptyTableDoesNothing) {
    TMassiveSortedTable<int, std::string> emptyTable;
    emptyTable.Clear();
    EXPECT_EQ(emptyTable.GetSize(), 0);
}

TEST_F(MassiveSortedTableTest, InsertMaintainsSortOrder) {
    TMassiveSortedTable<int, std::string> orderedTable;

    orderedTable.Insert(5, "Five");
    orderedTable.Insert(3, "Three");
    orderedTable.Insert(1, "One");
    orderedTable.Insert(4, "Four");
    orderedTable.Insert(2, "Two");

    EXPECT_TRUE(orderedTable.IsExists(1));
    EXPECT_TRUE(orderedTable.IsExists(2));
    EXPECT_TRUE(orderedTable.IsExists(3));
    EXPECT_TRUE(orderedTable.IsExists(4));
    EXPECT_TRUE(orderedTable.IsExists(5));
}

TEST_F(MassiveSortedTableTest, BinarySearchWorksCorrectly) {
    // Проверяем, что бинарный поиск корректно работает
    // для существующих и несуществующих элементов
    TMassiveSortedTable<int, std::string> bigTable;

    for (int i = 0; i < 100; i += 2) {  // Только четные числа
        bigTable.Insert(i, std::to_string(i));
    }

    for (int i = 0; i < 100; i += 2) {
        EXPECT_TRUE(bigTable.IsExists(i));
        EXPECT_EQ(bigTable.Find(i), std::to_string(i));
    }

    for (int i = 1; i < 100; i += 2) {
        EXPECT_FALSE(bigTable.IsExists(i));
    }
}
