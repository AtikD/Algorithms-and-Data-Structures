// Copyright 2025 atikdd.t.me

#pragma once

#include <itable.h>
#include <massive.h>
#include <pair.h>
#include <stdexcept>
#include <algorithm>

template <typename TKey, typename TVal>
class TMassiveSortedTable : public ITable<TKey, TVal> {
 private:
    TMassive<TPair<TKey, TVal>> _data;

    int BinarySearch(const TKey& key) const;

    size_t FindInsertPosition(const TKey& key) const;

 public:
    TMassiveSortedTable() = default;
    ~TMassiveSortedTable() override = default;

    bool Insert(const TKey& key, const TVal& val) override;
    TVal Find(const TKey& key) const override;
    bool IsExists(const TKey& key) const override;
    bool Delete(const TKey& key) override;
    size_t GetSize() const override;
    void Clear() override;
};


template <typename TKey, typename TVal>
int TMassiveSortedTable<TKey, TVal>::BinarySearch(const TKey& key) const {
    if (_data.empty()) {
        return -1;
    }

    int left = 0;
    int right = static_cast<int>(_data.size()) - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        const TKey& middleKey = _data[middle].first();

        if (middleKey == key) {
            return middle;
        }

        if (middleKey < key) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}

template <typename TKey, typename TVal>
size_t TMassiveSortedTable<TKey, TVal>::FindInsertPosition(
    const TKey& key) const {
    if (_data.empty()) {
        return 0;
    }
    int left = 0;
    int right = static_cast<int>(_data.size()) - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (_data[middle].first() < key) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return static_cast<size_t>(left);
}

template <typename TKey, typename TVal>
bool TMassiveSortedTable<TKey, TVal>::Insert(const TKey& key, const TVal& val) {
    if (BinarySearch(key) != -1) {
        return false;
    }

    size_t pos = FindInsertPosition(key);

    TPair<TKey, TVal> pair(key, val);
    _data.insert(pair, pos);

    return true;
}

template <typename TKey, typename TVal>
TVal TMassiveSortedTable<TKey, TVal>::Find(const TKey& key) const {
    int index = BinarySearch(key);

    if (index != -1) {
        return _data[index].second();
    }

    throw std::runtime_error("Key not found");
}

template <typename TKey, typename TVal>
bool TMassiveSortedTable<TKey, TVal>::IsExists(const TKey& key) const {
    return BinarySearch(key) != -1;
}

template <typename TKey, typename TVal>
bool TMassiveSortedTable<TKey, TVal>::Delete(const TKey& key) {
    int index = BinarySearch(key);

    if (index != -1) {
        _data.remove_by_index(index);
        return true;
    }

    return false;
}

template <typename TKey, typename TVal>
size_t TMassiveSortedTable<TKey, TVal>::GetSize() const {
    return _data.size();
}

template <typename TKey, typename TVal>
void TMassiveSortedTable<TKey, TVal>::Clear() {
    _data.clear();
}
