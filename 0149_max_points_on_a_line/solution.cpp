#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxPoints(vector<vector<int>>& points) {
    int len = (int)points.size();

    int result = 1;
    for (int i = 0; i < len - 1; i++) {
      std::unordered_map<int, int> counter;
      for (int j = i + 1; j < len; j++) {
        int diff_x = points[i][0] - points[j][0];
        int diff_y = points[i][1] - points[j][1];

        int sign = 0;
        if (diff_x == 0) {
          diff_y = std::abs(points[i][1]);
        } else if (diff_y == 0) {
          diff_x = std::abs(points[i][0]);
        } else {
          sign = ((diff_x > 0) ^ (diff_y > 0)) ? 1 : 0;
          int gcd = std::gcd(std::abs(diff_x), std::abs(diff_y));
          diff_x = std::abs(diff_x) / gcd;
          diff_y = std::abs(diff_y) / gcd;
        }

        int key = (sign << 31) | (diff_y << 16) | (diff_x);
        counter[key]++;
      }
      for (const auto& pair : counter) {
        result = std::max(result, pair.second + 1);
      }
    }

    return result;
  }
};

int main() {
  vector<vector<int>> points = {{1, 1}, {2, 2}, {3, 3}};

  Solution solution;
  auto result = solution.maxPoints(points);

  std::cout << result << std::endl;

  return 0;
}