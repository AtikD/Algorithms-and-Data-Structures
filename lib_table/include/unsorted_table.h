// Copyright 2025 atikdd.t.me

#pragma once
#include <itable.h>
#include <stdexcept>
#include <list.h>
#include <pair.h>
#include <node.h>

template <typename TKey, typename TVal>
class TUnsortedTable : public ITable<TKey, TVal> {
 private:
    TList<TPair<TKey, TVal>> _data;
    size_t _findIndex(const TKey& key) const;
 public:
    TUnsortedTable() = default;
    ~TUnsortedTable() override = default;

    bool Insert(const TKey& key, const TVal& val) override;
    TVal Find(const TKey& key) const override;
    bool IsExists(const TKey& key) const override;
    bool Delete(const TKey& key) override;
    size_t GetSize() const override;
    void Clear() override;
};


template <typename TKey, typename TVal>
bool TUnsortedTable<TKey, TVal>::Insert(const TKey& key, const TVal& val) {
    if (IsExists(key)) {
        throw std::invalid_argument("Key already exists in the table");
    }
    TPair<TKey, TVal> pair(key, val);
    _data.push_back(pair);
    return true;
}

template <typename TKey, typename TVal>
size_t TUnsortedTable<TKey, TVal>::_findIndex(const TKey& key) const {
    size_t index = 0;
    for (auto it = _data.begin(); it != _data.end(); ++it, ++index) {
        if ((*it).first() == key) {
            return index;
        }
    }
    return -1;
}

template <typename TKey, typename TVal>
TVal TUnsortedTable<TKey, TVal>::Find(const TKey& key) const {
    size_t index = _findIndex(key);
    if (index != -1) {
        TNode<TPair<TKey, TVal>>* node = _data.getNodeAt(index);
        return node->getValue().second();
    }
    throw std::out_of_range("Key not found");
}

template <typename TKey, typename TVal>
bool TUnsortedTable<TKey, TVal>::IsExists(const TKey& key) const {
    size_t index = _findIndex(key);
    return index != -1;
}

template <typename TKey, typename TVal>
bool TUnsortedTable<TKey, TVal>::Delete(const TKey& key) {
    size_t index = _findIndex(key);
    if (index == -1) 
        throw std::out_of_range("Key not found");
    _data.remove_at(index);
    return true;
}

template <typename TKey, typename TVal>
size_t TUnsortedTable<TKey, TVal>::GetSize() const {
    size_t count = 0;
    for (auto it = _data.begin(); it != _data.end(); ++it) {
        count++;
    }
    return count;
}

template <typename TKey, typename TVal>
void TUnsortedTable<TKey, TVal>::Clear() {
    while (!_data.isEmpty()) {
        _data.pop_front();
    }
}
