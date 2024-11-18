// Copyright 2024 atikdd.t.me

#pragma once

#include <massive.h>
#include <iostream>
#include <stdexcept>
#include <utility>



template <typename T>
class TVector {
 protected:
    TMassive<T> _data;
    size_t _start_index;

 public:
    TVector();
    explicit TVector(size_t size, size_t start_index = 0);
    TVector(const T* arr, size_t size, size_t start_index = 0);
    TVector(const TVector<T>& other);

    ~TVector();

    // Операторы присваивания
    TVector<T>& operator=(const TVector<T>& other);

    // Операторы доступа
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // А рифметические операторы
    TVector<T> operator+(const TVector<T>& other) const;
    TVector<T> operator-(const TVector<T>& other) const;
    T operator*(const TVector<T>& other) const;  // Скалярное произведение

    TVector<T>& operator+=(const TVector<T>& other);
    TVector<T>& operator-=(const TVector<T>& other);

    // Операторы сравнения
    bool operator==(const TVector<T>& other) const;
    bool operator!=(const TVector<T>& other) const;

    // Умножение на скаляр
    TVector<T> operator*(const T& scalar) const;
    TVector<T>& operator*=(const T& scalar);

    // Методы
    size_t size() const;
    size_t get_start_index() const;
    void set_start_index(size_t start_index);

    void resize(size_t new_size);
    void clear();

    void print(std::ostream& out = std::cout) const;
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

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
    if (this != &other) {
        _data = other._data;
        _start_index = other._start_index;
    }
    return *this;
}

template <typename T>
TVector<T> TVector<T>::operator+(const TVector<T>& other) const {
    if (size() != other.size() || _start_index != other._start_index) {
        throw std::logic_error("Размеры векторов не совпадают");
    }
    TVector<T> result(size(), _start_index);
    for (size_t i = 0; i < size(); ++i) {
        result._data.replace(i, _data[i] + other._data[i]);
    }
    return result;
}

template <typename T>
TVector<T> TVector<T>::operator-(const TVector<T>& other) const {
    if (size() != other.size() || _start_index != other._start_index) {
        throw std::logic_error("Размеры векторов не совпадают");
    }
    TVector<T> result(size(), _start_index);
    for (size_t i = 0; i < size(); ++i) {
        result._data.replace(i, _data[i] - other._data[i]);
    }
    return result;
}

template <typename T>
T TVector<T>::operator*(const TVector<T>& other) const {
    if (size() != other.size() || _start_index != other._start_index) {
        throw std::logic_error("Размеры векторов не совпадают");
    }
    T result = T();
    for (size_t i = 0; i < size(); ++i) {
        result += _data[i] * other._data[i];
    }
    return result;
}

template <typename T>
TVector<T>& TVector<T>::operator+=(const TVector<T>& other) {
    if (size() != other.size() || _start_index != other._start_index) {
        throw std::logic_error("Размеры векторов не совпадают");
    }
    for (size_t i = 0; i < size(); ++i) {
        _data.replace(i, _data[i] + other._data[i]);
    }
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::operator-=(const TVector<T>& other) {
    if (size() != other.size() || _start_index != other._start_index) {
        throw std::logic_error("Размеры векторов не совпадают");
    }
    for (size_t i = 0; i < size(); ++i) {
        _data.replace(i, _data[i] - other._data[i]);
    }
    return *this;
}

template <typename T>
bool TVector<T>::operator==(const TVector<T>& other) const {
    if (size() != other.size() || _start_index != other._start_index) {
        return false;
    }
    for (size_t i = 0; i < size(); ++i) {
        if (_data[i] != other._data[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

template <typename T>
TVector<T> TVector<T>::operator*(const T& scalar) const {
    TVector<T> result(size(), _start_index);
    for (size_t i = 0; i < size(); ++i) {
        result._data.replace(i, _data[i] * scalar);
    }
    return result;
}

template <typename T>
TVector<T>& TVector<T>::operator*=(const T& scalar) {
    for (size_t i = 0; i < size(); ++i) {
        _data.replace(i, _data[i] * scalar);
    }
    return *this;
}

template <typename T>
void TVector<T>::set_start_index(size_t start_index) {
    _start_index = start_index;
}

template <typename T>
void TVector<T>::resize(size_t new_size) {
    _data.resize(new_size, 0);
}

template <typename T>
void TVector<T>::clear() {
    _data.clear();
    _start_index = 0;
}

template <typename T>
void TVector<T>::print(std::ostream& out) const {
    out << "{ ";
    for (size_t i = 0; i < size(); ++i) {
        out << _data[i];
        if (i < size() - 1) {
            out << ", ";
        }
    }
    out << " }";
}
