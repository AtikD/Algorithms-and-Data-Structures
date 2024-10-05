// Copyright 2024 atikdd.t.me


#include <gtest/gtest.h>
#include "../lib_massive/massive.h"

TEST(TMassiveTest, InsertSingleValue) {
    TMassive<int> massive;
    massive.insert(10, 0);
    EXPECT_FALSE(massive.empty());
    massive.insert(20, 1);
    massive.insert(15, 1);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 15, 20, ");
}

TEST(TMassiveTest, EraseMultipleValues) {
    TMassive<int> massive;
    // Заполняем архив значениями
    for (int i = 0; i < 10; ++i) {
        massive.push_back(i);
    }
    EXPECT_EQ(massive.size(), 10);

    // Удаляем 3 элемента, начиная с позиции 2
    massive.erase(2, 3);
    EXPECT_EQ(massive.size(), 7);

    // Проверяем оставшиеся элементы
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "0, 1, 5, 6, 7, 8, 9, ");

    // Удаляем элементы, когда `pos + n` превышает размер
    massive.erase(5, 10);
    EXPECT_EQ(massive.size(), 5);
    ss.str("");
    massive.print(ss);
    EXPECT_EQ(ss.str(), "0, 1, 5, 6, 7, ");

    // Попытка удалить с позиции, выходящей за пределы
    EXPECT_THROW(massive.erase(10, 1), std::out_of_range);

    // Удаление 0 элементов
    massive.erase(0, 0);
    EXPECT_EQ(massive.size(), 5);
}

TEST(TMassiveTest, Clearmassive) {
    TMassive<int> massive;
    massive.insert(10, 0);
    massive.insert(20, 1);
    massive.clear();
    EXPECT_TRUE(massive.empty());
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "");
}
