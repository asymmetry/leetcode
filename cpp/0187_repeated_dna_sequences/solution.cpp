#include <iostream>
#include <string_view>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> findRepeatedDnaSequences(string s) {
    std::unordered_set<std::string_view> set;
    std::unordered_set<std::string_view> res;

    int len = (int)s.size();
    std::string_view sv(s);
    for (int i = 0; i < len - 9; i++) {
      std::string_view ss = sv.substr(i, 10);
      if (set.find(ss) != set.end()) {
        res.insert(ss);
      } else {
        set.insert(ss);
      }
    }

    std::vector<std::string> result;
    for (const auto& s : res) {
      result.emplace_back(s);
    }

    return result;
  }
};

int main() {
  string s = "AAAAAAAAAAA";

  Solution solution;
  auto result = solution.findRepeatedDnaSequences(s);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); i++) {
    std::cout << result[i];
    if (i != (int)result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}