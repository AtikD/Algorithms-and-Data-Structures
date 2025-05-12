// Copyright 2025 atikdd.ru

#pragma once

#include <stdexcept>

template <typename T>
class TBinSearchTree {
 private:
    struct Node {
        T key;
        Node* left;
        Node* right;

        explicit Node(const T& k)
            : key(k), left(nullptr), right(nullptr) {}
    };

    Node* _root;
    size_t _size;

    Node* findNode(Node* node, const T& key) const;
    Node* insertNode(Node* node, const T& key);
    Node* removeNode(Node* node, const T& key);
    Node* findMin(Node* node) const;
    void clearTree(Node* node);
    void copyTree(Node* src, Node*& dest);

 public:
    TBinSearchTree();
    TBinSearchTree(const TBinSearchTree& other);
    ~TBinSearchTree();

    
    bool isEmpty() const;
    size_t size() const;
    bool contains(const T& key) const;
    const T* find(const T& key) const;
    T* find(const T& key);
    bool insert(const T& key);
    bool remove(const T& key);
    void clear();
    const Node* getRoot() const{
        return _root;
    };
};


template <typename T>
TBinSearchTree<T>::TBinSearchTree() : _root(nullptr), _size(0) {}

template <typename T>
TBinSearchTree<T>::TBinSearchTree(const TBinSearchTree& other)
    : _root(nullptr), _size(0) {
    copyTree(other._root, _root);
    _size = other._size;
}

template <typename T>
TBinSearchTree<T>::~TBinSearchTree() {
    clear();
}

template <typename T>
void TBinSearchTree<T>::copyTree(Node* src, Node*& dest) {
    if (src == nullptr) {
        dest = nullptr;
        return;
    }

    dest = new Node(src->key);
    copyTree(src->left, dest->left);
    copyTree(src->right, dest->right);
}

template <typename T>
bool TBinSearchTree<T>::isEmpty() const {
    return _root == nullptr;
}

template <typename T>
size_t TBinSearchTree<T>::size() const {
    return _size;
}

template <typename T>
typename TBinSearchTree<T>::Node*
TBinSearchTree<T>::findNode(Node* node, const T& key) const {
    if (node == nullptr || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return findNode(node->left, key);
    } else {
        return findNode(node->right, key);
    }
}

template <typename T>
bool TBinSearchTree<T>::contains(const T& key) const {
    return findNode(_root, key) != nullptr;
}

template <typename T>
const T* TBinSearchTree<T>::find(const T& key) const {
    Node* node = findNode(_root, key);
    if (node == nullptr) {
        return nullptr;
    }
    return &(node->key);
}

template <typename T>
T* TBinSearchTree<T>::find(const T& key) {
    Node* node = findNode(_root, key);
    if (node == nullptr) {
        return nullptr;
    }
    return &(node->key);
}

template <typename T>
typename TBinSearchTree<T>::Node*
TBinSearchTree<T>::insertNode(Node* node, const T& key) {
    if (node == nullptr) {
        _size++;
        return new Node(key);
    }

    if (key == node->key) {
        node->key = key;
        return node;
    } else if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else {
        node->right = insertNode(node->right, key);
    }
    return node;
}

template <typename T>
bool TBinSearchTree<T>::insert(const T& key) {
    size_t oldSize = _size;
    _root = insertNode(_root, key);
    return _size > oldSize;
}

template <typename T>
typename TBinSearchTree<T>::Node*
TBinSearchTree<T>::findMin(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

template <typename T>
typename TBinSearchTree<T>::Node*
TBinSearchTree<T>::removeNode(Node* node, const T& key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key < node->key) {
        node->left = removeNode(node->left, key);
    } else if (key > node->key) {
        node->right = removeNode(node->right, key);
    } else {
        // Найден узел для удаления

        // Случай 1: Узел без потомков
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            _size--;
            return nullptr;
        }

        // Случай 2: Узел с одним потомком
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            _size--;
            return temp;
        }

        if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            _size--;
            return temp;
        }

        // Случай 3: Узел с двумя потомками
        // Находим минимальный узел в правом поддереве
        Node* successor = findMin(node->right);

        // Копируем ключ преемника
        node->key = successor->key;

        // Удаляем преемника
        node->right = removeNode(node->right, successor->key);
    }

    return node;
}

template <typename T>
bool TBinSearchTree<T>::remove(const T& key) {
    size_t oldSize = _size;
    _root = removeNode(_root, key);

    return _size < oldSize;
}

template <typename T>
void TBinSearchTree<T>::clearTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

template <typename T>
void TBinSearchTree<T>::clear() {
    clearTree(_root);
    _root = nullptr;
    _size = 0;
}
