#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string multiply(string num1, string num2) {
    int len1 = (int)num1.size();
    int len2 = (int)num2.size();

    string result(len1 + len2 + 1, '0');

    int carry = 0;
    for (int i = 0; i < len1; i++) {
      int ii = len1 - i - 1;
      carry = 0;
      for (int j = 0; j < len2; j++) {
        int jj = len2 - j - 1;

        int di = num1[ii] - '0';
        int dj = num2[jj] - '0';
        int ds = result[i + j] - '0';

        int r = di * dj + carry + ds;
        carry = r / 10;
        result[i + j] = '0' + r % 10;
      }

      int k = i + len2;
      while (carry > 0) {
        int ds = result[k] - '0';
        int r = ds + carry;
        carry = r / 10;
        result[k] = '0' + r % 10;
      }
    }

    string reversed;
    for (int i = (int)result.size() - 1; i >= 0; i--) {
      if (reversed.empty() && result[i] == '0') continue;
      reversed += result[i];
    }

    if (reversed.empty()) {
      return "0";
    }
    return reversed;
  }
};

int main() {
  string num1 = "123";
  string num2 = "456";

  Solution s;
  auto result = s.multiply(num1, num2);

  std::cout << result << std::endl;

  return 0;
}