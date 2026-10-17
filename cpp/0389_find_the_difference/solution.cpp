#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  char findTheDifference(string s, string t) {
    char result = '\0';
    for (auto c : s) {
      result = result ^ c;
    }
    for (auto c : t) {
      result = result ^ c;
    }
    return result;
  }
};

int main() {
  std::string s = "abcd";
  std::string t = "abcde";

  Solution solution;
  auto result = solution.findTheDifference(s, t);

  std::cout << result << std::endl;

  return 0;
}