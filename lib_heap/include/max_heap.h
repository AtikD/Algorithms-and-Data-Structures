// Copyright 2025 atikdd.t.me

#pragma once
#include <utility>
#include <algorithm>
#include "./iheap.h"

template <class TVal>
class MaxHeap : public IHeap<TVal> {
 public:
    explicit MaxHeap(size_t size = 0);
    MaxHeap(size_t size, const TVal* arr);
    MaxHeap(const MaxHeap<TVal>& other);

    void insert(TVal value) noexcept override;
    void emplace(size_t pos, TVal value) override;
    TVal top() const override;
    TVal remove_top() override;

 protected:
    void heapify() noexcept override;
    void sift_down(size_t i) noexcept override;
    void sift_up(size_t i) noexcept override;
};

template <class TVal>
MaxHeap<TVal>::MaxHeap(size_t size) : IHeap<TVal>(size) {}

template <class TVal>
MaxHeap<TVal>::MaxHeap(size_t size, const TVal* arr) : IHeap<TVal>(size, arr) {
    heapify();
}

template <class TVal>
MaxHeap<TVal>::MaxHeap(const MaxHeap<TVal>& other) : IHeap<TVal>(other) {}

template <class TVal>
void MaxHeap<TVal>::insert(TVal value) noexcept {
    this->_data.push_back(value);
    sift_up(this->_data.size() - 1);
}


template <class TVal>
void MaxHeap<TVal>::emplace(size_t pos, TVal value) {
    if (pos >= this->_data.size()) {
        throw std::out_of_range("Position out of range");
    }

    TVal old_value = this->_data[pos];
    this->_data[pos] = value;

    if (value > old_value) {
        sift_up(pos);
    } else if (value < old_value) {
        sift_down(pos);
    }
}

template <class TVal>
TVal MaxHeap<TVal>::top() const {
    if (this->is_empty()) {
        throw std::out_of_range("Heap is empty");
    }
    return this->_data[0];
}

template <class TVal>
TVal MaxHeap<TVal>::remove_top() {
    if (this->is_empty()) {
        throw std::out_of_range("Heap is empty");
    }

    TVal max_value = this->_data[0];

    if (this->_data.size() > 1) {
        TVal last = this->_data[this->_data.size() - 1];

        this->_data.pop_back();

        this->_data[0] = last;

        sift_down(0);
    } else {
        this->_data.pop_back();
    }

    return max_value;
}

template <class TVal>
void MaxHeap<TVal>::heapify() noexcept {
    for (int i = this->_data.size() / 2 - 1; i >= 0; i--) {
        sift_down(i);
    }
}

template <class TVal>
void MaxHeap<TVal>::sift_down(size_t i) noexcept {
    size_t largest = i;
    size_t l = this->left(i);
    size_t r = this->right(i);

    if (l < this->_data.size() && this->_data[l] > this->_data[largest]) {
        largest = l;
    }

    if (r < this->_data.size() && this->_data[r] > this->_data[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(this->_data[i], this->_data[largest]);
        sift_down(largest);
    }
}

template <class TVal>
void MaxHeap<TVal>::sift_up(size_t i) noexcept {
    while (i > 0 && this->_data[this->parent(i)] < this->_data[i]) {
        std::swap(this->_data[i], this->_data[this->parent(i)]);
        i = this->parent(i);
    }
}
