#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxEnvelopes(vector<vector<int>>& envelopes) {
    std::sort(envelopes.begin(), envelopes.end(),
              [](const auto& e1, const auto& e2) {
                if (e1[0] < e2[0]) return true;
                if (e1[0] > e2[0]) return false;
                return e1[1] > e2[1];
              });

    // int len = (int)envelopes.size();

    // int max_result = 1;
    // std::vector<int> result(len, 1);
    // for (int i = 1; i < len; i++) {
    //   for (int j = 0; j < i; j++) {
    //     if (envelopes[i][1] > envelopes[j][1]) {
    //       result[i] = std::max(result[i], result[j] + 1);
    //     }
    //   }
    //   max_result = std::max(result[i], max_result);
    // }

    // return max_result;

    std::vector<int> tails;
    for (const auto& envelope : envelopes) {
      auto it = std::lower_bound(tails.begin(), tails.end(), envelope[1]);
      if (it == tails.end()) {
        tails.push_back(envelope[1]);
      } else {
        *it = envelope[1];
      }
    }

    return (int)tails.size();
  }
};

int main() {
  vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};

  Solution solution;
  auto result = solution.maxEnvelopes(envelopes);

  std::cout << result << std::endl;

  return 0;
}