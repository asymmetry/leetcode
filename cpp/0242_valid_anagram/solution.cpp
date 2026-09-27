#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isAnagram(string s, string t) {
    std::unordered_multiset<char> ss;
    for (char& c : s) {
      ss.insert(c);
    }

    for (char& c : t) {
      if (ss.count(c) == 0) {
        return false;
      }
      ss.erase(ss.find(c));
    }

    return ss.empty();
  }
};

int main() {
  std::string s = "anagram";
  std::string t = "nagaram";

  Solution solution;
  auto result = solution.isAnagram(s, t);

  std::cout << result << std::endl;

  return 0;
}