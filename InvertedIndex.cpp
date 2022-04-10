#include "InvertedIndex.h"
#include <algorithm>
#include <iostream>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    docs = input_docs;
    for (int doc_id = 0; doc_id < docs.size(); ++doc_id) {
        size_t prev = 0,next;
        std::map<std::string, int> wordsCount;

        while ((next = docs[doc_id].find(" ", prev)) != std::string::npos) {
            std::string word = docs[doc_id].substr(prev, next - prev);
            if (word.length() > 0) {
                std::transform(word.begin(), word.end(), word.begin(), tolower);
                std::cout << word<< std::endl;
                ++wordsCount[word];
            }
            prev = next + 1;
        }
        for (const auto &it: wordsCount) {
            freq_dictionary[it.first].push_back(Entry(doc_id, it.second));
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    return freq_dictionary[word];
}