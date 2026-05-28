// Copyright 2021 NNTU-CS
#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& dict, const char* filename) {
    std::ifstream source(filename);
    if (!source.is_open()) {
        std::cerr << "Error: cannot open " << filename << std::endl;
        return;
    }

    std::string token;
    char ch;
    while (source.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            token += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        } else {
            if (!token.empty()) {
                dict.insert(token);
                token.clear();
            }
        }
    }
    if (!token.empty()) {
        dict.insert(token);
    }
}

void printFreq(BST<std::string>& dict) {
    auto items = dict.symBypass();
    std::sort(items.begin(), items.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    std::ofstream outFile("result/freq.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error: cannot create result/freq.txt" << std::endl;
        return;
    }

    for (const auto& entry : items) {
        std::cout << entry.first << " " << entry.second << std::endl;
        outFile << entry.first << " " << entry.second << std::endl;
    }
}
