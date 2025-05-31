// Copyright 2025 atikdd.t.me
#pragma once
#include <stdexcept>

class DSU {
    int _size;
    int *_parent;
    int *_rank;

 public:
    explicit DSU(int size = 0);
    ~DSU();
    void make_set(int elem);
    int find(int elem);
    void union_trivial(int first, int second);
    void union_by_rank(int first, int second);
    void clear();
};
