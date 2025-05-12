// Copyright 2025 atikdd.ru

#include <gtest/gtest.h>
#include <bst_table.h>
#include <string>

class BSTTableTest : public ::testing::Test {
 protected:
    TBSTTable<int, std::string> table;

    void SetUp() override {
        table.Insert(3, "Three");
        table.Insert(1, "One");
        table.Insert(2, "Two");
    }
};

TEST_F(BSTTableTest, InsertNewKeysReturnsTrue) {
    EXPECT_TRUE(table.Insert(4, "Four"));
    EXPECT_TRUE(table.Insert(5, "Five"));
}

TEST_F(BSTTableTest, InsertExistingKeyReturnsFalse) {
    EXPECT_FALSE(table.Insert(1, "Another One"));
    EXPECT_FALSE(table.Insert(2, "Another Two"));
}

TEST_F(BSTTableTest, FindExistingKeyReturnsValue) {
    EXPECT_EQ(table.Find(1), "One");
    EXPECT_EQ(table.Find(2), "Two");
    EXPECT_EQ(table.Find(3), "Three");
}

TEST_F(BSTTableTest, FindNonExistingKeyThrowsException) {
    EXPECT_THROW(table.Find(4), std::runtime_error);
    EXPECT_THROW(table.Find(99), std::runtime_error);
}

TEST_F(BSTTableTest, IsExistsReturnsTrueForExistingKeys) {
    EXPECT_TRUE(table.IsExists(1));
    EXPECT_TRUE(table.IsExists(2));
    EXPECT_TRUE(table.IsExists(3));
}

TEST_F(BSTTableTest, IsExistsReturnsFalseForNonExistingKeys) {
    EXPECT_FALSE(table.IsExists(4));
    EXPECT_FALSE(table.IsExists(99));
}

TEST_F(BSTTableTest, DeleteExistingKeyReturnsTrue) {
    EXPECT_TRUE(table.Delete(2));
    EXPECT_FALSE(table.IsExists(2));
    EXPECT_EQ(table.GetSize(), 2);
}

TEST_F(BSTTableTest, DeleteNonExistingKeyReturnsFalse) {
    EXPECT_FALSE(table.Delete(4));
    EXPECT_FALSE(table.Delete(99));
    EXPECT_EQ(table.GetSize(), 3);
}

TEST_F(BSTTableTest, GetSizeReturnsCorrectSize) {
    EXPECT_EQ(table.GetSize(), 3);
    table.Insert(4, "Four");
    EXPECT_EQ(table.GetSize(), 4);
    table.Delete(1);
    EXPECT_EQ(table.GetSize(), 3);
}

TEST_F(BSTTableTest, ClearEmptiesTheTable) {
    table.Clear();
    EXPECT_EQ(table.GetSize(), 0);
    EXPECT_FALSE(table.IsExists(1));
    EXPECT_FALSE(table.IsExists(2));
    EXPECT_FALSE(table.IsExists(3));
}

TEST_F(BSTTableTest, InsertAfterClearWorks) {
    table.Clear();
    EXPECT_TRUE(table.Insert(1, "One"));
    EXPECT_EQ(table.GetSize(), 1);
    EXPECT_TRUE(table.IsExists(1));
}

TEST_F(BSTTableTest, EmptyTableInitially) {
    TBSTTable<int, std::string> emptyTable;
    EXPECT_EQ(emptyTable.GetSize(), 0);
    EXPECT_FALSE(emptyTable.IsExists(1));
}

TEST_F(BSTTableTest, DeleteFromEmptyTableReturnsFalse) {
    TBSTTable<int, std::string> emptyTable;
    EXPECT_FALSE(emptyTable.Delete(1));
}

TEST_F(BSTTableTest, FindInEmptyTableThrowsException) {
    TBSTTable<int, std::string> emptyTable;
    EXPECT_THROW(emptyTable.Find(1), std::runtime_error);
}

TEST_F(BSTTableTest, ClearEmptyTableDoesNothing) {
    TBSTTable<int, std::string> emptyTable;
    emptyTable.Clear();
    EXPECT_EQ(emptyTable.GetSize(), 0);
}

TEST_F(BSTTableTest, BSTOrdering) {
    TBSTTable<int, std::string> orderedTable;

    orderedTable.Insert(5, "Five");
    orderedTable.Insert(3, "Three");
    orderedTable.Insert(7, "Seven");
    orderedTable.Insert(1, "One");
    orderedTable.Insert(4, "Four");
    orderedTable.Insert(6, "Six");
    orderedTable.Insert(8, "Eight");

    EXPECT_TRUE(orderedTable.IsExists(1));
    EXPECT_TRUE(orderedTable.IsExists(3));
    EXPECT_TRUE(orderedTable.IsExists(4));
    EXPECT_TRUE(orderedTable.IsExists(5));
    EXPECT_TRUE(orderedTable.IsExists(6));
    EXPECT_TRUE(orderedTable.IsExists(7));
    EXPECT_TRUE(orderedTable.IsExists(8));
    
    EXPECT_EQ(orderedTable.GetSize(), 7);
}

TEST_F(BSTTableTest, LargeDataSet) {
    TBSTTable<int, std::string> bigTable;

    for (int i = 0; i < 1000; ++i) {
        bigTable.Insert(i, std::to_string(i));
    }

    EXPECT_EQ(bigTable.GetSize(), 1000);

    EXPECT_EQ(bigTable.Find(0), "0");
    EXPECT_EQ(bigTable.Find(500), "500");
    EXPECT_EQ(bigTable.Find(999), "999");

    EXPECT_TRUE(bigTable.Delete(250));
    EXPECT_TRUE(bigTable.Delete(750));
    EXPECT_FALSE(bigTable.IsExists(250));
    EXPECT_FALSE(bigTable.IsExists(750));
    
    EXPECT_EQ(bigTable.GetSize(), 998);
}

TEST_F(BSTTableTest, WorstCaseLinearInsertion) {
    TBSTTable<int, std::string> linearTable;

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(linearTable.Insert(i, std::to_string(i)));
    }

    EXPECT_EQ(linearTable.GetSize(), 100);

    EXPECT_EQ(linearTable.Find(0), "0");
    EXPECT_EQ(linearTable.Find(50), "50");
    EXPECT_EQ(linearTable.Find(99), "99");
}

TEST_F(BSTTableTest, StringKeysAndIntValues) {
    TBSTTable<std::string, int> stringTable;

    EXPECT_TRUE(stringTable.Insert("alpha", 1));
    EXPECT_TRUE(stringTable.Insert("beta", 2));
    EXPECT_TRUE(stringTable.Insert("gamma", 3));

    EXPECT_EQ(stringTable.Find("alpha"), 1);
    EXPECT_EQ(stringTable.Find("beta"), 2);
    EXPECT_EQ(stringTable.Find("gamma"), 3);

    EXPECT_TRUE(stringTable.Delete("beta"));
    EXPECT_EQ(stringTable.GetSize(), 2);
}
