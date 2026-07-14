#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    int len_s = (int)s.size();
    int len_d = (int)wordDict.size();
    std::vector<int> len_w;
    for (int i = 0; i < len_d; i++) {
      len_w.push_back((int)wordDict[i].size());
    }

    std::vector<int> results(len_s, 0);

    for (int i = 0; i < len_s; i++) {
      for (int j = 0; j < len_d; j++) {
        int k = i - len_w[j] + 1;
        if (k >= 0 && s.substr(k, len_w[j]) == wordDict[j]) {
          if (k == 0) {
            results[i] = 1;
          } else {
            results[i] = results[i] | results[k - 1];
          }
          if (results[i] == 1) continue;
        }
      }
    }

    return results[len_s - 1] == 1;
  }
};

int main() {
  string s = "leetcode";
  vector<string> wordDict = {"leet", "code"};

  Solution solution;
  auto result = solution.wordBreak(s, wordDict);

  std::cout << result << std::endl;

  return 0;
}