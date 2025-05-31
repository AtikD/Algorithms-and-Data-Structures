// Copyright 2025 atikdd.ru

#pragma once

#include <itable.h>
#include <bst.h>
#include <pair.h>
#include <stdexcept>


template <typename TKey, typename TVal>
class TBSTTable : public ITable<TKey, TVal> {
 private:
    TBinSearchTree<TPair<TKey, TVal>> _tree;

 public:
    TBSTTable() = default;
    TBSTTable(const TBSTTable& other) = default;
    ~TBSTTable() override = default;

    bool Insert(const TKey& key, const TVal& val) override;
    TVal Find(const TKey& key) const override;
    bool IsExists(const TKey& key) const override;
    bool Delete(const TKey& key) override;
    size_t GetSize() const override;
    void Clear() override;
};


template <typename TKey, typename TVal>
bool TBSTTable<TKey, TVal>::Insert(const TKey& key, const TVal& val) {
    TPair<TKey, TVal> pair(key, val);
    if (IsExists(key)) {
        return false;
    }
    return _tree.insert(pair);
}

template <typename TKey, typename TVal>
TVal TBSTTable<TKey, TVal>::Find(const TKey& key) const {
    TPair<TKey, TVal> search_pair(key, TVal());

    const TPair<TKey, TVal>* found = _tree.find(search_pair);
    if (found == nullptr) {
        throw std::runtime_error("Key not found");
    }

    return found->second();
}

template <typename TKey, typename TVal>
bool TBSTTable<TKey, TVal>::IsExists(const TKey& key) const {
    TPair<TKey, TVal> search_pair(key, TVal());
    return _tree.contains(search_pair);
}

template <typename TKey, typename TVal>
bool TBSTTable<TKey, TVal>::Delete(const TKey& key) {
    TPair<TKey, TVal> search_pair(key, TVal());
    return _tree.remove(search_pair);
}

template <typename TKey, typename TVal>
size_t TBSTTable<TKey, TVal>::GetSize() const {
    return _tree.size();
}

template <typename TKey, typename TVal>
void TBSTTable<TKey, TVal>::Clear() {
    _tree.clear();
}
