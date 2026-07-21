#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int len = (int)gas.size();

    for (int i = 0; i < len; i++) {
      int tank = 0;
      for (int j = i; j < i + len; j++) {
        int cur = j % len;
        tank += gas[cur];
        tank -= cost[cur];
        if (tank < 0) {
          break;
        }
      }
      if (tank >= 0) {
        return i;
      }
    }

    return -1;

    // int len = (int)gas.size();

    // int start_point = 0;
    // int tank = 0;
    // int total_tank = 0;
    // for (int i = 0; i < len; i++) {
    //   tank += gas[i] - cost[i];
    //   total_tank += gas[i] - cost[i];
    //   if (tank < 0) {
    //     start_point = i + 1;
    //     tank = 0;
    //   }
    // }

    // if (total_tank < 0) return -1;

    // return start_point;
  }
};

int main() {
  vector<int> gas = {1, 2, 3, 4, 5};
  vector<int> cost = {3, 4, 5, 1, 2};

  Solution solution;
  auto result = solution.canCompleteCircuit(gas, cost);

  std::cout << result << std::endl;

  return 0;
}