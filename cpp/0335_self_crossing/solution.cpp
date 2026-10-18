#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isSelfCrossing(vector<int>& distance) {
    int n = (int)distance.size();
    if (n < 4) return false;
    for (int i = 3; i < n; i++) {
      if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3])
        return true;
      if (i >= 4 && distance[i - 1] == distance[i - 3] &&
          distance[i] + distance[i - 4] >= distance[i - 2])
        return true;
      if (i >= 5 && distance[i - 2] >= distance[i - 4] &&
          distance[i] + distance[i - 4] >= distance[i - 2] &&
          distance[i - 1] <= distance[i - 3] &&
          distance[i - 1] + distance[i - 5] >= distance[i - 3])
        return true;
    }
    return false;
  }
};

int main() {
  std::vector<int> distance = {2, 1, 1, 2};

  Solution solution;
  auto result = solution.isSelfCrossing(distance);

  std::cout << result << std::endl;

  return 0;
}