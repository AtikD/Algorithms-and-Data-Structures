// Copyright 2025 atikdd.t.me

#pragma once
#include <string>

template <typename TKey, typename TVal>
class IHeap {
 protected:
    int tableSize;
    int elemCount;

    int _hash(const TKey& key) const;
    int _hashImpl(const int& key) const;
    int _hashImpl(const std::string& key) const;

 public:
    explicit IHeap(int size = 101);
    IHeap(const IHeap& other);
    ~IHeap() = default;
    virtual bool Insert(const TKey& key, const TVal& value) = 0;
    virtual bool Delete(const TKey& key) = 0;
    virtual TVal Find(const TKey& key) const = 0;
    virtual void Clear() = 0;
    int size() const { return tableSize; }
    int count() const { return elemCount; }
};

template <typename TKey, typename TVal>
IHeap<TKey, TVal>::IHeap(int size) : tableSize(size), elemCount(0) {
    if (size <= 0) {
        size = 101;
        tableSize = size;
    }
}

template <typename TKey, typename TVal>
IHeap<TKey, TVal>::IHeap(const IHeap& other)
    : tableSize(other.tableSize), elemCount(other.elemCount) {}

template <typename TKey, typename TVal>
int IHeap<TKey, TVal>::_hash(const TKey& key) const {
    return _hashImpl(key) % tableSize;
}

template <typename TKey, typename TVal>
int IHeap<TKey, TVal>::_hashImpl(const int& key) const {
    return _hashImpl(std::to_string(key));
}

template <typename TKey, typename TVal>
int IHeap<TKey, TVal>::_hashImpl(const std::string& key) const {
    int hash = 0;
    for (int i = 0; i < key.length(); ++i) {
        hash = hash + static_cast<unsigned char>(key[i]);
    }
    return hash;
}
