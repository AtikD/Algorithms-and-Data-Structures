// Copyright 2025 atikdd.t.me

#include <gtest/gtest.h>
#include <unsorted_table.h>
#include <string>

class UnsortedTableTest : public ::testing::Test {
 protected:
    TUnsortedTable<int, std::string> table;

    void SetUp() override {
        table.Insert(1, "One");
        table.Insert(2, "Two");
        table.Insert(3, "Three");
    }
};

TEST_F(UnsortedTableTest, InsertNewKeysReturnsTrue) {
    EXPECT_TRUE(table.Insert(4, "Four"));
    EXPECT_TRUE(table.Insert(5, "Five"));
}

TEST_F(UnsortedTableTest, InsertExistingKeyReturnsFalse) {
    EXPECT_FALSE(table.Insert(1, "Another One"));
    EXPECT_FALSE(table.Insert(2, "Another Two"));
}

TEST_F(UnsortedTableTest, FindExistingKeyReturnsValue) {
    EXPECT_EQ(table.Find(1), "One");
    EXPECT_EQ(table.Find(2), "Two");
    EXPECT_EQ(table.Find(3), "Three");
}

TEST_F(UnsortedTableTest, FindNonExistingKeyThrowsException) {
    EXPECT_THROW(table.Find(4), std::runtime_error);
    EXPECT_THROW(table.Find(99), std::runtime_error);
}

TEST_F(UnsortedTableTest, IsExistsReturnsTrueForExistingKeys) {
    EXPECT_TRUE(table.IsExists(1));
    EXPECT_TRUE(table.IsExists(2));
    EXPECT_TRUE(table.IsExists(3));
}

TEST_F(UnsortedTableTest, IsExistsReturnsFalseForNonExistingKeys) {
    EXPECT_FALSE(table.IsExists(4));
    EXPECT_FALSE(table.IsExists(99));
}

TEST_F(UnsortedTableTest, DeleteExistingKeyReturnsTrue) {
    EXPECT_TRUE(table.Delete(2));
    EXPECT_FALSE(table.IsExists(2));
    EXPECT_EQ(table.GetSize(), 2);
}

TEST_F(UnsortedTableTest, DeleteNonExistingKeyReturnsFalse) {
    EXPECT_FALSE(table.Delete(4));
    EXPECT_FALSE(table.Delete(99));
    EXPECT_EQ(table.GetSize(), 3);
}

TEST_F(UnsortedTableTest, GetSizeReturnsCorrectSize) {
    EXPECT_EQ(table.GetSize(), 3);
    table.Insert(4, "Four");
    EXPECT_EQ(table.GetSize(), 4);
    table.Delete(1);
    EXPECT_EQ(table.GetSize(), 3);
}

TEST_F(UnsortedTableTest, ClearEmptiesTheTable) {
    table.Clear();
    EXPECT_EQ(table.GetSize(), 0);
    EXPECT_FALSE(table.IsExists(1));
    EXPECT_FALSE(table.IsExists(2));
    EXPECT_FALSE(table.IsExists(3));
}

TEST_F(UnsortedTableTest, InsertAfterClearWorks) {
    table.Clear();
    EXPECT_TRUE(table.Insert(1, "One"));
    EXPECT_EQ(table.GetSize(), 1);
    EXPECT_TRUE(table.IsExists(1));
}

TEST_F(UnsortedTableTest, EmptyTableInitially) {
    TUnsortedTable<int, std::string> emptyTable;
    EXPECT_EQ(emptyTable.GetSize(), 0);
    EXPECT_FALSE(emptyTable.IsExists(1));
}

TEST_F(UnsortedTableTest, DeleteFromEmptyTableReturnsFalse) {
    TUnsortedTable<int, std::string> emptyTable;
    EXPECT_FALSE(emptyTable.Delete(1));
}

TEST_F(UnsortedTableTest, FindInEmptyTableThrowsException) {
    TUnsortedTable<int, std::string> emptyTable;
    EXPECT_THROW(emptyTable.Find(1), std::runtime_error);
}

TEST_F(UnsortedTableTest, ClearEmptyTableDoesNothing) {
    TUnsortedTable<int, std::string> emptyTable;
    emptyTable.Clear();
    EXPECT_EQ(emptyTable.GetSize(), 0);
}

// Тесты для различных типов данных
TEST(UnsortedTableTypesTest, StringKeys) {
    TUnsortedTable<std::string, int> table;
    EXPECT_TRUE(table.Insert("one", 1));
    EXPECT_TRUE(table.Insert("two", 2));
    EXPECT_EQ(table.Find("one"), 1);
    EXPECT_TRUE(table.Delete("one"));
    EXPECT_FALSE(table.IsExists("one"));
}

TEST(UnsortedTableTypesTest, NonTrivialValues) {
    class TestValue {
     public:
        int id;
        std::string name;

        TestValue() : id(0), name("") {}
        TestValue(int i, const std::string& n) : id(i), name(n) {}

        bool operator==(const TestValue& other) const {
            return id == other.id && name == other.name;
        }
    };

    TUnsortedTable<int, TestValue> table;
    EXPECT_TRUE(table.Insert(1, TestValue(1, "test1")));
    EXPECT_TRUE(table.Insert(2, TestValue(2, "test2")));

    TestValue val = table.Find(1);
    EXPECT_EQ(val.id, 1);
    EXPECT_EQ(val.name, "test1");
}
