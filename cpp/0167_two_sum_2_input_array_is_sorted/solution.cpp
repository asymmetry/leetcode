#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    int len = (int)numbers.size();

    int i = 0;
    int j = len - 1;
    while (i < j) {
      int sum = numbers[i] + numbers[j];
      if (sum == target) {
        return {i + 1, j + 1};
      } else if (sum < target) {
        i++;
      } else {
        j--;
      }
    }

    return {-1, -1};
  }
};

int main() {
  vector<int> numbers = {2, 7, 11, 15};
  int target = 9;

  Solution solution;
  auto result = solution.twoSum(numbers, target);

  std::cout << "[" << result[0] << ", " << result[1] << "]" << std::endl;

  return 0;
}