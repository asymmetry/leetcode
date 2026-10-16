#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  Solution(vector<int>& nums) : nums(nums), gen_(std::random_device()()) {}

  vector<int> reset() { return nums; }

  vector<int> shuffle() {
    std::vector<int> result(nums.begin(), nums.end());
    int len = (int)nums.size();
    for (int i = len - 1; i > 0; i--) {
      std::uniform_int_distribution<int> dist(0, i);
      int j = dist(gen_);
      std::swap(result[i], result[j]);
    }
    return result;
  }

 private:
  std::vector<int> nums;
  std::mt19937 gen_;
};

void printVector(const vector<int>& v) {
  std::cout << "[";
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i];
    if (i < v.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;
}

int main() {
  vector<int> nums = {1, 2, 3};

  auto solution = new Solution(nums);
  printVector(solution->shuffle());
  printVector(solution->reset());
  printVector(solution->shuffle());

  return 0;
}