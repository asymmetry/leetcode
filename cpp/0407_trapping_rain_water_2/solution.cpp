#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
 private:
  struct Cell {
    int r, c, h;
    // Min-heap ordering: lowest height elements are prioritized
    bool operator>(const Cell& other) const { return h > other.h; }
  };

 public:
  int trapRainWater(vector<vector<int>>& heightMap) {
    if (heightMap.empty() || heightMap[0].empty()) return 0;

    int m = heightMap.size();
    int n = heightMap[0].size();

    // Min-priority queue to keep track of the lowest boundary cell
    std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> minHeap;
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

    // 1. Push all border cells into the min-heap and mark them visited
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (r == 0 || r == m - 1 || c == 0 || c == n - 1) {
          minHeap.push({r, c, heightMap[r][c]});
          visited[r][c] = true;
        }
      }
    }

    int totalWater = 0;
    // Direction vectors for 4-way connectivity
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    // 2. Process cells starting from the lowest boundary inwards
    while (!minHeap.empty()) {
      Cell curr = minHeap.top();
      minHeap.pop();

      for (int i = 0; i < 4; ++i) {
        int nr = curr.r + dr[i];
        int nc = curr.c + dc[i];

        // Check bounds and skip if already visited
        if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
          visited[nr][nc] = true;

          // If the neighbor is shorter than the current spill boundary, it
          // traps water
          if (heightMap[nr][nc] < curr.h) {
            totalWater += curr.h - heightMap[nr][nc];
          }

          // Push neighbor with the effective boundary height constraint
          minHeap.push({nr, nc, std::max(heightMap[nr][nc], curr.h)});
        }
      }
    }

    return totalWater;
  }
};

int main() {
  std::vector<std::vector<int>> heightMap = {
      {1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}};

  Solution solution;
  auto result = solution.trapRainWater(heightMap);

  std::cout << result << std::endl;

  return 0;
}