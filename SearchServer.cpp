#include "SearchServer.h"
#include <algorithm>
#include <iostream>
#include "ConverterJSON.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> result;
    for (auto &query: queries_input) {
        std::string word;
        std::map<std::string, int> uniqueWords;

        std::stringstream ss(query);
        while (getline(ss, word, ' ')) {
            uniqueWords[word];
        }
        std::map<int, int> docsTable; //doc_id, absoluteRelevance
        float absoluteRelevanceMax = 0;
        auto it = uniqueWords.begin();

        for (auto item: uniqueWords) {
            std::vector<Entry> docs = _index.GetWordCount(item.first);
            for (auto &doc: docs) {
                docsTable[doc.doc_id] += doc.count; //absoluteRelevance
                if (absoluteRelevanceMax < docsTable[doc.doc_id]) {
                    absoluteRelevanceMax = docsTable[doc.doc_id];
                }
            }
        }
        std::vector<RelativeIndex> RelativeIndex_vec;
        for (auto doc: docsTable) {
            float rank = 0;

            if (doc.second > 0) {
                rank = doc.second / absoluteRelevanceMax;
            }
            RelativeIndex RI;
            RI.doc_id = doc.first;
            RI.rank = rank;
            RelativeIndex_vec.push_back(RI);
        }

        std::sort(RelativeIndex_vec.begin(), RelativeIndex_vec.end(), [](RelativeIndex a, RelativeIndex b) {
            if (a.rank == b.rank) {
                return a.doc_id < b.doc_id;
            } else {
                return a.rank > b.rank;
            }
        });

        if (RelativeIndex_vec.size() > _responsesLimit) {
            RelativeIndex_vec.resize(_responsesLimit);
        }
        result.push_back(RelativeIndex_vec);
    }
    return result;
}

std::vector<std::vector<std::pair<int, float>>>
SearchServer::RelativeIndexToPair(std::vector<std::vector<RelativeIndex>> &result) {
    std::vector<std::vector<std::pair<int, float>>> answers;
    for (auto &query: result) {
        std::vector<std::pair<int, float>> answerPairs;
        for (auto &answer: query) {
            answerPairs.push_back(std::make_pair(answer.doc_id, answer.rank));
        }
        answers.push_back(answerPairs);
    }
    return answers;
}