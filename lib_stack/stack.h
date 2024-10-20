// Copyright 2024 atikdd.t.me

#pragma once

#include <stdexcept>
#include "../lib_massive/massive.h"


template <typename T>
class Stack {
 private:
    TMassive<T> _data;

 public:
    // Конструкторы
    Stack();
    // Stack(const Stack<T>& other);
    // Stack(Stack<T>&& other) noexcept;

    // Деструктор
    // ~Stack();

    // Операторы присваивания
    // Stack<T>& operator=(const Stack<T>& other);
    // Stack<T>& operator=(Stack<T>&& other) noexcept;

    // Основные методы
    // void push(const T& value);    // Добавить элемент на вершину стека
    // void pop();                   // Удалить элемент с вершины стека
    // T& top();                     // Получить элемент на вершине стека
    // const T& top() const;         // Для константных объектов

    // bool empty() const;           // Проверить, пуст ли стек
    // size_t size() const;          // Получить количество элементов

    // void clear();                 // Очистить стек
};

template <typename T>
Stack<T>::Stack() : _data() {}
