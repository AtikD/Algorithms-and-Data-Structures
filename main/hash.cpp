// Copyright 2025 atikdd.ru
#include <hash_chained.h>
#include <hash_opened.h>
#include <iostream>
#include <string>


void MergeByChain() {
    THashTableChained<std::string, int> hashOp1;
    hashOp1.Insert("lampshade", 1);
    hashOp1.Insert("cinema", 2);
    hashOp1.Insert("airplane", 3);
    hashOp1.Insert("person", 4);

    THashTableChained<std::string, int> hashOp2;
    hashOp2.Insert("cinema", 15);
    hashOp2.Insert("music", 16);
    hashOp2.Insert("airplane", 17);

    hashOp1.Insert(hashOp2);
    std::cout << "\nHash table 1 after merge:\n";
    std::cout << hashOp1;

    hashOp2.Insert(hashOp1);
    std::cout << "\nHash table 2 after merge:\n";
    std::cout << hashOp2;
}

void MergeByOpen() {
    THashTableOpen<std::string, int> hashOp1;
    hashOp1.Insert("lampshade", 1);
    hashOp1.Insert("cinema", 2);
    hashOp1.Insert("airplane", 3);
    hashOp1.Insert("person", 4);

    THashTableOpen<std::string, int> hashOp2;
    hashOp2.Insert("cinema", 15);
    hashOp2.Insert("music", 16);
    hashOp2.Insert("airplane", 17);

    hashOp1.Insert(hashOp2);
    std::cout << "\nHash table 1 after merge:\n";
    std::cout << hashOp1;

    hashOp2.Insert(hashOp1);
    std::cout << "\nHash table 2 after merge:\n";
    std::cout << hashOp2;
}

int main() {
    MergeByChain();
    std::cout << "\n\n";
    MergeByOpen();
    return 0;
}
