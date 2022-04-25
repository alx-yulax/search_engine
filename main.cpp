#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {
    ConverterJSON conv;
    if (!conv.CheckConfig("0.1")) {
        return 1;
    }
    std::vector<std::string> docs = conv.GetTextDocuments();
    std::vector<std::string> queries = conv.GetRequests();
    int responsesLimit = conv.GetResponsesLimit();

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx, responsesLimit);
    std::vector<std::vector<RelativeIndex>> result = srv.search(queries);
    std::vector<std::vector<std::pair<int, float>>> answers = srv.RelativeIndexToPair(result);

    conv.PutAnswers(answers);

    return 0;
}

