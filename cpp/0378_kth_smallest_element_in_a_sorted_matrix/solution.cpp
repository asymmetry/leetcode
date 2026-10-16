#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
 public:
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    auto compare = [](const std::pair<int, int>& a,
                      const std::pair<int, int>& b) {
      return a.first > b.first;
    };

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        decltype(compare)>
        queue(compare);

    int n = (int)matrix.size();
    for (int i = 0; i < n; i++) {
      queue.push(std::pair<int, int>(matrix[i][0], i));
    }

    std::vector<int> indices(n, 0);

    int result = 0;
    for (int i = 0; i < k; i++) {
      auto& top = queue.top();
      int index = top.second;
      result = top.first;
      queue.pop();
      if (indices[index] + 1 < n) {
        indices[index]++;
        queue.push(std::pair<int, int>(matrix[index][indices[index]], index));
      }
    }

    return result;
  }
};

int main() {
  std::vector<std::vector<int>> matrix = {
      {1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
  int k = 8;

  Solution solution;
  auto result = solution.kthSmallest(matrix, k);

  std::cout << result << std::endl;

  return 0;
}