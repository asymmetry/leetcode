#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2,
                  int by2) {
    int area_1 = (ax2 - ax1) * (ay2 - ay1);
    int area_2 = (bx2 - bx1) * (by2 - by1);
    int area_3 = (std::min(ax2, bx2) - std::max(ax1, bx1)) *
                 (std::min(ay2, by2) - std::max(ay1, by1));
    if (std::min(ax2, bx2) - std::max(ax1, bx1) < 0 ||
        std::min(ay2, by2) - std::max(ay1, by1) < 0)
      area_3 = 0;
    return area_1 + area_2 - area_3;
  }
};

int main() {
  vector<int> rect1 = {-3, 0, 3, 4};
  vector<int> rect2 = {0, -1, 9, 2};

  Solution solution;
  auto result = solution.computeArea(rect1[0], rect1[1], rect1[2], rect1[3],
                                     rect2[0], rect2[1], rect2[2], rect2[3]);

  std::cout << result << std::endl;

  return 0;
}