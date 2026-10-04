#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProduct(vector<string>& words) {
    std::vector<std::pair<int, int>> table;
    for (const auto& word : words) {
      int l = (int)word.size();
      int used = 0;
      for (const auto& ch : word) {
        int chi = ch - 'a';
        used |= 1 << chi;
      }
      table.emplace_back(l, used);
    }

    int result = 0;
    int len = (int)words.size();
    for (int i = 0; i < len - 1; i++) {
      for (int j = i + 1; j < len; j++) {
        if ((table[i].second & table[j].second) != 0) continue;
        result = std::max(result, table[i].first * table[j].first);
      }
    }

    return result;
  }
};

int main() {
  std::vector<std::string> words = {"abcw", "baz",  "foo",
                                    "bar",  "xtfn", "abcdef"};

  auto solution = new Solution();
  auto result = solution->maxProduct(words);

  std::cout << result << std::endl;

  return 0;
}