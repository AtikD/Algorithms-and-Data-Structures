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
        : _capacity(capacity), _data(new T[_capacity]),
          _top(-1), _back(-1), _size(0) {
    if (_capacity <= 0) {
        throw std::invalid_argument("Capacity must be positive");
    }
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
