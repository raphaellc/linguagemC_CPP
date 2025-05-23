#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <sstream> // for std::ostringstream

template <typename K, typename V>
class Node {
private:
    K key;
    V value;
    int height;
    Node<K, V>* left;
    Node<K, V>* right;

public:
    Node(K key, V value);  // Constructor declaration

    Node<K, V>* next(K other);

    bool isLeaf() const;

    std::string toString() const;

    K getKey() const;
    V getValue() const;
    int getHeight() const;
    Node<K, V>* getLeft() const;
    Node<K, V>* getRight() const;

    void setKey(K key);
    void setValue(V value);
    void setHeight(int height);
    void setLeft(Node<K, V>* left);
    void setRight(Node<K, V>* right);
};

#endif