// Copyright 2025 atikdd.ru

#pragma once

#include <itable.h>
#include <massive.h>
#include <pair.h>

template <typename TKey, typename TVal>
class TMassiveUnsortedTable : public ITable<TKey, TVal> {
 private:
    TMassive<TPair<TKey, TVal>> _data;

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
        return false;
    }
    TPair<TKey, TVal> pair(key, val);
    _data.push_back(pair);
    return true;
}

template <typename TKey, typename TVal>
TVal TMassiveUnsortedTable<TKey, TVal>::Find(const TKey& key) const {
    for (size_t i = 0; i < _data.size(); ++i) {
        if (_data[i].first() == key) {
            return _data[i].second();
        }
    }
    throw std::runtime_error("Key not found");
}

template <typename TKey, typename TVal>
bool TMassiveUnsortedTable<TKey, TVal>::IsExists(const TKey& key) const {
    for (size_t i = 0; i < _data.size(); ++i) {
        if (_data[i].first() == key) {
            return true;
        }
    }
    return false;
}

template <typename TKey, typename TVal>
bool TMassiveUnsortedTable<TKey, TVal>::Delete(const TKey& key) {
    for (size_t i = 0; i < _data.size(); ++i) {
        if (_data[i].first() == key) {
            _data.remove_by_index(i);
            return true;
        }
    }
    return false;
}

template <typename TKey, typename TVal>
size_t TMassiveUnsortedTable<TKey, TVal>::GetSize() const {
    return _data.size();
}

template <typename TKey, typename TVal>
void TMassiveUnsortedTable<TKey, TVal>::Clear() {
    _data.clear();
}
