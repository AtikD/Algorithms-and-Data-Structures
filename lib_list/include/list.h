// Copyright 2024 atikdd.t.me

#pragma once

#include <node.h>
#include <iostream>
#include <algorithm>


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

    // Возвращает значение первого элемента
    T front() const;
    // Возвращает указатель на узел по индексу (0-based)
    TNode<T>* getNodeAt(size_t pos) const;

    // Удаление
    void pop_back();                                     // Из конца
    void pop_front();                                    // Из начала
    void remove(TNode<T>* node);                         // Указанный узел
    void remove_at(size_t pos);                          // По указанной позиции

    // Замена значения
    void replace(TNode<T>* node, const T& newValue);     // Указанный узел
    void replace_at(size_t pos, const T& newValue);      // По указанной позиции

    TNode<T>* getHead() const;

    TNode<T>* getTail() const;

    // Ввод / вывод
    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const TList<U>& list);

    template <class U>
    friend std::istream& operator>>(std::istream& is, TList<U>& list);

    class iterator {
     private:
        TNode<T>* current;

     public:
        iterator() : current(nullptr) {}
        explicit iterator(TNode<T>* node) : current(node) {}

        T& operator*() const {
            return current->getValue();
        }

        iterator& operator++() {  // Префиксный
            if (current) {
                current = current->getNext();
            }
            return *this;
        }
        iterator& operator++() const {  // Префиксный
            if (current) {
                current = current->getNext();
            }
            return *this;
        }

        iterator operator++(int) {  // Постфиксный
            iterator temp = *this;
            if (current) {
                current = current->getNext();
            }
            return temp;
        }
        iterator operator++(int) const {  // Постфиксный
            iterator temp = *this;
            if (current) {
                current = current->getNext();
            }
            return temp;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };
    iterator begin() {
        return iterator(_head);
    }
    iterator end() {
        return iterator(nullptr);
    }

    iterator begin() const {
        return iterator(_head);
    }

    iterator end() const {
        return iterator(nullptr);
    }
};

template <class T>
TList<T>::TList() : _head(nullptr), _tail(nullptr) {}

template <class T>
TList<T>::TList(const TList<T>& other): _head(nullptr),
                                    _tail(nullptr) {
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
TNode<T>* TList<T>::getHead() const {
    return _head;
}

template <class T>
TNode<T>* TList<T>::getTail() const {
    return _tail;
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

template <class T>
TNode<T>* TList<T>::find(const T& value) const {
    TNode<T>* current = _head;
    while (current != nullptr) {
        if (current->getValue() == value) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

template <class T>
void TList<T>::pop_back() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    } else {
        TNode<T>* current = _head;
        while (current->getNext() != _tail) {
            current = current->getNext();
        }
        delete _tail;
        _tail = current;
        _tail->setNext(nullptr);
    }
}

template <class T>
void TList<T>::pop_front() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    TNode<T>* temp = _head;
    _head = _head->getNext();
    delete temp;
    if (_head == nullptr) {
        _tail = nullptr;
    }
}

template <class T>
void TList<T>::remove(TNode<T>* node) {
    if (isEmpty() || node == nullptr) {
        throw std::invalid_argument("Node cannot be null or list is empty");
    }
    if (node == _head) {
        pop_front();
        return;
    }
    TNode<T>* current = _head;
    while (current->getNext() != nullptr && current->getNext() != node) {
        current = current->getNext();
    }
    if (current->getNext() == nullptr) {
        throw std::invalid_argument("Node not found in the list");
    }
    current->setNext(node->getNext());
    if (node == _tail) {
        _tail = current;
    }
    delete node;
}

template <class T>
void TList<T>::remove_at(size_t pos) {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    if (pos == 0) {
        pop_front();
        return;
    }
    TNode<T>* current = _head;
    for (size_t i = 0; i < pos - 1; ++i) {
        if (current == nullptr || current->getNext() == nullptr) {
            throw std::out_of_range("Position out of range");
        }
        current = current->getNext();
    }
    TNode<T>* nodeToDelete = current->getNext();
    if (nodeToDelete == nullptr) {
        throw std::out_of_range("Position out of range");
    }
    current->setNext(nodeToDelete->getNext());
    if (nodeToDelete == _tail) {
        _tail = current;
    }
    delete nodeToDelete;
}

template <class T>
void TList<T>::replace(TNode<T>* node, const T& newValue) {
    if (node == nullptr) {
        throw std::invalid_argument("Node cannot be null");
    }
    node->setValue(newValue);
}

template <class T>
void TList<T>::replace_at(size_t pos, const T& newValue) {
    TNode<T>* current = _head;
    for (size_t i = 0; i < pos; ++i) {
        if (current == nullptr) {
            throw std::out_of_range("Position out of range");
        }
        current = current->getNext();
    }
    if (current == nullptr) {
        throw std::out_of_range("Position out of range");
    }
    current->setValue(newValue);
}

template <class U>
std::ostream& operator<<(std::ostream& os, const TList<U>& list) {
    TNode<U>* current = list._head;
    while (current != nullptr) {
        os << current->getValue() << " -> ";
        current = current->getNext();
    }
    os << "nullptr";
    return os;
}

template <class U>
std::istream& operator>>(std::istream& is, TList<U>& list) {
    U value;
    while (is >> value) {
        list.push_back(value);
    }
    return is;
}

template <class T>
T TList<T>::front() const {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    return _head->getValue();
}

template <class T>
TNode<T>* TList<T>::getNodeAt(size_t pos) const {
    TNode<T>* current = _head;
    size_t index = 0;
    while (current != nullptr) {
        if (index == pos) {
            return current;
        }
        current = current->getNext();
        ++index;
    }
    throw std::out_of_range("Position out of range");
}
