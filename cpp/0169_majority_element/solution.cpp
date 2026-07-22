#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    int len = (int)nums.size();

    int candidate = nums[0];
    int count = 1;
    for (int i = 1; i < len; i++) {
      if (nums[i] == candidate)
        count++;
      else {
        count--;
        if (count == 0) {
          candidate = nums[i];
          count++;
        }
      }
    }

    return candidate;
  }
};

int main() {
  vector<int> numbers = {3, 2, 3};

  Solution solution;
  auto result = solution.majorityElement(numbers);

  std::cout << result << std::endl;

  return 0;
}