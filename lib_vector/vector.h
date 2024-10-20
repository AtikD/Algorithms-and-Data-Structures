// Copyright 2024 atikdd.t.me

#pragma once

#include <iostream>
#include <stdexcept>
#include "../lib_massive/massive.h"


template <typename T>
class TVector {
 private:
    TMassive<T> _data;    // Хранение данных вектора
    size_t _start_index;  // Начальный индекс вектора

 public:
    // Конструкторы
    TVector();
    TVector(size_t size, size_t start_index = 0);
    TVector(const T* arr, size_t size, size_t start_index = 0);
    TVector(const TVector<T>& other);
    TVector(TVector<T>&& other) noexcept;

    // Деструктор
    ~TVector();

    // Операторы присваивания
    TVector<T>& operator=(const TVector<T>& other);
    TVector<T>& operator=(TVector<T>&& other) noexcept;

    // Операторы доступа
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Арифметические операторы
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
