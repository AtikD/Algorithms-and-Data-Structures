// Copyright 2025 atikdd.ru

#pragma once

#include <queue.h>
#include <lstack.h>
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
    class InOrderIterator{
     private:
        LStack<Node*> _stack;
        Node* _current;

        void pushLeftBranch(Node* node) {
            while (node != nullptr) {
                _stack.push(node);
                node = node->left;
            }
        }

     public:
        explicit InOrderIterator(Node* root) : _current(nullptr) {
            pushLeftBranch(root);
            if (!_stack.empty()) {
                _current = _stack.top();
                _stack.pop();
                pushLeftBranch(_current->right);
            }
        }
        InOrderIterator() : _current(nullptr) {}
                bool operator==(const InOrderIterator& other) const {
            return _current == other._current;
        }

        bool operator!=(const InOrderIterator& other) const {
            return _current != other._current;
        }

        const T& operator*() const {
            if (_current == nullptr) {
                throw std::out_of_range("Iterator dereference out of range");
            }
            return _current->key;
        }

        InOrderIterator& operator++() {
            if (!_stack.empty()) {
                _current = _stack.top();
                _stack.pop();
                pushLeftBranch(_current->right);
            } else {
                _current = nullptr;
            }
            return *this;
        }

        InOrderIterator operator++(int) {
            InOrderIterator temp(*this);
            ++(*this);
            return temp;
        }
    };
    class LevelOrderIterator{
     private:
        struct QueueItem{
            Node* node;
            int level;
            QueueItem() : node(nullptr), level(0) {}
            QueueItem(Node* n, int l) : node(n), level(l){}
        };

        TQueue<QueueItem> _queue;
        Node* _current;
        int _currentLevel;

     public:
        explicit LevelOrderIterator(Node* root)
            : _current(nullptr), _currentLevel(0) {
            if (root != nullptr) {
                _queue.push(QueueItem(root, 0));

                QueueItem item = _queue.pop();
                _current = item.node;
                _currentLevel = item.level;

                if (_current->left) {
                    _queue.push(QueueItem(_current->left, _currentLevel + 1));
                }
                if (_current->right) {
                    _queue.push(QueueItem(_current->right, _currentLevel + 1));
                }
            }
        }

        LevelOrderIterator() : _current(nullptr), _currentLevel(0) {}

        bool operator==(const LevelOrderIterator& other) const {
            return _current == other._current;
        }

        bool operator!=(const LevelOrderIterator& other) const {
            return _current != other._current;
        }

        const T& operator*() const {
            if (_current == nullptr) {
                throw std::out_of_range("Iterator dereference out of range");
            }
            return _current->key;
        }

        int level() const {
            return _currentLevel;
        }

        LevelOrderIterator& operator++() {
            if (!_queue.is_empty()) {
                QueueItem item = _queue.pop();
                _current = item.node;
                _currentLevel = item.level;

                if (_current->left) {
                    _queue.push(QueueItem(_current->left, _currentLevel + 1));
                }
                if (_current->right) {
                    _queue.push(QueueItem(_current->right, _currentLevel + 1));
                }
            } else {
                _current = nullptr;
            }
            return *this;
        }

        LevelOrderIterator operator++(int) {
            LevelOrderIterator temp(*this);
            ++(*this);
            return temp;
        }
    };

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
    const Node* getRoot() const {
        return _root;
    }

    InOrderIterator beginInOrder() const {
        return InOrderIterator(_root);
    }

    InOrderIterator endInOrder() const {
        return InOrderIterator();
    }

    LevelOrderIterator beginLevelOrder() const {
        return LevelOrderIterator(_root);
    }

    LevelOrderIterator endLevelOrder() const {
        return LevelOrderIterator();
    }

    InOrderIterator begin() const {
        return beginInOrder();
    }

    InOrderIterator end() const {
        return endInOrder();
    }
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
