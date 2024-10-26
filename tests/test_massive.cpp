// Copyright 2024 atikdd.t.me


#include <gtest/gtest.h>
#include <utility>
#include <algorithm>
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

TEST(TMassiveTest, DefaultConstructor) {
    TMassive<int> massive;
    EXPECT_EQ(massive.size(), 0);
    EXPECT_EQ(massive.capacity(), STEP_CAPACITY);
    EXPECT_TRUE(massive.empty());
}

TEST(TMassiveTest, CopyConstructor) {
    TMassive<int> original;
    original.push_back(1);
    original.push_back(2);

    TMassive<int> copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
}

TEST(TMassiveTest, MoveConstructor) {
    TMassive<int> original;
    original.push_back(1);
    original.push_back(2);

    TMassive<int> moved(std::move(original));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(original.size(), 0);
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

    // Удаление 0 элементов
    massive.erase(0, 0);
    EXPECT_EQ(massive.size(), 5);
}

TEST(TMassiveTest, ClearMassive) {
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

TEST(TMassiveTest, ResizeMethod) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(30);

    // Увеличиваем размер до 5, заполняя значением 0
    massive.resize(5, 0);
    EXPECT_EQ(massive.size(), 5);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 20, 30, 0, 0, ");

    // Уменьшаем размер до 2
    massive.resize(2, 0);
    EXPECT_EQ(massive.size(), 2);
    ss.str("");
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 20, ");
}

TEST(TMassiveTest, PushFrontMethod) {
    TMassive<int> massive;
    massive.push_back(20);
    massive.push_back(30);

    massive.push_front(10);

    EXPECT_EQ(massive.size(), 3);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 20, 30, ");
}

TEST(TMassiveTest, PopFrontMethod) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(30);

    massive.pop_front();

    EXPECT_EQ(massive.size(), 2);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "20, 30, ");

    // Проверяем исключение при попытке удалить из пустого архива
    massive.pop_front();
    massive.pop_front();
    EXPECT_THROW(massive.pop_front(), std::out_of_range);
}

TEST(TMassiveTest, InsertArrayMethod) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(40);

    int arr[] = {20, 30};

    // Вставляем массив из 2 элементов на позицию 1
    massive.insert(arr, 2, 1);

    EXPECT_EQ(massive.size(), 4);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 20, 30, 40, ");
}

TEST(TMassiveTest, FindLastMethod_ValueInArchive) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(10);
    massive.push_back(30);

    size_t index = massive.find_last(10);
    EXPECT_EQ(index, 2);
}

TEST(TMassiveTest, PopBackMethod) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(30);

    massive.pop_back();

    EXPECT_EQ(massive.size(), 2);
    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 20, ");
}

TEST(TMassiveTest, ReplaceMethod) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(30);

    // Заменяем значение на позиции 1
    massive.replace(1, 25);

    std::stringstream ss;
    massive.print(ss);
    EXPECT_EQ(ss.str(), "10, 25, 30, ");
}

TEST(TMassiveTest, FindFirstMethod_ValueInArchive) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(10);
    massive.push_back(30);

    size_t index = massive.find_first(10);
    EXPECT_EQ(index, 0);

    index = massive.find_first(20);
    EXPECT_EQ(index, 1);
}

TEST(TMassiveTest, FindAllMethod) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(10);
    massive.push_back(30);
    massive.push_back(10);

    size_t count = 0;
    size_t* indices = massive.find_all(10);

    EXPECT_EQ(indices[0], 3);
    ASSERT_NE(indices, nullptr);
    EXPECT_EQ(indices[1], 0);
    EXPECT_EQ(indices[2], 2);
    EXPECT_EQ(indices[3], 4);

    delete[] indices;

    // Проверка для значения, которого нет
    indices = massive.find_all(40);
    EXPECT_EQ(indices, nullptr);
}

TEST(TMassiveTest, AccessOperator) {
    TMassive<int> massive;
    massive.push_back(12);
    massive.push_back(20);
    massive.push_back(17);
    massive.push_back(30);
    massive.push_back(14);

    EXPECT_EQ(massive[3], 30);
}

TEST(TMassiveTest, AccessOperatorOutOfRange) {
    TMassive<int> massive;
    massive.push_back(12);
    massive.push_back(20);
    massive.push_back(17);
    massive.push_back(30);
    massive.push_back(14);

    EXPECT_THROW(massive[100], std::out_of_range);
}

TEST(TMassiveTest, AccessOperatorNotValid) {
    TMassive<int> massive;
    EXPECT_THROW(massive[0], std::logic_error);
}

TEST(TMassiveTest, PopBackMethodEmptyMassive) {
    TMassive<int> massive;
    EXPECT_THROW(massive.pop_back(), std::out_of_range);
}

TEST(TMassiveTest, PopFrontMethodEmptyMassive) {
    TMassive<int> massive;
    EXPECT_THROW(massive.pop_front(), std::out_of_range);
}

TEST(TMassiveTest, InsertArrayMethodOutOfRange) {
    TMassive<int> massive;
    int arr[] = {20, 30};

    EXPECT_THROW(massive.insert(arr, 2, 10), std::out_of_range);
}

TEST(TMassiveTest, InsertSingleValueOutOfRange) {
    TMassive<int> massive;
    EXPECT_THROW(massive.insert(10, 10), std::out_of_range);
}

TEST(TMassiveTest, ReplaceMethodOutOfRange) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);
    massive.push_back(30);

    EXPECT_THROW(massive.replace(5, 50), std::out_of_range);
}

TEST(TMassiveTest, ReplaceMethodNotValid) {
    TMassive<int> massive;
    EXPECT_THROW(massive.replace(0, 50), std::logic_error);
}

TEST(TMassiveTest, EraseOutOfRange) {
    TMassive<int> massive;
    // Заполняем архив значениями
    for (int i = 0; i < 10; ++i) {
        massive.push_back(i);
    }
    EXPECT_THROW(massive.erase(10, 1), std::out_of_range);
}

TEST(TMassiveTest, RemoveFirstOccurrenceNotValid) {
    TMassive<int> massive;
    EXPECT_THROW(massive.remove_first(40), std::logic_error);
}

TEST(TMassiveTest, RemoveLastOccurrenceNotValid) {
    TMassive<int> massive;
    EXPECT_THROW(massive.remove_last(40), std::logic_error);
}

TEST(TMassiveTest, RemoveByIndexOutOfRange) {
    TMassive<int> massive;
    EXPECT_THROW(massive.remove_by_index(5), std::out_of_range);
}

TEST(TMassiveTest, FindLastMethod_ValueNotInArchive) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);

    EXPECT_THROW(massive.find_last(40), std::logic_error);
}

TEST(TMassiveTest, FindFirstMethod_ValueNotInArchive) {
    TMassive<int> massive;
    massive.push_back(10);
    massive.push_back(20);

    EXPECT_THROW(massive.find_first(40), std::logic_error);
}
