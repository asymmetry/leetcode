#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    auto result = _wordBreak(std::string_view(s), wordDict);
    return result;
  }

  std::vector<std::string> _wordBreak(std::string_view s,
                                      std::vector<std::string>& wordDict) {
    int len_s = (int)s.size();

    std::vector<std::string> result;
    for (const auto& word : wordDict) {
      int len_w = (int)word.size();
      int k = len_s - len_w;
      if (k >= 0 && s.substr(k, len_w) == word) {
        if (k == 0) {
          result.push_back(word);
        } else {
          auto res = _wordBreak(s.substr(0, k), wordDict);
          for (auto r : res) {
            r.push_back(' ');
            r.append(word);
            result.push_back(r);
          }
        }
      }
    }

    return result;
  }
};

int main() {
  string s = "catsanddog";
  vector<string> wordDict = {"cats", "cat", "and", "sand", "dog"};

  Solution solution;
  auto result = solution.wordBreak(s, wordDict);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i];
    if (i != result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}