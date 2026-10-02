#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};
    if (n == 2) return {0, 1};

    std::vector<std::vector<int>> map(n, std::vector<int>());
    for (const auto& edge : edges) {
      map[edge[0]].push_back(edge[1]);
      map[edge[1]].push_back(edge[0]);
    }

    std::vector<int> degree(n, 0);
    for (int i = 0; i < n; i++) {
      degree[i] = (int)map[i].size();
    }

    while (true) {
      int count_nodes = 0;
      std::vector<int> leaves;
      for (int i = 0; i < n; i++) {
        if (degree[i] > 0) count_nodes++;
        if (degree[i] == 1) {
          leaves.push_back(i);
        }
      }
      if (count_nodes == (int)leaves.size()) return leaves;
      if (count_nodes == (int)leaves.size() + 1) {
        for (int i = 0; i < n; i++) {
          if (degree[i] > 1) return {i};
        }
      }
      for (const auto& l : leaves) {
        degree[l]--;
        for (const auto& n : map[l]) {
          degree[n]--;
        }
      }
    }
  }
};

int main() {
  int n = 4;
  std::vector<std::vector<int>> edges = {
      {1, 0},
      {1, 2},
      {1, 3},
  };

  auto solution = new Solution();
  auto result = solution->findMinHeightTrees(n, edges);

  std::cout << "[";
  for (const auto& r : result) {
    std::cout << r;
    if (&r != &result.back()) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}