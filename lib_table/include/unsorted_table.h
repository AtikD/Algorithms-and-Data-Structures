// Copyright 2025 atikdd.t.me

#pragma once
#include <itable.h>
#include <stdexcept>
#include <list.h>
#include <pair.h>

template <typename TKey, typename TVal>
class TUnsortedTable : public ITable<TKey, TVal> {
 private:
    TList<TPair<TKey, TVal>> _data;

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
        return false;
    }
    TPair<TKey, TVal> pair(key, val);
    _data.push_back(pair);
    return true;
}

template <typename TKey, typename TVal>
TVal TUnsortedTable<TKey, TVal>::Find(const TKey& key) const {
    for (auto it = _data.begin(); it != _data.end(); ++it) {
        if ((*it).first() == key) {
            return (*it).second();
        }
    }
    throw std::runtime_error("Key not found");
}

template <typename TKey, typename TVal>
bool TUnsortedTable<TKey, TVal>::IsExists(const TKey& key) const {
    for (auto it = _data.begin(); it != _data.end(); ++it) {
        if ((*it).first() == key) {
            return true;
        }
    }
    return false;
}

template <typename TKey, typename TVal>
bool TUnsortedTable<TKey, TVal>::Delete(const TKey& key) {
    size_t index = 0;
    for (auto it = _data.begin(); it != _data.end(); ++it, ++index) {
        if ((*it).first() == key) {
            _data.remove_at(index);
            return true;
        }
    }
    return false;
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
