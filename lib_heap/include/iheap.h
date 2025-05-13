// Copyright 2025 atikdd.t.me
#pragma once
#include <massive.h>
#include <stdexcept>

template <class TVal>
class IHeap {
 protected:
    TMassive<TVal> _data;

 public:
    explicit IHeap(size_t size = 0) {}
    IHeap(size_t size, const TVal* arr);
    IHeap(const IHeap& other);
    virtual ~IHeap() = default;

    inline size_t left(size_t i) const { return 2 * i + 1; }
    inline size_t right(size_t i) const { return 2 * i + 2; }
    inline size_t parent(size_t i) const { return (i - 1) / 2; }

    inline bool is_empty() const noexcept { return _data.empty(); }
    inline size_t size() const noexcept { return _data.size(); }
    virtual void insert(TVal value) noexcept = 0;
    virtual void emplace(size_t pos, TVal value) = 0;

    virtual TVal top() const = 0;
    virtual TVal remove_top() = 0;
    void clear();

    IHeap& operator=(const IHeap& other);
    TVal& operator[](size_t index);
    const TVal& operator[](size_t index) const;

 protected:
    virtual void heapify() noexcept = 0;
    virtual void sift_down(size_t i) noexcept = 0;
    virtual void sift_up(size_t i) noexcept = 0;
};

template <class TVal>
IHeap<TVal>::IHeap(size_t size, const TVal* arr) {
    if (size > 0) {
        _data.insert(arr, size, 0);
    }
}

template <class TVal>
IHeap<TVal>::IHeap(const IHeap& other) : _data(other._data) {}

template <class TVal>
void IHeap<TVal>::clear() {
    _data.clear();
}

template <class TVal>
IHeap<TVal>& IHeap<TVal>::operator=(const IHeap& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template <class TVal>
TVal& IHeap<TVal>::operator[](size_t index) {
    if (index >= _data.size()) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template <class TVal>
const TVal& IHeap<TVal>::operator[](size_t index) const {
    if (index >= _data.size()) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template <class TVal>
std::ostream& operator<<(std::ostream& os, const IHeap<TVal>& heap) {
    for (size_t i = 0; i < heap.size(); ++i) {
        os << heap[i];
        if (i < heap.size() - 1) {
            os << " ";
        }
    }
    return os;
}
