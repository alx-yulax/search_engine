#include "InvertedIndex.h"
#include <algorithm>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    docs = input_docs;
    freq_dictionary.clear();
    for (int doc_id = 0; doc_id < docs.size(); ++doc_id) {
        size_t prev = 0,next;
        std::map<std::string, int> wordsCount;

        while ((next = docs[doc_id].find(" ", prev)) != std::string::npos) {
            std::string word = docs[doc_id].substr(prev, next - prev);
            if (word.length() > 0) {
                std::transform(word.begin(), word.end(), word.begin(), tolower);
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
    auto search = freq_dictionary.find(word);
    if (search != freq_dictionary.end()) {
        return search->second;
    } else {
        std::vector<Entry> empty;
        return empty;
    }
}