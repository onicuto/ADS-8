#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& freqTree, const char* inputFile) {
    std::ifstream fileStream(inputFile);
    if (!fileStream.is_open()) {
        std::cerr << "Error: cannot open " << inputFile << std::endl;
        return;
    }

    std::string buffer;
    char symbol;
    while (fileStream.get(symbol)) {
        if (std::isalpha(static_cast<unsigned char>(symbol))) {
            buffer += static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
        } else {
            if (!buffer.empty()) {
                freqTree.insert(buffer);
                buffer.clear();
            }
        }
    }
    if (!buffer.empty()) {
        freqTree.insert(buffer);
    }
}

void printFreq(BST<std::string>& freqTree) {
    auto entries = freqTree.symBypass();
    std::sort(entries.begin(), entries.end(),
              [](const auto& firstPair, const auto& secondPair) {
                  return firstPair.second > secondPair.second;
              });

    std::ofstream outputFile("result/freq.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: cannot create result/freq.txt" << std::endl;
        return;
    }

    for (const auto& entry : entries) {
        std::cout << entry.first << " " << entry.second << std::endl;
        outputFile << entry.first << " " << entry.second << std::endl;
    }
}    auto words = tree.symBypass();
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
