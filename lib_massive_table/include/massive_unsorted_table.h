// Copyright 2025 atikdd.ru

#pragma once

#include <itable.h>
#include <massive.h>
#include <pair.h>

template <typename TKey, typename TVal>
class TMassiveUnsortedTable : public ITable<TKey, TVal> {
 private:
    TMassive<TPair<TKey, TVal>> _data;
    size_t _findIndex(const TKey& key) const;
 public:
    TMassiveUnsortedTable() = default;
    ~TMassiveUnsortedTable() override = default;
    bool Insert(const TKey& key, const TVal& val) override;
    TVal Find(const TKey& key) const override;
    bool IsExists(const TKey& key) const override;
    bool Delete(const TKey& key) override;
    size_t GetSize() const override;
    void Clear() override;
};

template <typename TKey, typename TVal>
bool TMassiveUnsortedTable<TKey, TVal>::Insert(
    const TKey& key, const TVal& val) {
    if (IsExists(key)) {
        throw std::invalid_argument("Key already exists in the table");
    }
    TPair<TKey, TVal> pair(key, val);
    _data.push_back(pair);
    return true;
}

template <typename TKey, typename TVal>
size_t TMassiveUnsortedTable<TKey, TVal>::_findIndex(const TKey& key) const {
    for (size_t i = 0; i < _data.size(); ++i) {
        if (_data[i].first() == key) {
            return i;
        }
    }
    return -1;
}

template <typename TKey, typename TVal>
TVal TMassiveUnsortedTable<TKey, TVal>::Find(const TKey& key) const {
    size_t index = _findIndex(key);
    if (index != -1) {
        return _data[index].second();
    }
    throw std::out_of_range("Key not found");
}

template <typename TKey, typename TVal>
bool TMassiveUnsortedTable<TKey, TVal>::IsExists(const TKey& key) const {
    size_t index = _findIndex(key);
    return index !=-1;
}

template <typename TKey, typename TVal>
bool TMassiveUnsortedTable<TKey, TVal>::Delete(const TKey& key) {
    size_t index = _findIndex(key);
    if (index == -1)
        throw std::out_of_range("Key not found");
    _data.remove_by_index(index);
    return true;
}

template <typename TKey, typename TVal>
size_t TMassiveUnsortedTable<TKey, TVal>::GetSize() const {
    return _data.size();
}

template <typename TKey, typename TVal>
void TMassiveUnsortedTable<TKey, TVal>::Clear() {
    _data.clear();
}
