#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int numDecodings(string s) {
    int len = (int)s.size();

    vector<int> ways(len, 0);
    if (s[0] == '0') return 0;
    ways[0] = 1;

    for (int i = 1; i < len; i++) {
      if (s[i] == '0' && s[i - 1] > '2') return 0;

      ways[i] = s[i] == '0' ? 0 : ways[i - 1];
      if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6')) {
        ways[i] += i >= 2 ? ways[i - 2] : 1;
      }
    }

    return ways[len - 1];
  }
};

int main() {
  string s = "226";

  Solution solution;
  auto result = solution.numDecodings(s);

  std::cout << result << std::endl;

  return 0;
}