#include <iostream>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findSubstring(string s, vector<string>& words) {
    std::string_view sw(s);

    int len_s = (int)s.size();
    int len_words = (int)words.size();
    int len_word = (int)words[0].size();
    int len_sub = len_words * len_word;

    std::unordered_map<std::string_view, int> word_map;
    for (const auto& word : words) {
      if (word_map.find(word) != word_map.end()) {
        word_map[word]++;
      } else {
        word_map[word] = 1;
      }
    }

    vector<int> result;

    std::unordered_map<std::string_view, int> test;
    for (int i = 0; i <= len_s - len_sub; i++) {
      test.clear();

      auto sub_str = sw.substr(i, len_sub);

      for (int j = 0; j < len_sub; j += len_word) {
        auto sub_str_w = sub_str.substr(j, len_word);

        if (test.find(sub_str_w) != test.end()) {
          test[sub_str_w]++;
        } else {
          test[sub_str_w] = 1;
        }
      }

      bool found = true;
      for (const auto& pair : test) {
        if (word_map.find(pair.first) == word_map.end()) {
          found = false;
          break;
        } else if (word_map[pair.first] != pair.second) {
          found = false;
          break;
        }
      }

      if (found) {
        result.push_back(i);
      }
    }

    return result;
  }
};

int main() {
  string s = "barfoofoobarthefoobarman";
  vector<string> words = {"bar","foo","the"};

  Solution solution;
  auto result = solution.findSubstring(s, words);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); ++i) {
    if (i != (int)result.size() - 1) {
      std::cout << result[i] << ",";
    } else {
      std::cout << result[i];
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}