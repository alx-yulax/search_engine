
#include "ConverterJSON.h"
#include <fstream>
#include <iostream>

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> input_docs;

    std::ifstream config("config.json");
    if (!config.is_open()) {
        std::cout << "Config file is missing" << std::endl;
        return input_docs;
    }

    nlohmann::json j_config;
    config >> j_config;
    config.close();

    if (j_config["files"].size() == 0) {
        std::cout << "Config: key files is empty!" << std::endl;
        return input_docs;
    }

    for (auto &item: j_config["files"]) {
        std::string path = item.get<std::string>();

        std::ifstream doc(path);
        if (!doc.is_open()) {
            std::cout << path << " is missing" << std::endl;
        } else {
            std::string word, words;
            int wordsCount = 0;

            while (!doc.eof()) {
                doc >> word;
                if (word.length() > 100) {
                    std::cout << word << " - word is too long" << std::endl;
                    continue;
                } else {
                    words += word + " ";
                    ++wordsCount;
                }

                if (wordsCount > 1000) {
                    std::cout << "in file: " << path << " more than 1000 words" << std::endl;
                    break;
                }
            }
            input_docs.push_back(words);
            doc.close();
        }
    }
    /*
     for (auto &words : input_docs){
        std::cout << words<< std::endl;
    }
    */
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream config("config.json");
    if (!config.is_open()) {
        std::cout << "Config file is missing" << std::endl;
    } else {
        nlohmann::json j_config;
        config >> j_config;
        config.close();

        int responsesLimit = j_config["max_responses"].get<int>();
        if (responsesLimit > 0) {
            return responsesLimit;
        }
    }
    return 5; // default max_responses
}

std::vector<std::string> ConverterJSON::GetRequests() {

}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {

}