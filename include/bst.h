// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        int counter;
        Node* leftBranch;
        Node* rightBranch;

        explicit Node(const T& v) : value(v), counter(1), leftBranch(nullptr), rightBranch(nullptr) {}
    };

    Node* rootPtr;

    Node* insertNode(Node* cur, const T& v) {
        if (!cur) return new Node(v);
        if (v == cur->value) {
            ++cur->counter;
        } else if (v < cur->value) {
            cur->leftBranch = insertNode(cur->leftBranch, v);
        } else {
            cur->rightBranch = insertNode(cur->rightBranch, v);
        }
        return cur;
    }

    int calcDepth(Node* cur) const {
        if (!cur) return 0;
        int leftDep = calcDepth(cur->leftBranch);
        int rightDep = calcDepth(cur->rightBranch);
        return 1 + std::max(leftDep, rightDep);
    }

    Node* findNode(Node* cur, const T& v) const {
        if (!cur) return nullptr;
        if (v == cur->value) return cur;
        if (v < cur->value) return findNode(cur->leftBranch, v);
        return findNode(cur->rightBranch, v);
    }

    void freeTree(Node* cur) {
        if (cur) {
            freeTree(cur->leftBranch);
            freeTree(cur->rightBranch);
            delete cur;
        }
    }

    void inorderCollect(Node* cur, std::vector<std::pair<T, int>>& out) const {
        if (cur) {
            inorderCollect(cur->leftBranch, out);
            out.emplace_back(cur->value, cur->counter);
            inorderCollect(cur->rightBranch, out);
        }
    }

 public:
    BST() : rootPtr(nullptr) {}
    ~BST() { freeTree(rootPtr); }

    void insert(const T& v) {
        rootPtr = insertNode(rootPtr, v);
    }

    int depth() const {
        int h = calcDepth(rootPtr);
        return h > 0 ? h - 1 : 0;
    }

    int search(const T& v) const {
        Node* node = findNode(rootPtr, v);
        return node ? node->counter : 0;
    }

    std::vector<std::pair<T, int>> symBypass() const {
        std::vector<std::pair<T, int>> result;
        inorderCollect(rootPtr, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
