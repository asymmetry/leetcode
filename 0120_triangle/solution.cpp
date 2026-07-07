#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    int n = (int)triangle.size();

    vector<int> sums(n, 0);
    sums[0] = triangle[0][0];

    for (int i = 1; i < n; i++) {
      for (int j = i; j >= 0; j--) {
        if (j == 0) {
          sums[j] = triangle[i][j] + sums[j];
        } else if (j == i) {
          sums[j] = triangle[i][j] + sums[j - 1];
        } else {
          sums[j] = triangle[i][j] + std::min(sums[j], sums[j - 1]);
        }
      }
    }

    int result = sums[0];
    for (auto r : sums) {
      result = std::min(result, r);
    }

    return result;
  }
};

int main() {
  vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};

  Solution solution;
  auto result = solution.minimumTotal(triangle);

  std::cout << result << std::endl;

  return 0;
}