// Copyright 2024 atikdd.t.me

#pragma once

#include <list.h>

template <typename T>
bool hasCycle(const TList<T>& list) {
    TNode<T>* head = list.getHead();
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
