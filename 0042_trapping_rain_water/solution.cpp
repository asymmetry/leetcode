#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int trap(vector<int>& height) {
    int len = (int)height.size();

    int area = 0;
    int h = 0;
    for (int i = 0; i < len; i++) {
      h = std::max(height[i], h);
      if (h > height[i]) area += (h - height[i]);
    }
    for (int i = 0; i < len; i++) {
      area -= (h - height[i]);
    }

    h = 0;
    for (int i = len - 1; i >= 0; i--) {
      h = std::max(height[i], h);
      if (h > height[i]) area += (h - height[i]);
    }

    return area;
  }
};

int main() {
  vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

  Solution solution;
  auto result = solution.trap(height);

  std::cout << result << std::endl;

  return 0;
}