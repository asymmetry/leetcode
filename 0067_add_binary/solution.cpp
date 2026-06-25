#include <iostream>

using namespace std;

class Solution {
 public:
  string addBinary(string a, string b) {
    int len_a = (int)a.size();
    int len_b = (int)b.size();

    int len = std::max(len_a, len_b);

    string result;
    int carry = 0;
    for (int i = 0; i < len; i++) {
      int ia = len_a - i - 1;
      int ib = len_b - i - 1;

      if (ia >= 0 && ib >= 0) {
        int r = a[ia] + b[ib] + carry - '0' * 2;
        carry = r / 2;
        result.push_back('0' + r % 2);
      } else if (ia >= 0) {
        int r = a[ia] + carry - '0';
        carry = r / 2;
        result.push_back('0' + r % 2);
      } else if (ib >= 0) {
        int r = b[ib] + carry - '0';
        carry = r / 2;
        result.push_back('0' + r % 2);
      }
    }
    if (carry > 0) {
      result.push_back('1');
    }

    for (int i = 0; i < (int)result.size() / 2; i++) {
      std::swap(result[i], result[(int)result.size() - i - 1]);
    }

    return result;
  }
};

int main() {
  string a = "0";
  string b = "1011";

  Solution solution;
  auto result = solution.addBinary(a, b);

  std::cout << result << std::endl;

  return 0;
}