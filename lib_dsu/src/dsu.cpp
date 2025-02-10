// Copyright 2025 atikdd.t.me
#include "../include/dsu.h"
#include <iostream>

DSU::DSU(int size) : _size(size) {
    if (size < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }
    _parent = new int[size];
    rank = new int[size];
    for (int i = 0; i < size; i++) {
        _parent[i] = i;
        rank[i] = 0;
    }
}

DSU::~DSU() {
    delete[] _parent;
    delete[] rank;
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

    if (rank[idx1] < rank[idx2]) {
        _parent[idx1] = idx2;
    } else if (rank[idx1] > rank[idx2]) {
        _parent[idx2] = idx1;
    } else {
        _parent[idx2] = idx1;
        rank[idx1]++;
    }
}

