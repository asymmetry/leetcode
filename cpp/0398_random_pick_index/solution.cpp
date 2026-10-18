#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  Solution(vector<int>& nums) : indices(), gen(std::random_device()()) {
    for (int i = 0; i < (int)nums.size(); i++) {
      indices[nums[i]].push_back(i);
    }
  }

  int pick(int target) {
    int len = (int)indices[target].size();
    auto dist = std::uniform_int_distribution(0, len - 1);
    return indices[target][dist(gen)];
  }

 private:
  std::unordered_map<int, std::vector<int>> indices;
  std::mt19937 gen;
};

int main() {
  std::vector<int> nums = {1, 2, 3, 3, 3};

  Solution* solution = new Solution(nums);
  std::cout << solution->pick(3) << std::endl;
  std::cout << solution->pick(1) << std::endl;
  std::cout << solution->pick(3) << std::endl;

  return 0;
}