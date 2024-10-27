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
