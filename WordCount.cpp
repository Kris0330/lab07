#include "WordCount.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// ✅ 構造函數（避免 undefined reference）
WordCount::WordCount() {
    // Hash table 內的 vector 會自動初始化，這裡不用額外處理
}

// ✅ 清理單詞函數，轉換為有效單詞
std::string WordCount::makeValidWord(std::string word) {
    std::string validWord = "";
    for (size_t i = 0; i < word.length(); i++) {
        if (isalpha(word[i]) || (i > 0 && i < word.length() - 1 && (word[i] == '-' || word[i] == '\''))) {
            validWord += tolower(word[i]);
        }
    }
    return validWord;
}

// ✅ 增加單詞計數（處理 undefined reference）
int WordCount::incrWordCount(std::string word) {
    word = makeValidWord(word);  // 確保單詞格式正確
    if (word.empty()) return 0;

    size_t index = hash(word);  // 計算 hash 值，獲取索引
    for (auto &entry : table[index]) {
        if (entry.first == word) {
            entry.second++;  // 增加計數
            return entry.second;
        }
    }

    // 單詞不存在，新增並設為 1
    table[index].push_back({word, 1});
    return 1;
}

// ✅ 解析文本並加入 hash table
void WordCount::addAllWords(string text) {
    istringstream stream(text);
    string word;
    while (stream >> word) {
        word = makeValidWord(word);  // 確保單詞是有效的
        if (!word.empty()) {
            incrWordCount(word);
        }
    }
}

// ✅ 根據字母順序輸出
void WordCount::dumpWordsSortedByWord(ostream &out) const {
    map<string, int> sortedWords;

    // 遍歷 Hash Table
    for (int i = 0; i < CAPACITY; i++) {
        for (const auto &entry : table[i]) {
            sortedWords[entry.first] = entry.second;
        }
    }

    // 輸出結果
    for (const auto &pair : sortedWords) {
        out << pair.first << "," << pair.second << endl;
    }
}

// ✅ 根據出現次數輸出（降序）
void WordCount::dumpWordsSortedByOccurence(ostream &out) const {
    vector<pair<int, string>> wordList;

    // 遍歷 Hash Table
    for (int i = 0; i < CAPACITY; i++) {
        for (const auto &entry : table[i]) {
            wordList.push_back(make_pair(entry.second, entry.first));
        }
    }

    // 按出現次數降序排序，次數相同時按字母順序排序
    sort(wordList.begin(), wordList.end(), [](const pair<int, string> &a, const pair<int, string> &b) {
        if (a.first != b.first) {
            return a.first > b.first; // 出現次數降序
        }
        return a.second < b.second;  // 次數相同時按字母順序
    });

    // 輸出結果
    for (const auto &pair : wordList) {
        out << pair.second << "," << pair.first << endl;
    }
}

// ✅ Hash 函數
size_t WordCount::hash(std::string word) const {
    size_t hashValue = 0;
    for (char c : word) {
        hashValue = hashValue * 31 + c; // 簡單 hash 函數
    }
    return hashValue % CAPACITY;
}

