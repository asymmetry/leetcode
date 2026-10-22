#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canCross(vector<int>& stones) {
    int n = (int)stones.size();

    std::unordered_map<int, std::unordered_set<int>> jumps;
    for (const auto stone : stones) {
      jumps[stone].clear();
    }
    jumps[1].insert(1);

    for (int i = 1; i < n - 1; i++) {
      for (const auto jump : jumps[stones[i]]) {
        for (int j = -1; j <= 1; j++) {
          if (jump + j >= 1 &&
              jumps.find(stones[i] + jump + j) != jumps.end()) {
            jumps[stones[i] + jump + j].insert(jump + j);
          }
        }
      }
    }

    return !jumps[stones[n - 1]].empty();
  }
};

int main() {
  std::vector<int> stones = {0, 1, 3, 5, 6, 8, 12, 17};

  Solution solution;
  auto result = solution.canCross(stones);

  std::cout << result << std::endl;

  return 0;
}