// Copyright 2025 atikdd.t.me

#pragma once

#include <massive.h>
#include <pair.h>
#include <stdexcept>
#include <string>
#include "./ihash.h"

enum class TableEntryState { EMPTY, OCCUPIED, DELETED };

template <typename TKey, typename TVal>
class THashTableOpen : public IHeap<TKey, TVal> {
 private:
    struct TableEntry {
        TPair<TKey, TVal> pair;
        TableEntryState state;

        TableEntry() : state(TableEntryState::EMPTY) {}
        TableEntry(const TKey& key, const TVal& value)
            : pair(key, value), state(TableEntryState::OCCUPIED) {}
    };

    TMassive<TableEntry> table;
    int _hash2(int key) const;
    int _find(const TKey& key) const;

 public:
    explicit THashTableOpen(int size = 191);
    THashTableOpen(const THashTableOpen& other);
    bool Insert(const TKey& key, const TVal& value) override;
    bool Insert(const THashTableOpen<TKey, TVal>& other);
    bool Delete(const TKey& key) override;
    TVal Find(const TKey& key) const override;
    void Clear() override;
    template <typename K, typename V>
    friend std::ostream& operator<<(std::ostream& os,
        const THashTableOpen<K, V>& hash);
};

template <typename TKey, typename TVal>
THashTableOpen<TKey, TVal>::THashTableOpen(int size)
    : IHeap<TKey, TVal>(size) {
    table.resize(this->tableSize);
    for (int i = 0; i < this->tableSize; ++i) {
        table[i] = TableEntry();
    }
}

template <typename TKey, typename TVal>
THashTableOpen<TKey, TVal>::THashTableOpen(
    const THashTableOpen& other)
    : IHeap<TKey, TVal>(other) {
    table = other.table;
}

template <typename TKey, typename TVal>
int THashTableOpen<TKey, TVal>::_hash2(int key) const {
    return key % this->tableSize;
}

template <typename TKey, typename TVal>
int THashTableOpen<TKey, TVal>::_find(const TKey& key) const {
    int pos = this->_hash(key);
    int startPos = pos;
    int trys = 1;
    while (1) {
        if (table[pos].state == TableEntryState::EMPTY)
            return -1;
        if (table[pos].state == TableEntryState::OCCUPIED
            && table[pos].pair.first() == key) {
            return pos;
        }
        pos = _hash2(trys + pos);
        trys++;
        if (pos == startPos) {
            return -1;
        }
    }
}

template <typename TKey, typename TVal>
bool THashTableOpen<TKey, TVal>::Insert(const TKey& key, const TVal& value) {
    if (_find(key) != -1) {
        throw std::logic_error("Key already exists");
    }
    if (this->elemCount == this->tableSize) {
        throw std::overflow_error("Hash table is full");
    }

    int pos = this->_hash(key);
    int trys = 1;
    while (table[pos].state == TableEntryState::OCCUPIED) {
        pos = _hash2(trys + pos);
        trys++;
    }

    table[pos] = TableEntry(key, value);
    ++this->elemCount;
    return true;
}

template <typename TKey, typename TVal>
bool THashTableOpen<TKey, TVal>::Insert(
    const THashTableOpen<TKey, TVal>& other) {
    for (int i = 0; i < other.tableSize; ++i) {
        if (_find(other.table[i].pair.first()) == -1
        && other.table[i].state == TableEntryState::OCCUPIED) {
            Insert(other.table[i].pair.first(),
                other.table[i].pair.second());
        }
    }
    return true;
}

template <typename TKey, typename TVal>
bool THashTableOpen<TKey, TVal>::Delete(const TKey& key) {
    int pos = _find(key);
    if (pos == -1) {
        throw std::out_of_range("Key not found in hash table");
    }

    table[pos].state = TableEntryState::DELETED;
    --this->elemCount;

    return true;
}

template <typename TKey, typename TVal>
TVal THashTableOpen<TKey, TVal>::Find(const TKey& key) const {
    int pos = _find(key);
    if (pos == -1) {
        throw std::out_of_range("Key not found in hash table");
    }

    return table[pos].pair.second();
}

template <typename TKey, typename TVal>
void THashTableOpen<TKey, TVal>::Clear() {
    for (int i = 0; i < this->tableSize; ++i) {
        table[i].state = TableEntryState::EMPTY;
    }
    this->elemCount = 0;
}

template <typename TKey, typename TVal>
std::ostream& operator<<(std::ostream& os,
        const THashTableOpen<TKey, TVal>& hash) {
    if (hash.count() == 0) {
        os << "Empty" << std::endl;
        return os;
    }
    for (size_t i = 0; i < hash.size(); ++i) {
        if (hash.table[i].state != TableEntryState::OCCUPIED)
            continue;
        os << hash.table[i].pair.first() << ": " << hash.table[i].pair.second();
        if (i < hash.size() - 1) {
            os << "\n";
        }
    }
    return os;
}
