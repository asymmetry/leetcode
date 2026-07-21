#include <iostream>

using namespace std;

class Solution {
 public:
  int lengthOfLastWord(string s) {
    int len = (int)s.size();

    int i = len - 1;
    while (i >= 0 && s[i] == ' ') i--;
    int end = i;

    while (i >= 0 && s[i] != ' ') i--;
    int begin = i;

    return end - begin;
  }
};

int main() {
  string s = "Hello World";

  Solution solution;
  auto result = solution.lengthOfLastWord(s);

  std::cout << result << std::endl;

  return 0;
}