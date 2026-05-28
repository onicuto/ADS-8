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
        T data;
        int freq;
        Node* leftChild;
        Node* rightChild;

        explicit Node(const T& val) : data(val), freq(1), leftChild(nullptr), rightChild(nullptr) {}
    };

    Node* treeRoot;

    Node* addNode(Node* cur, T val) {
        if (!cur) return new Node(val);
        if (val == cur->data) {
            ++cur->freq;
        } else if (val < cur->data) {
            cur->leftChild = addNode(cur->leftChild, val);
        } else {
            cur->rightChild = addNode(cur->rightChild, val);
        }
        return cur;
    }

    int computeHeight(Node* cur) const {
        if (!cur) return 0;
        int leftH = computeHeight(cur->leftChild);
        int rightH = computeHeight(cur->rightChild);
        return 1 + std::max(leftH, rightH);
    }

    Node* findNode(Node* cur, const T& val) const {
        if (!cur) return nullptr;
        if (val == cur->data) return cur;
        if (val < cur->data) return findNode(cur->leftChild, val);
        return findNode(cur->rightChild, val);
    }

    void eraseTree(Node* cur) {
        if (cur) {
            eraseTree(cur->leftChild);
            eraseTree(cur->rightChild);
            delete cur;
        }
    }

    void collectInOrder(Node* cur, std::vector<std::pair<T, int>>& outVec) const {
        if (cur) {
            collectInOrder(cur->leftChild, outVec);
            outVec.emplace_back(cur->data, cur->freq);
            collectInOrder(cur->rightChild, outVec);
        }
    }

 public:
    BST() : treeRoot(nullptr) {}
    ~BST() { eraseTree(treeRoot); }

    void insert(T val) {
        treeRoot = addNode(treeRoot, val);
    }

    int depth() const {
        int h = computeHeight(treeRoot);
        return h > 0 ? h - 1 : 0;
    }

    int search(const T& val) const {
        Node* node = findNode(treeRoot, val);
        return node ? node->freq : 0;
    }

    std::vector<std::pair<T, int>> symBypass() const {
        std::vector<std::pair<T, int>> result;
        collectInOrder(treeRoot, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_    }

    // Вспомогательная рекурсивная функция для вычисления глубины дерева
    int calculateHeight(TreeNode* currentNode) const {
        if (!currentNode) return -1;
        int leftHeight = calculateHeight(currentNode->leftChild);
        int rightHeight = calculateHeight(currentNode->rightChild);
        return 1 + std::max(leftHeight, rightHeight);
    }

    // Вспомогательная рекурсивная функция для поиска частоты слова
    int findFrequency(TreeNode* currentNode, const KeyType& key) const {
        if (!currentNode) return 0;
        if (key == currentNode->word) return currentNode->frequency;
        if (key < currentNode->word)
            return findFrequency(currentNode->leftChild, key);
        return findFrequency(currentNode->rightChild, key);
    }

    // Вспомогательная рекурсивная функция для удаления дерева
    void deleteTree(TreeNode* currentNode) {
        if (!currentNode) return;
        deleteTree(currentNode->leftChild);
        deleteTree(currentNode->rightChild);
        delete currentNode;
    }

 public:
    // Конструктор: создает пустое дерево
    TreeDictionary() : rootNode(nullptr) {}

    // Деструктор: удаляет все узлы дерева
    ~TreeDictionary() {
        deleteTree(rootNode);
    }

    // Публичный метод для вставки слова
    void insert(const KeyType& key) {
        insertNode(rootNode, key);
    }

    // Публичный метод для получения высоты дерева
    int depth() const {
        return calculateHeight(rootNode);
    }

    // Публичный метод для поиска частоты слова
    int search(const KeyType& key) const {
        return findFrequency(rootNode, key);
    }

    // Получение корневого узла (используется в alg.cpp для обхода)
    TreeNode* getRoot() const {
        return rootNode;
    }
};

#endif  // INCLUDE_TREE_DICTIONARY_H_        if (!node) return 0;
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
