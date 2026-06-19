#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    int len = (int)nums.size();

    std::unordered_map<int, int> map;
    for (int i = 0; i < len; i++) {
      if (map.count(nums[i]) != 0) {
        map[nums[i]]++;
      } else {
        map[nums[i]] = 1;
      }
    }

    vector<vector<int>> result;

    for (const auto& x : map) {
      int xx = x.first;
      for (const auto& y : map) {
        int yy = y.first;
        if (xx < yy || (xx == yy && x.second >= 2)) {
          int zz = 0 - xx - yy;
          if (map.count(zz) == 0 || (zz < xx) || (zz < yy) ||
              (zz == xx && x.second < 2) || (zz == yy && y.second < 2) ||
              (zz == xx && zz == yy && x.second < 3)) {
            continue;
          }
          result.push_back(vector<int>{xx, yy, zz});
        }
      }
    }

    return result;
  }
};

int main() {
  vector<int> nums = {-1, 0, 1, 2, -1, -4};

  Solution solution;
  auto result = solution.threeSum(nums);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); ++i) {
    std::cout << "[";
    for (int j = 0; j < (int)result[i].size(); ++j) {
      if (j != (int)result[i].size() - 1) {
        std::cout << result[i][j] << ",";
      } else {
        std::cout << result[i][j];
      }
    }
    if (i != (int)result.size() - 1) {
      std::cout << "],";
    } else {
      std::cout << "]";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}