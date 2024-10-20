// Copyright 2024 atikdd.t.me

#pragma once

#include <stdexcept>
#include "../lib_massive/massive.h"

//  Стек — это абстрактный тип данных, который
//  реализует принцип LIFO (Last In, First Out),
//  что означает "последним пришел — первым вышел".
//  В стеке элементы добавляются и удаляются только с
//  одного конца, называемого вершиной стека.
template <typename T>
class Stack {
 private:
    TMassive<T> _data;

 public:
    // Конструкторы
    Stack();
    Stack(const Stack<T>& other);

    // Деструктор
    ~Stack();

    // Операторы присваивания
    Stack<T>& operator=(const Stack<T>& other);

    // Основные методы
    void push(const T& value);    // Добавить элемент на вершину стека
    void pop();                   // Удалить элемент с вершины стека
    T& top();                     // Получить элемент на вершине стека
    const T& top() const;         // Для константных объектов

    bool empty() const;           // Проверить, пуст ли стек
    size_t size() const;          // Получить количество элементов

    void clear();                 // Очистить стек
};

template <typename T>
Stack<T>::Stack() : _data() {}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) : _data(other._data) {}

template <typename T>
Stack<T>::~Stack() {}

template <typename T>
T& Stack<T>::top() {
    if (empty()) {
        throw std::out_of_range("Стек пуст. Невозможно выполнить top().");
    }
    return _data[_data.size() - 1];
}

template <typename T>
size_t Stack<T>::size() const {
    return _data.size();
}

template <typename T>
bool Stack<T>::empty() const {
    return _data.empty();
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Стек пуст. Невозможно выполнить pop().");
    }
    _data.pop_back();
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Стек пуст. Невозможно выполнить top().");
    }
    return _data[_data.size() - 1];
}

template <typename T>
void Stack<T>::push(const T& value) {
    _data.push_back(value);
}

template <typename T>
void Stack<T>::clear() {
    _data.clear();
}
