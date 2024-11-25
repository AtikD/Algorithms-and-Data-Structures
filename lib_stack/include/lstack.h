// Copyright 2024 atikdd.t.me

#pragma once

#include <list.h>

template <typename T>
class LStack{
 private:
    TList<T> _data;
 public:
    LStack();
    explicit LStack(const LStack<T>& other);
    ~LStack();

    LStack<T>& operator=(const LStack<T>& other);

    void push(const T& value);
    void pop();
    T top();

    bool empty() const noexcept;
    size_t size() const noexcept;
};

template <class T>
LStack<T>::LStack() : _data() {}

template <typename T>
LStack<T>::LStack(const LStack<T>& other) : _data(other._data) {}

template <typename T>
LStack<T>::~LStack() {}

template <class T>
T LStack<T>::top() {
    if (empty()) {
        throw std::out_of_range("Стек пуст.");
    }
    return _data.front();
}

template <typename T>
size_t LStack<T>::size() const noexcept {
    return _data.size();
}

template <typename T>
bool LStack<T>::empty() const noexcept {
    return _data.isEmpty();
}

template <class T>
LStack<T>& LStack<T>::operator=(const LStack<T>& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template <class T>
void LStack<T>::push(const T& value) {
    _data.push_front(value);
}

template <class T>
void LStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Стек пуст.");
    }
    _data.pop_front();
}
