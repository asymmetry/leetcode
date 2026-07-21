#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxArea(vector<int>& height) {
    int len = (int)height.size();

    int l = 0, r = len - 1;
    int max_h = 0, max_area = 0;
    while (r > l) {
      max_h = std::min(height[r], height[l]);
      max_area = std::max(max_area, max_h * (r - l));
      if (height[l] < height[r])
        l++;
      else
        r--;
    }

    return max_area;
  }
};

int main() {
  vector<int> height = {1, 1};

  Solution solution;
  auto result = solution.maxArea(height);

  std::cout << result << std::endl;

  return 0;
}