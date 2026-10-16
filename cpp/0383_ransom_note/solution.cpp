#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canConstruct(string ransomNote, string magazine) {
    std::vector<int> r(26, 0);
    std::vector<int> m(26, 0);

    for (const auto& c : ransomNote) {
      int i = c - 'a';
      r[i]++;
    }
    for (const auto& c : magazine) {
      int i = c - 'a';
      m[i]++;
    }

    for (int i = 0; i < 26; i++) {
      if (r[i] > m[i]) return false;
    }

    return true;
  }
};

int main() {
  std::string ransomNote = "a";
  std::string magazine = "b";

  Solution solution;
  auto result = solution.canConstruct(ransomNote, magazine);

  std::cout << result << std::endl;

  return 0;
}