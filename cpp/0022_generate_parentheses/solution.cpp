#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    vector<unordered_set<string>> results(n + 1);
    results[0].insert("");

    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < i; ++j) {
        for (const auto& left : results[j]) {
          for (const auto& right : results[i - 1 - j]) {
            results[i].insert("(" + left + ")" + right);
          }
        }
      }
    }

    vector<string> result(results[n].begin(), results[n].end());

    return result;
  }
};

int main() {
  int n = 3;

  Solution s;
  auto result = s.generateParenthesis(n);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    if (i != result.size() - 1) {
      std::cout << result[i] << ",";
    } else {
      std::cout << result[i];
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}