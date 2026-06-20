#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> letterCombinations(string digits) {
    vector<string> mapping = {"abc", "def",  "ghi", "jkl",
                              "mno", "pqrs", "tuv", "wxyz"};

    vector<string> result;

    for (const auto& digit : digits) {
      int index = digit - '2';

      vector<string> new_result;
      for (const auto& c : mapping[index]) {
        if (result.empty()) {
          new_result.push_back(string(1, c));
          continue;
        }
        for (const auto& str : result) {
          new_result.push_back(str + c);
        }
      }

      result = new_result;
    }

    return result;
  }
};

int main() {
  string digits = "23";

  Solution solution;
  auto result = solution.letterCombinations(digits);

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