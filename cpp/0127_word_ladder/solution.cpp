#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    std::unordered_set<string> wordSet(wordList.begin(), wordList.end());
    wordSet.erase(beginWord);

    std::unordered_set<char> charSet;
    for (const auto& word : wordSet) {
      charSet.insert(word.begin(), word.end());
    }

    std::unordered_set<string> tests;
    tests.insert(beginWord);

    int level = 1;
    while (!tests.empty()) {
      std::unordered_set<string> new_tests;

      for (auto& word : tests) {
        if (word == endWord) {
          return level;
        } else {
          for (int i = 0; i < (int)word.size(); i++) {
            for (const auto& c : charSet) {
              string new_word(word);
              new_word[i] = c;
              if (wordSet.find(new_word) != wordSet.end()) {
                new_tests.insert(new_word);
              }
            }
          }
        }
      }

      for (const auto& word : new_tests) {
        wordSet.erase(word);
      }

      tests = std::move(new_tests);
      level++;
    }

    return 0;
  }
};

int main() {
  string beginWord = "hit";
  string endWord = "cog";
  vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

  Solution solution;
  auto result = solution.ladderLength(beginWord, endWord, wordList);

  std::cout << result << std::endl;

  return 0;
}