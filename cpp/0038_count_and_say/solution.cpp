#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string countAndSay(int n) {
    string result = "1";

    for (int i = 2; i <= n; i++) {
      int len = (int)result.size();

      int count = 1;
      int index = 0;
      string new_result = "";
      for (int j = 1; j < len; j++) {
        if (result[index] != result[j]) {
          new_result += std::to_string(count) + result[index];
          index = j;
          count = 1;
        } else {
          count++;
        }
      }
      result = new_result + std::to_string(count) + result[index];
    }

    return result;
  }
};

int main() {
  int n = 7;

  Solution solution;
  auto result = solution.countAndSay(n);

  std::cout << result << std::endl;

  return 0;
}