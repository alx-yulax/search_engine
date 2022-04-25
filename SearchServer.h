
#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include "InvertedIndex.h"
#include <sstream>
#include <map>

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex &other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex &idx, int respLimit = 5) : _index(idx) {
        if (respLimit < 1)
            respLimit = 5;
        _responsesLimit = respLimit;
    };

/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input);

    std::vector<std::vector<std::pair<int, float>>> RelativeIndexToPair(std::vector<std::vector<RelativeIndex>> &result);

private:
    InvertedIndex _index;
    int _responsesLimit;
};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
