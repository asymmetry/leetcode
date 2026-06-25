#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> plusOne(vector<int>& digits) {
    int len = (int)digits.size();

    vector<int> result;
    digits[len - 1]++;

    int carry = 0;
    for (int i = len - 1; i >= 0; i--) {
      digits[i] += carry;
      carry = digits[i] / 10;
      result.insert(result.begin(), digits[i] % 10);
    }
    if (carry > 0) result.insert(result.begin(), carry);

    return result;
  }
};

int main() {
  vector<int> digits = {9, 9, 9};

  Solution solution;
  auto result = solution.plusOne(digits);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); ++i) {
    std::cout << result[i];
    if (i != (int)result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}