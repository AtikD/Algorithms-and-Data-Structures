// Copyright 2024 atikdd.t.me

#pragma once

#include <stdexcept>
#include <iostream>
#include "../lib_massive/massive.h"

template <typename T>
class TQueue {
 private:
    int _capacity;       // Максимальный размер очереди
    T* _data;            // Массив для хранения элементов
    int _top;            // Индекс начала очереди
    int _back;           // Индекс конца очереди
    int _size;           // Текущее количество элементов

 public:
    TQueue();
    explicit TQueue(int capacity);
    TQueue(const TQueue<T>& other);
    explicit TQueue(const TMassive<T>& massive);

    ~TQueue();

    void push(const T& value);
    T pop();
    bool is_full() const;
    bool is_empty() const;

    void clear();
    void print() const;
    int get_top() const;
    int get_back() const;
    int size() const;
    int capacity() const;
};

template <typename T>
TQueue<T>::TQueue()
        : _capacity(10), _data(new T[_capacity]),
          _top(-1), _back(-1), _size(0) {}

template <typename T>
TQueue<T>::TQueue(int capacity)
        : _capacity(capacity), _data(nullptr), _top(-1), _back(-1), _size(0) {
    if (_capacity <= 0) {
        throw std::invalid_argument("Capacity must be positive");
    }
    _data = new T[_capacity];
}

template <typename T>
TQueue<T>::TQueue(const TQueue<T>& other)
    : _capacity(other._capacity), _data(new T[other._capacity]),
      _top(other._top), _back(other._back), _size(other._size) {
    if (!other.is_empty()) {
        int i = other._top;
        while (true) {
            _data[i] = other._data[i];
            if (i == other._back) {
                break;
            }
            i = (i + 1) % _capacity;
        }
    }
}

template <typename T>
TQueue<T>::TQueue(const TMassive<T>& massive)
    : _capacity(massive.size()), _data(new T[_capacity]),
      _top(-1), _back(-1), _size(0) {
    for (size_t i = 0; i < massive.size(); ++i) {
        push(massive[i]);
    }
}

template <typename T>
TQueue<T>::~TQueue() {
    delete[] _data;
}

template <typename T>
void TQueue<T>::push(const T& value) {
    if (is_full()) {
        throw std::overflow_error("Очередь полна!");
    }

    if (is_empty()) {
        _top = 0;
        _back = 0;
    } else {
        _back = (_back + 1) % _capacity;
    }

    _data[_back] = value;
    ++_size;
}

template <typename T>
T TQueue<T>::pop() {
    if (is_empty()) {
        throw std::underflow_error("Очередь пуста!");
    }

    T value = _data[_top];

    if (_top == _back) {
        // Очередь стала пустой
        _top = -1;
        _back = -1;
    } else {
        _top = (_top + 1) % _capacity;
    }

    --_size;
    return value;
}

template <typename T>
bool TQueue<T>::is_empty() const {
    return _size == 0;
}

template <typename T>
bool TQueue<T>::is_full() const {
    return _size == _capacity;
}

template <typename T>
void TQueue<T>::clear() {
    _top = -1;
    _back = -1;
    _size = 0;
}

template <typename T>
void TQueue<T>::print() const {
    if (is_empty()) {
        std::cout << "Очередь пуста." << std::endl;
        return;
    }
    int i = _top;
    while (true) {
        std::cout << _data[i] << " ";
        if (i == _back) {
            break;
        }
        i = (i + 1) % _capacity;
    }
    std::cout << std::endl;
}

template <typename T>
int TQueue<T>::get_top() const {
    return _top;
}

template <typename T>
int TQueue<T>::get_back() const {
    return _back;
}

template <typename T>
int TQueue<T>::size() const {
    return _size;
}

template <typename T>
int TQueue<T>::capacity() const {
    return _capacity;
}
