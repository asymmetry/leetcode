#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<string>> findLadders(string beginWord, string endWord,
                                     vector<string>& wordList) {
    std::unordered_map<string, int> wordMap;
    for (int i = 0; i < (int)wordList.size(); i++) {
      wordMap[wordList[i]] = i;
    }
    wordMap.erase(beginWord);

    std::unordered_set<char> charSet;
    for (const auto& [word, _] : wordMap) {
      charSet.insert(word.begin(), word.end());
    }

    wordList.push_back(beginWord);
    wordMap[beginWord] = (int)wordList.size() - 1;

    std::unordered_map<string, std::vector<std::vector<int>>> tests;
    tests[beginWord] = {{wordMap[beginWord]}};

    while (!tests.empty()) {
      std::unordered_map<string, std::vector<std::vector<int>>> new_tests;

      for (auto& [word, history] : tests) {
        if (word == endWord) {
          std::vector<std::vector<string>> result;
          for (const auto& h : history) {
            std::vector<string> path;
            for (int index : h) {
              path.push_back(wordList[index]);
            }
            result.push_back(path);
          }
          return result;
        } else {
          for (int i = 0; i < (int)word.size(); i++) {
            for (const auto& c : charSet) {
              string new_word(word);
              new_word[i] = c;
              if (wordMap.find(new_word) != wordMap.end()) {
                for (auto h : history) {
                  h.push_back(wordMap[new_word]);
                  new_tests[new_word].push_back(h);
                }
              }
            }
          }
        }
      }

      for (const auto& [word, _] : new_tests) {
        wordMap.erase(word);
      }

      tests = std::move(new_tests);
    }

    return {};
  }
};

int main() {
  string beginWord = "hit";
  string endWord = "cog";
  vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

  Solution solution;
  auto result = solution.findLadders(beginWord, endWord, wordList);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "[";
    for (size_t j = 0; j < result[i].size(); ++j) {
      std::cout << result[i][j];
      if (j + 1 < result[i].size()) std::cout << ",";
    }
    std::cout << "]";
    if (i + 1 < result.size()) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}