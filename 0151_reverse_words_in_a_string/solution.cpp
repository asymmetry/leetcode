#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string reverseWords(string s) {
    int i = 0;
    int j = 0;
    int len = (int)s.size();

    while (i < len) {
      while (i < len && s[i] == ' ') i++;

      if (i == len) break;

      if (j != 0) {
        s[j++] = ' ';
      }

      int k = i;
      while (k < len && s[k] != ' ') {
        s[j++] = s[k++];
      }

      std::reverse(s.begin() + j - (k - i), s.begin() + j);

      i = k;
    }

    s.erase(j, len - j);
    std::reverse(s.begin(), s.end());

    return s;
  }
};

int main() {
  string s = "a good   example";

  Solution solution;
  auto result = solution.reverseWords(s);

  std::cout << result << std::endl;

  return 0;
}