// Copyright 2024 atikdd.t.me

#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include "../lib_massive/massive.h"


template <typename T>
class TVector {
 private:
    TMassive<T> _data;
    size_t _start_index;

 public:
    TVector();
    TVector(size_t size, size_t start_index);
    TVector(const T* arr, size_t size, size_t start_index);
    TVector(const TVector<T>& other);
    TVector(TVector<T>&& other) noexcept;

    ~TVector();

    // Операторы присваивания
    // TVector<T>& operator=(const TVector<T>& other);
    // TVector<T>& operator=(TVector<T>&& other) noexcept;

    // Операторы доступа
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // А рифметические операторы
    // TVector<T> operator+(const TVector<T>& other) const;
    // TVector<T> operator-(const TVector<T>& other) const;
    // T operator*(const TVector<T>& other) const;  // Скалярное произведение

    // TVector<T>& operator+=(const TVector<T>& other);
    // TVector<T>& operator-=(const TVector<T>& other);

    // Операторы сравнения
    // bool operator==(const TVector<T>& other) const;
    // bool operator!=(const TVector<T>& other) const;

    // Умножение на скаляр
    // TVector<T> operator*(const T& scalar) const;
    // TVector<T>& operator*=(const T& scalar);

    // Методы
    size_t size() const;
    size_t get_start_index() const;
    // void set_start_index(size_t start_index);

    // void resize(size_t new_size);
    // void clear();

    // void print(std::ostream& out = std::cout) const;
};

template <typename T>
TVector<T>::TVector() : _data(), _start_index(0) {}

template <typename T>
TVector<T>::TVector(size_t size, size_t start_index) :
                    _data(), _start_index(start_index) {
    _data.resize(size, 0);
}

template <typename T>
TVector<T>::TVector(const T* arr, size_t size, size_t start_index) :
            _data(), _start_index(start_index) {
    _data.insert(arr, size, 0);
}

template <typename T>
TVector<T>::TVector(const TVector<T>& other) :
                _data(other._data), _start_index(other._start_index) {}

template <typename T>
TVector<T>::TVector(TVector<T>&& other) noexcept :
            _data(std::move(other._data)), _start_index(other._start_index) {
    other._start_index = 0;
}



template <typename T>
TVector<T>::~TVector() {}

template <typename T>
size_t TVector<T>::get_start_index() const {
    return _start_index;
}

template <typename T>
size_t TVector<T>::size() const {
    return _data.size();
}

template <typename T>
T& TVector<T>::operator[](size_t index) {
    if (index < _start_index || index >= _start_index + _data.size()) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return _data[index - _start_index];
}

template <typename T>
const T& TVector<T>::operator[](size_t index) const {
    if (index < _start_index || index >= _start_index + _data.size()) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return _data[index - _start_index];
}
