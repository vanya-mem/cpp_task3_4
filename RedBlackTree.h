#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <string>

enum Color { RED, BLACK };

template <typename T>
class RedBlackTree {
private:
    struct Node {
        T data;
        bool color;
        Node* left;
        Node* right;
        Node* parent;

        Node(T data)
            : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void rotateLeft(Node*&);
    void rotateRight(Node*&);
    void fixInsert(Node*&);
    void inorderHelper(Node*) const;
    Node* searchHelper(Node*, T) const;

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const T& data);
    bool search(const T& data) const;
    void inorder() const;
};

template <typename T>
void RedBlackTree<T>::rotateLeft(Node*& node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (node->right != nullptr)
        node->right->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

template <typename T>
void RedBlackTree<T>::rotateRight(Node*& node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != nullptr)
        node->left->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

template <typename T>
void RedBlackTree<T>::fixInsert(Node*& node) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;

    while ((node != root) && (node->color != BLACK) &&
           (node->parent->color == RED)) {

        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }

                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node* uncle = grandparent->left;

            if ((uncle != nullptr) && (uncle->color == RED)) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }

                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::insert(const T& data) {
    Node* node = new Node(data);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;

    if (y == nullptr)
        root = node;
    else if (node->data < y->data)
        y->left = node;
    else
        y->right = node;

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == nullptr)
        return;

    fixInsert(node);
}

template <typename T>
void RedBlackTree<T>::inorderHelper(Node* node) const {
    if (node == nullptr)
        return;

    inorderHelper(node->left);
    std::cout << node->data << " ";
    inorderHelper(node->right);
}

template <typename T>
void RedBlackTree<T>::inorder() const {
    inorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::searchHelper(Node* node, T key) const {
    if (node == nullptr || node->data == key)
        return node;

    if (key < node->data)
        return searchHelper(node->left, key);

    return searchHelper(node->right, key);
}

template <typename T>
bool RedBlackTree<T>::search(const T& key) const {
    return searchHelper(root, key) != nullptr;
}

#endif
