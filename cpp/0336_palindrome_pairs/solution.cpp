#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> palindromePairs(vector<string>& words) {
    std::vector<std::vector<int>> result;

    std::unordered_map<std::string, int> wordMap;
    for (int i = 0; i < (int)words.size(); i++) {
      wordMap[words[i]] = i;
    }

    for (int i = 0; i < (int)words.size(); i++) {
      const std::string& word = words[i];

      if (word == "") continue;

      if (wordMap.find("") != wordMap.end() && isPalindrome(word)) {
        int emptyIndex = wordMap[""];
        result.push_back({i, emptyIndex});
        result.push_back({emptyIndex, i});
      }

      std::string reversedWord = word;
      std::reverse(reversedWord.begin(), reversedWord.end());
      if (wordMap.find(reversedWord) != wordMap.end() &&
          wordMap[reversedWord] != i) {
        result.push_back({i, wordMap[reversedWord]});
      }

      for (int j = 0; j < (int)word.size(); j++) {
        std::string prefix = word.substr(0, j);
        std::string suffix = word.substr(j);

        if (isPalindrome(prefix) && prefix != "") {
          std::string reversedSuffix = suffix;
          std::reverse(reversedSuffix.begin(), reversedSuffix.end());
          if (wordMap.find(reversedSuffix) != wordMap.end() &&
              wordMap[reversedSuffix] != i) {
            result.push_back({wordMap[reversedSuffix], i});
          }
        }

        if (isPalindrome(suffix) && suffix != "") {
          std::string reversedPrefix = prefix;
          std::reverse(reversedPrefix.begin(), reversedPrefix.end());
          if (wordMap.find(reversedPrefix) != wordMap.end() &&
              wordMap[reversedPrefix] != i) {
            result.push_back({i, wordMap[reversedPrefix]});
          }
        }
      }
    }

    return result;
  }

 private:
  bool isPalindrome(const std::string& s) {
    int left = 0;
    int right = (int)s.size() - 1;
    while (left < right) {
      if (s[left] != s[right]) return false;
      left++;
      right--;
    }
    return true;
  }
};

int main() {
  std::vector<std::string> words = {"abcd", "dcba", "lls", "s", "sssll"};

  Solution solution;
  auto result = solution.palindromePairs(words);

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