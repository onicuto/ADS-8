// Copyright 2021 NNTU-CS
#include "bst.h"

#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::string curWord;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            curWord += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        } else {
            if (!curWord.empty()) {
                tree.insert(curWord);
                curWord.clear();
            }
        }
    }
    if (!curWord.empty()) {
        tree.insert(curWord);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.symBypass();
    std::sort(words.begin(), words.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    std::ofstream out("result/freq.txt");
    if (!out.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл result/freq.txt" << std::endl;
        return;
    }

    for (const auto& pair : words) {
        std::cout << pair.first << " " << pair.second << std::endl;
        out << pair.first << " " << pair.second << std::endl;
    }

    out.close();
}
}
