#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isSubsequence(string s, string t) {
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()) {
      if (s[i] == t[j]) {
        i++;
      }
      j++;
    }
    return i == s.size();
  }
};

int main() {
  std::string s = "abc";
  std::string t = "ahbgdc";

  Solution solution;
  auto result = solution.isSubsequence(s, t);

  std::cout << result << std::endl;

  return 0;
}