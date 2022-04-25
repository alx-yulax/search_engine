
#include "ConverterJSON.h"
#include "SearchServer.h"
#include <iostream>

void ConverterJSON::GetText(int doc_id, std::string path, std::map<int, std::string> &input_docs_Sorted) {
    std::string word, words = "";
    int wordsCount = 0;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << path << " is missing" << std::endl;
    } else {
        while (!file.eof()) {
            file >> word;
            if (word.length() > 100) {
                std::cout << word << " - word is too long (skip)" << std::endl;
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
        file.close();
    }
    input_docs_access.lock();
    input_docs_Sorted[doc_id] = words;
    input_docs_access.unlock();
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> input_docs;

    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cout << "Config file is missing" << std::endl;
        return input_docs;
    }

    nlohmann::json j;
    file >> j;
    file.close();

    if (j["files"].size() == 0) {
        std::cout << "Config: key files is empty!" << std::endl;
        return input_docs;
    }

    std::vector<std::thread> threads;
    std::map<int, std::string> input_docs_Sorted;

    for (int doc_id = 0; doc_id < j["files"].size(); ++doc_id) {
        std::string path = j["files"][doc_id].get<std::string>();
        threads.emplace_back([this, doc_id, path, &input_docs_Sorted]() {
            this->GetText(doc_id, path, input_docs_Sorted);
        });
    }

    for (auto &currentThread: threads) {
        currentThread.join();
    }

    for (auto &item: input_docs_Sorted) {
        input_docs.push_back(item.second);
    }
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cout << "Config file is missing" << std::endl;
    } else {
        nlohmann::json j;
        file >> j;
        file.close();
        if (!j["config"].is_null()) {
            if (!j["config"]["max_responses"].is_null()) {
                int responsesLimit = j["config"]["max_responses"].get<int>();
                if (responsesLimit > 0) {
                    return responsesLimit;
                }
            }
        }
    }
    return 5; // default max_responses
}


std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> requests;

    std::ifstream file("requests.json");
    if (!file.is_open()) {
        std::cout << "requests file is missing" << std::endl;
        return requests;
    }

    nlohmann::json j;
    file >> j;
    file.close();

    if (j["requests"].size() == 0) {
        std::cout << "requests file is empty!" << std::endl;
        return requests;
    }

    for (int ind_requests = 0; ind_requests < j["requests"].size() && ind_requests <= 1000; ++ind_requests) {
        std::string word, words, wordsToCheck = j["requests"][ind_requests].get<std::string>();
        int wordsCount = 0;

        std::stringstream ss(wordsToCheck);
        while (getline(ss, word, ' ')) {
            ++wordsCount;
            if (wordsCount > 10) {
                std::cout << "request #" << ind_requests << "has more then 10 words" << std::endl;
                break;
            }
            words += word + " ";
        }
        requests.push_back(words);
    }
    return requests;
}

bool ConverterJSON::CheckConfig(std::string currentVersion) {
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cout << "Config file is missing" << std::endl;
        return false;
    }
    nlohmann::json j;
    file >> j;
    file.close();

    if (j["config"].is_null()) {
        std::cout << "Config file is empty" << std::endl;
        return false;
    } else {
        if (!j["config"]["name"].is_null()) {
            std::cout << j["config"]["name"].get<std::string>() << std::endl;
        }
        if (!j["config"]["version"].is_null()) {
            float currentVersionF = std::stof(currentVersion);
            float configVersionF = std::stof(j["config"]["version"].get<std::string>());
            if (currentVersionF == configVersionF) {
                std::cout << "version: " << currentVersionF << std::endl;
                return true;
            } else if (currentVersionF > configVersionF) {
                std::cout << "Config.json has incorrect file version" << std::endl;
                std::cout << "Please update the config file" << std::endl;
                return false;
            } else {
                std::cout << "Config.json has incorrect file version" << std::endl;
                std::cout << "Please update the search engine" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Wrong config" << std::endl;
    return false;
}

void ConverterJSON::PutAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {

    nlohmann::json j;

    for (int i = 0; i < answers.size(); ++i) {
        std::string requestId = std::to_string(i + 1);
        while (requestId.length() < 3) {
            requestId = "0" + requestId;
        }
        requestId = "request" + requestId;

        if (answers[i].size() == 0) {
            j["answers"][requestId]["result"] = false;
        } else {
            j["answers"][requestId]["result"] = true;
            for (auto &doc: answers[i]) {
                nlohmann::json jDoc;
                jDoc["docid"] = doc.first;
                jDoc["rank"] = doc.second;
                j["answers"][requestId]["relevance"].push_back(jDoc);
            }
        }
    }

    std::ofstream f_out("answers.json");
    f_out << j;
    f_out.close();
}