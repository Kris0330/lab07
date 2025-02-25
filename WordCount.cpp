#include "WordCount.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

WordCount::WordCount() {

}

std::string WordCount::makeValidWord(std::string word) {
    std::string validWord = "";
    for (size_t i = 0; i < word.length(); i++) {
        if (isalpha(word[i]) || (i > 0 && i < word.length() - 1 && (word[i] == '-' || word[i] == '\''))) {
            validWord += tolower(word[i]);
        }
    }
    return validWord;
}

int WordCount::incrWordCount(std::string word) {
    word = makeValidWord(word);
    if (word.empty()) return 0;

    size_t index = hash(word);
    for (auto &entry : table[index]) {
        if (entry.first == word) {
            entry.second++;
            return entry.second;
        }
    }

    table[index].push_back({word, 1});
    return 1;
}

void WordCount::addAllWords(string text) {
    istringstream stream(text);
    string word;
    while (stream >> word) {
        word = makeValidWord(word);
        if (!word.empty()) {
            incrWordCount(word);
        }
    }
}

void WordCount::dumpWordsSortedByWord(ostream &out) const {
    map<string, int> sortedWords;

    for (size_t i = 0; i < CAPACITY; i++) {
        for (const auto &entry : table[i]) {
            sortedWords[entry.first] = entry.second;
        }
    }

    for (const auto &pair : sortedWords) {
        out << pair.first << "," << pair.second << endl;
    }
}

void WordCount::dumpWordsSortedByOccurence(ostream &out) const {
    vector<pair<int, string>> wordList;

    for (size_t i = 0; i < CAPACITY; i++) {
        for (const auto &entry : table[i]) {
            wordList.push_back(make_pair(entry.second, entry.first));
        }
    }

    sort(wordList.begin(), wordList.end(), [](const std::pair<int, std::string> &a, const std::pair<int, std::string> &b) {
        if (a.first != b.first) {
            return a.first > b.first;  
        }
        return a.second < b.second;  
    });

    for (const auto &pair : wordList) {
        out << pair.second << "," << pair.first << endl;
    }
}

size_t WordCount::hash(std::string word) const {
    size_t hashValue = 0;
    for (char c : word) {
        hashValue = hashValue * 31 + c;
    }
    return hashValue % CAPACITY;
}
