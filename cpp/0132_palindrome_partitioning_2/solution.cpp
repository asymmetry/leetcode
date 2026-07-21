#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minCut(string s) {
    int len = (int)s.size();

    std::vector<std::vector<int>> is_palindrome(len, std::vector<int>(len, 0));
    for (int i = 0; i < len; i++) {
      is_palindrome[i][i] = 1;
    }

    for (int l = 2; l <= len; l++) {
      for (int i = 0; i < len - l + 1; i++) {
        int j = i + l - 1;
        if (s[i] == s[j]) {
          if (l == 2) {
            is_palindrome[i][j] = 1;
          } else {
            is_palindrome[i][j] = is_palindrome[i + 1][j - 1];
          }
        }
      }
    }

    std::vector<int> result(len, 0);
    for (int i = 0; i < len; i++) {
      result[i] = i;
    }

    for (int i = 0; i < len; i++) {
      for (int j = 0; j <= i; j++) {
        if (is_palindrome[j][i] == 1) {
          if (j == 0)
            result[i] = 0;
          else
            result[i] = std::min(result[i], result[j - 1] + 1);
        }
      }
      printf("%d\n", result[i]);
    }

    return result[len - 1];
  }
};

int main() {
  string s = "abbab";

  Solution solution;
  auto result = solution.minCut(s);

  std::cout << result << std::endl;

  return 0;
}