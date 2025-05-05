// Copyright 2025 atikdd.t.me
#include <dsu.h>
#include <stdexcept>

DSU::DSU(int size) : _size(size) {
    if (size < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }

    if (size > 0) {
        _parent = new int[size];
        _rank = new int[size];
        for (int i = 0; i < size; i++) {
            _parent[i] = i;
            _rank[i] = 0;
        }
    } else {
        _parent = nullptr;
        _rank = nullptr;
    }
}

DSU::~DSU() {
    clear();
}

void DSU::make_set(int elem) {
    if (elem <= 0) {
        throw std::invalid_argument("Element must be positive");
    }

    if (elem <= _size) {
        throw std::invalid_argument("Element already exists");
    }

    int *new_parent = new int[elem];
    int *new_rank = new int[elem];

    for (int i = 0; i < _size; i++) {
        new_parent[i] = _parent[i];
        new_rank[i] = _rank[i];
    }


    for (int i = _size; i < elem; i++) {
        new_parent[i] = i;
        new_rank[i] = 0;
    }


    delete[] _parent;
    delete[] _rank;
    _parent = new_parent;
    _rank = new_rank;
    _size = elem;
}

int DSU::find(int elem) {
    if (elem <= 0 || elem > _size) {
        throw std::logic_error("Input Error: element out of range");
    }

    int idx = elem - 1;
    if (_parent[idx] != idx) {
        _parent[idx] = find(_parent[idx] + 1) - 1;
    }
    return _parent[idx] + 1;
}

void DSU::union_trivial(int first, int second) {
    int rep1 = find(first);
    int rep2 = find(second);

    if (rep1 == rep2) {
        return;
    }

    _parent[rep2 - 1] = rep1 - 1;
}

void DSU::union_by_rank(int first, int second) {
    int rep1 = find(first);
    int rep2 = find(second);

    if (rep1 == rep2) {
        return;
    }

    int idx1 = rep1 - 1;
    int idx2 = rep2 - 1;

    if (_rank[idx1] < _rank[idx2]) {
        _parent[idx1] = idx2;
    } else if (_rank[idx1] > _rank[idx2]) {
        _parent[idx2] = idx1;
    } else {
        _parent[idx2] = idx1;
        _rank[idx1]++;
    }
}

void DSU::clear() {
    delete[] _parent;
    delete[] _rank;
    _parent = nullptr;
    _rank = nullptr;
    _size = 0;
}

