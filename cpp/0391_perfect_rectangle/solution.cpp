#include <iostream>
#include <limits>
#include <set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isRectangleCover(vector<vector<int>>& rectangles) {
    int x_min = std::numeric_limits<int>::max();
    int y_min = std::numeric_limits<int>::max();
    int x_max = std::numeric_limits<int>::min();
    int y_max = std::numeric_limits<int>::min();

    std::set<std::pair<int, int>> points;
    long long total_area = 0;

    for (const auto& rect : rectangles) {
      int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
      x_min = std::min(x_min, x1);
      y_min = std::min(y_min, y1);
      x_max = std::max(x_max, x2);
      y_max = std::max(y_max, y2);

      total_area += static_cast<long long>(x2 - x1) * (y2 - y1);

      if (!points.insert({x1, y1}).second) points.erase({x1, y1});
      if (!points.insert({x1, y2}).second) points.erase({x1, y2});
      if (!points.insert({x2, y1}).second) points.erase({x2, y1});
      if (!points.insert({x2, y2}).second) points.erase({x2, y2});
    }

    if (points.size() != 4) return false;
    if (!points.count({x_min, y_min})) return false;
    if (!points.count({x_min, y_max})) return false;
    if (!points.count({x_max, y_min})) return false;
    if (!points.count({x_max, y_max})) return false;

    long long area = static_cast<long long>(x_max - x_min) * (y_max - y_min);
    return area == total_area;
  }
};

int main() {
  std::vector<std::vector<int>> rectangles = {
      {1, 1, 3, 3}, {3, 1, 4, 2}, {3, 2, 4, 4}, {1, 3, 2, 4}, {2, 3, 3, 4}};

  Solution solution;
  auto result = solution.isRectangleCover(rectangles);

  std::cout << std::boolalpha << result << std::endl;

  return 0;
}