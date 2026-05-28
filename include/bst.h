// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <utility>
#include <vector>
#include <string>

template <typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        explicit Node(T k) : key(std::move(k)), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, T value) {
        if (!node) return new Node(std::move(value));
        if (value == node->key) {
            ++node->count;
        } else if (value < node->key) {
            node->left = insert(node->left, std::move(value));
        } else {
            node->right = insert(node->right, std::move(value));
        }
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int lDepth = depth(node->left);
        int rDepth = depth(node->right);
        return 1 + std::max(lDepth, rDepth);
    }

    Node* search(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value == node->key) return node;
        if (value < node->key) return search(node->left, value);
        return search(node->right, value);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void symBypass(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node) {
            symBypass(node->left, result);
            result.emplace_back(node->key, node->count);
            symBypass(node->right, result);
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(T value) {
        root = insert(root, std::move(value));
    }

    int depth() const {
        int d = depth(root);
        return d > 0 ? d - 1 : 0;
    }

    int search(const T& value) const {
        Node* node = search(root, value);
        return node ? node->count : 0;
    }

    std::vector<std::pair<T, int>> symBypass() const {
        std::vector<std::pair<T, int>> result;
        symBypass(root, result);
        return result;
    }
};
void makeTree(BST<std::string>& tree, const std::string& filename);

void printFreq(const BST<std::string>& tree);
#endif  // INCLUDE_BST_H_
