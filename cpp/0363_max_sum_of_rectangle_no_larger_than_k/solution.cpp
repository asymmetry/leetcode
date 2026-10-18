#include <iostream>
#include <limits>
#include <set>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    if (matrix.empty() || matrix[0].empty()) return 0;

    int rows = matrix.size();
    int cols = matrix[0].size();

    int max_sum = std::numeric_limits<int>::min();
    for (int left = 0; left < cols; ++left) {
      std::vector<int> row_sums(rows, 0);
      for (int right = left; right < cols; ++right) {
        for (int i = 0; i < rows; ++i) {
          row_sums[i] += matrix[i][right];
        }

        std::set<int> cum_sums;
        cum_sums.insert(0);
        int cum_sum = 0;
        for (int sum : row_sums) {
          cum_sum += sum;
          auto it = cum_sums.lower_bound(cum_sum - k);
          if (it != cum_sums.end()) {
            max_sum = std::max(max_sum, cum_sum - *it);
          }
          cum_sums.insert(cum_sum);
        }
      }
    }

    return max_sum;
  }
};

int main() {
  std::vector<std::vector<int>> matrix = {{1, 0, 1}, {0, -2, 3}};
  int k = 2;

  Solution solution;
  auto result = solution.maxSumSubmatrix(matrix, k);

  std::cout << result << std::endl;

  return 0;
}