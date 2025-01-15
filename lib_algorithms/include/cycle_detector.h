// Copyright 2024 atikdd.t.me

#pragma once

#include <list.h>

template <typename T>
bool hasCycleReverse(TList<T>* list) {
    if (list == nullptr) {
        return false;
    }

    TNode<T>* current = list->getHead();
    TNode<T>* prev = nullptr;
    TNode<T>* next = nullptr;

    while (current != nullptr) {
        next = current->getNext();
        current->setNext(prev);
        prev = current;
        current = next;

        // Если узел указывает на голову списка, это цикл
        if (current == list->getHead()) {
            return true;
        }
    }

    return false;  // Цикл отсутствует
}


template <typename T>
bool hasCycleFloyd(const TList<T>* list) {
    TNode<T>* head = list->getHead();
    if (head == nullptr) {
        return false;
    }

    TNode<T>* slow = head;
    TNode<T>* fast = head;

    while (fast != nullptr && fast->getNext() != nullptr) {
        slow = slow->getNext();
        fast = fast->getNext()->getNext();

        if (slow == fast) {
            return true;  // Цикл обнаружен
        }
    }

    return false;  // Цикла нет
}

