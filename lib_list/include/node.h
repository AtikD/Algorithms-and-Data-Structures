// Copyright 2024 atikdd.t.me

#pragma once

#include <iostream>

template <class T>
class TNode {
 private:
    T _value;
    TNode<T>* _pnext;

 public:
    // Конструкторы
    explicit TNode(const T& value, TNode<T>* pnext = nullptr);
    TNode(const TNode<T>& other);

    // Оператор присваивания
    TNode<T>& operator=(const TNode<T>& other);

    // Оператор сравнения
    bool operator==(const TNode<T>& other) const;

    // Геттеры и сеттеры
    T getValue() const;
    void setValue(const T& value);

    TNode<T>* getNext() const;
    void setNext(TNode<T>* pnext);

    // Ввод / вывод
    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const TNode<U>& node);

    template <class U>
    friend std::istream& operator>>(std::istream& is, TNode<U>& node);
};

template <class T>
TNode<T>::TNode(const T& value, TNode<T>* pnext)
    : _value(value), _pnext(pnext) {}

template <class T>
TNode<T>::TNode(const TNode<T>& other)
    : _value(other._value), _pnext(other._pnext) {}

template <class T>
TNode<T>& TNode<T>::operator=(const TNode<T>& other) {
    if (this != &other) {
        _value = other._value;
        _pnext = other._pnext;
    }
    return *this;
}

template <class T>
bool TNode<T>::operator==(const TNode<T>& other) const {
    return _value == other._value;
}

template <class T>
T TNode<T>::getValue() const {
    return _value;
}

template <class T>
void TNode<T>::setValue(const T& value) {
    _value = value;
}

template <class T>
TNode<T>* TNode<T>::getNext() const {
    return _pnext;
}

template <class T>
void TNode<T>::setNext(TNode<T>* pnext) {
    _pnext = pnext;
}

template <class U>
std::ostream& operator<<(std::ostream& os, const TNode<U>& node) {
    os << node._value;
    return os;
}

template <class U>
std::istream& operator>>(std::istream& is, TNode<U>& node) {
    is >> node._value;
    return is;
}
