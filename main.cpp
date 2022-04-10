#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"


int main( ) {

    InvertedIndex idx;
    ConverterJSON conv;

    idx.UpdateDocumentBase(conv.GetTextDocuments());

    const std::vector<std::string> requests{"m", "statement"};
    std::vector<std::vector<Entry>> result;

    for(auto& request : requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }

    return 0;
}

