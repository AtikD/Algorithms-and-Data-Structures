// Copyright 2024 atikdd.t.me

#pragma once

#include <iostream>
#include "../lib_list/node.h"

template <class T>
class TList {
 private:
    TNode<T>* _head;
    TNode<T>* _tail;

 public:
    // Конструкторы и деструктор
    TList();
    TList(const TList<T>& other);
    ~TList();

    // Проверка на пустоту
    bool isEmpty() const;

    // Вставка
    void push_back(const T& value);                     // В конец
    void push_front(const T& value);                    // В начало
    void insert_after(TNode<T>* node, const T& value);  // После указанного узла
    void insert_at(size_t pos, const T& value);         // На указанную позицию

    // Поиск
    TNode<T>* find(const T& value) const;                // По значению

    // Удаление
    void pop_back();                                     // Из конца
    void pop_front();                                    // Из начала
    void remove(TNode<T>* node);                         // Указанный узел
    void remove_at(size_t pos);                          // По указанной позиции

    // Замена значения
    void replace(TNode<T>* node, const T& newValue);     // Указанный узел
    void replace_at(size_t pos, const T& newValue);      // По указанной позиции

    // Ввод / вывод
    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const TList<U>& list);

    template <class U>
    friend std::istream& operator>>(std::istream& is, TList<U>& list);
};

template <class T>
TList<T>::TList() : _head(nullptr), _tail(nullptr) {}

template <class T>
TList<T>::TList(const TList<T>& other) : _head(nullptr), _tail(nullptr) {
    TNode<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->getValue());
        current = current->getNext();
    }
}

template <class T>
TList<T>::~TList() {
    while (!isEmpty()) {
        pop_front();
    }
}

template <class T>
bool TList<T>::isEmpty() const {
    return _head == nullptr;
}

template <class T>
void TList<T>::push_back(const T& value) {
    TNode<T>* newNode = new TNode<T>(value);
    if (isEmpty()) {
        _head = newNode;
        _tail = newNode;
    } else {
        _tail->setNext(newNode);
        _tail = newNode;
    }
}

template <class T>
void TList<T>::push_front(const T& value) {
    TNode<T>* newNode = new TNode<T>(value, _head);
    if (isEmpty()) {
        _tail = newNode;
    }
    _head = newNode;
}

template <class T>
void TList<T>::insert_after(TNode<T>* node, const T& value) {
    if (node == nullptr) {
        throw std::invalid_argument("Node cannot be null");
    }
    TNode<T>* newNode = new TNode<T>(value, node->getNext());
    node->setNext(newNode);
    if (node == _tail) {
        _tail = newNode;
    }
}

template <class T>
void TList<T>::insert_at(size_t pos, const T& value) {
    if (pos == 0) {
        push_front(value);
        return;
    }
    TNode<T>* current = _head;
    for (size_t i = 0; i < pos - 1; ++i) {
        if (current == nullptr) {
            throw std::out_of_range("Position out of range");
        }
        current = current->getNext();
    }
    if (current == nullptr) {
        throw std::out_of_range("Position out of range");
    }
    insert_after(current, value);
}
