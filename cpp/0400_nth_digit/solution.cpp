#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findNthDigit(int n) {
    int digit_per_num = 1;
    int begin = 1;
    int end = 9;
    long long n_limit = 9;
    long long n_begin = 1;
    while (true) {
      if (n <= n_limit) {
        long long num = (n - n_begin) / digit_per_num + begin;
        int digit_index = (n - n_begin) % digit_per_num;
        for (int i = 0; i < digit_per_num - digit_index - 1; i++) {
          num /= 10;
        }
        num %= 10;
        return (int)num;
      } else {
        begin = begin * 10;
        end = end * 10 + 9;
        digit_per_num += 1;
        long long count = end - begin + 1;
        n_begin = n_limit + 1;
        n_limit += count * digit_per_num;
      }
    }
  }
};

int main() {
  int n = 189;

  Solution solution;
  auto result = solution.findNthDigit(n);

  std::cout << result << std::endl;

  return 0;
}