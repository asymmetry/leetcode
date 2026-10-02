#include <iostream>
#include <vector>

using namespace std;

class NumArray {
 public:
  NumArray(vector<int>& nums) {
    int sum = 0;
    for (const auto& n : nums) {
      sum += n;
      sums.push_back(sum);
    }
  }

  void update(int index, int val) {
    int ori = 0;
    if (index == 0) {
      ori = sums[0];
    } else {
      ori = sums[index] - sums[index - 1];
    }

    int diff = val - ori;
    for (int i = index; i < (int)sums.size(); i++) {
      sums[i] += diff;
    }
  }

  int sumRange(int left, int right) {
    if (left == 0) {
      return sums[right];
    } else {
      return sums[right] - sums[left - 1];
    }
  }

 private:
  std::vector<int> sums = {};
};

int main() {
  std::vector<int> nums{1, 3, 5};
  auto num_array = new NumArray(nums);
  std::cout << num_array->sumRange(0, 2) << std::endl;
  num_array->update(1, 2);
  std::cout << num_array->sumRange(0, 2) << std::endl;

  return 0;
}