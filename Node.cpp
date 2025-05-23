#include "Node.h"

template <typename K, typename V>
Node<K, V>::Node(K key, V value) : key(key), value(value), height(1), left(nullptr), right(nullptr) {}

template <typename K, typename V>
Node<K, V>* Node<K, V>::next(K other) {
    return other < key ? left : right;
}

template <typename K, typename V>
bool Node<K, V>::isLeaf() const {
    return left == nullptr && right == nullptr;
}

template <typename K, typename V>
std::string Node<K, V>::toString() const {
    std::ostringstream oss;
    oss << key;
    return oss.str();
}

template <typename K, typename V>
K Node<K, V>::getKey() const {
    return key;
}

template <typename K, typename V>
V Node<K, V>::getValue() const {
    return value;
}

template <typename K, typename V>
int Node<K, V>::getHeight() const {
    return height;
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::getLeft() const {
    return left;
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::getRight() const {
    return right;
}

template <typename K, typename V>
void Node<K, V>::setKey(K key) {
    this->key = key;
}

template <typename K, typename V>
void Node<K, V>::setValue(V value) {
    this->value = value;
}

template <typename K, typename V>
void Node<K, V>::setHeight(int height) {
    this->height = height;
}

template <typename K, typename V>
void Node<K, V>::setLeft(Node<K, V>* left) {
    this->left = left;
}

template <typename K, typename V>
void Node<K, V>::setRight(Node<K, V>* right) {
    this->right = right;
}