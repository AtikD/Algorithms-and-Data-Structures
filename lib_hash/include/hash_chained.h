// Copyright 2025 atikdd.t.me

#pragma once

#include <massive.h>
#include <pair.h>
#include <stdexcept>
#include <string>
#include "./ihash.h"

template <typename TKey, typename TVal>
class THashTableChained : public IHeap<TKey, TVal> {
 private:
    TMassive<TMassive<TPair<TKey, TVal>>> table;
    int _find(const TKey& key, int index) const;

 public:
    explicit THashTableChained(int size = 101);
    THashTableChained(const THashTableChained& other);

    bool Insert(const TKey& key, const TVal& value) override;
    bool Insert(const THashTableChained<TKey, TVal>& other);
    bool Delete(const TKey& key) override;
    TVal Find(const TKey& key) const override;
    void Clear() override;
    template <typename K, typename V>
    friend std::ostream& operator<<(std::ostream& os,
        const THashTableChained<K, V>& hash);
};

template <typename TKey, typename TVal>
THashTableChained<TKey, TVal>::THashTableChained(
    int size) : IHeap<TKey, TVal>(size) {
    table.resize(this->tableSize);
}

template <typename TKey, typename TVal>
THashTableChained<TKey, TVal>::THashTableChained(
    const THashTableChained& other
) : IHeap<TKey, TVal>(other) {
    table = other.table;
}

template <typename TKey, typename TVal>
int THashTableChained<TKey, TVal>::_find(
    const TKey& key, int index) const {
    const TMassive<TPair<TKey, TVal>>& chain = table[index];
    for (int i = 0; i < chain.size(); ++i) {
        if (chain[i].first() == key) {
            return i;
        }
    }
    return -1;
}

template <typename TKey, typename TVal>
bool THashTableChained<TKey, TVal>::Insert(
    const TKey& key, const TVal& value) {

    int index = this->_hash(key);
    int secondIndex = _find(key, index);

    if (secondIndex != -1) {
        throw std::logic_error("Key already exists");
    }

    TPair<TKey, TVal> newPair(key, value);
    table[index].push_back(newPair);

    ++this->elemCount;
    return true;
}

template <typename TKey, typename TVal>
bool THashTableChained<TKey, TVal>::Insert(
    const THashTableChained<TKey, TVal>& other) {
    for (int i = 0; i < other.tableSize; ++i) {
        for (int j = 0; j < other.table[i].size(); ++j) {
            const TPair<TKey, TVal>& pair = other.table[i][j];
            int index = this->_hash(pair.first());
            if (_find(pair.first(), index) != -1)
                continue;
            Insert(pair.first(), pair.second());
        }
    }
    return true;
}

template <typename TKey, typename TVal>
bool THashTableChained<TKey, TVal>::Delete(const TKey& key) {
    int firstIndex = this->_hash(key);
    int secontIndex = _find(key, firstIndex);

    if (secontIndex == -1) {
        throw std::out_of_range("Key not found");
    }

    table[firstIndex].remove_by_index(secontIndex);
    --this->elemCount;
    return true;
}

template <typename TKey, typename TVal>
TVal THashTableChained<TKey, TVal>::Find(
    const TKey& key)
const {
    int firstIndex = this->_hash(key);
    int secondIndex = _find(key, firstIndex);

    if (secondIndex == -1) {
        throw std::out_of_range("Key not found");
    }

    return table[firstIndex][secondIndex].second();
}

template <typename TKey, typename TVal>
void THashTableChained<TKey, TVal>::Clear() {
    for (int i = 0; i < this->tableSize; ++i) {
        table[i].clear();
    }
    this->elemCount = 0;
}

template <typename TKey, typename TVal>
std::ostream& operator<<(std::ostream& os,
        const THashTableChained<TKey, TVal>& hash) {
    if (hash.count() == 0) {
        os << "Empty" << std::endl;
        return os;
    }

    for (int i = 0; i < hash.size(); ++i) {
        const TMassive<TPair<TKey, TVal>>& chain = hash.table[i];
        if (chain.size() > 0) {
            for (int j = 0; j < chain.size(); ++j) {
                os << chain[j].first() << ": "
                   << chain[j].second() << "\n";
            }
        }
    }
    return os;
}
