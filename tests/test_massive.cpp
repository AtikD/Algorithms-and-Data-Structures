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

TEST(TMassiveTest, RemoveAllOccurrences) {
    TMassive<int> massive;
    // Заполняем архив значениями
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(10);
    massive.push_back(30);
    massive.push_back(10);

    // Удаляем все вхождения 10
    massive.remove_all(10);

    EXPECT_EQ(massive.size(), 2);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "20, 30, ");
}

TEST(TMassiveTest, RemoveFirstOccurrence) {
    TMassive<int> massive;
    // Заполняем архив значениями
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(10);
    massive.push_back(30);

    // Удаляем первое вхождение 10
    massive.remove_first(10);

    EXPECT_EQ(massive.size(), 3);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "20, 10, 30, ");

    massive.remove_first(10);
    std::stringstream ss2;
    massive.print(ss2);
    EXPECT_EQ(ss2.str(), "20, 30, ");
    // Проверяем удаление значения, которого нет
    EXPECT_THROW(massive.remove_first(40), std::logic_error);
}

TEST(TMassiveTest, RemoveLastOccurrence) {
    TMassive<int> massive;
    // Заполняем архив значениями
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(10);
    massive.push_back(30);

    // Удаляем последнее вхождение 10
    massive.remove_last(10);

    EXPECT_EQ(massive.size(), 3);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 20, 30, ");

    // Проверяем удаление значения, которого нет
    EXPECT_THROW(massive.remove_last(40), std::logic_error);
}

TEST(TMassiveTest, RemoveByIndex) {
    TMassive<int> massive;
    // Заполняем архив значениями
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(30);

    // Удаляем элемент по индексу 1 (значение 20)
    massive.remove_by_index(1);

    EXPECT_EQ(massive.size(), 2);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 30, ");

    // Попытка удалить по некорректному индексу
    EXPECT_THROW(massive.remove_by_index(5), std::out_of_range);
}

TEST(TMassiveTest, SwapMethod) {
    TMassive<int> massive1;
    TMassive<int> massive2;

    massive1.push_back(10);
    massive1.push_back(20);

    massive2.push_back(30);
    massive2.push_back(40);
    massive2.push_back(50);

    // Выполняем обмен
    massive1.swap(massive2);

    // Проверяем содержимое massive1
    std::stringstream ss1;
    massive1.print(ss1);
    EXPECT_EQ(ss1.str(), "30, 40, 50, ");

    // Проверяем содержимое massive2
    std::stringstream ss2;
    massive2.print(ss2);
    EXPECT_EQ(ss2.str(), "10, 20, ");
}

TEST(TMassiveTest, AssignMethod) {
    TMassive<int> massive1;
    TMassive<int> massive2;

    massive1.push_back(10);
    massive1.push_back(20);

    massive2.push_back(30);
    massive2.push_back(40);
    massive2.push_back(50);

    // Присваиваем massive1 содержимое massive2
    massive1.assign(massive2);

    // Проверяем содержимое massive1
    std::stringstream ss1;
    massive1.print(ss1);
    EXPECT_EQ(ss1.str(), "30, 40, 50, ");

    // Проверяем, что massive2 не изменился
    std::stringstream ss2;
    massive2.print(ss2);
    EXPECT_EQ(ss2.str(), "30, 40, 50, ");
}
