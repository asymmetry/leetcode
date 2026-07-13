#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
 public:
  int candy(vector<int>& ratings) {
    int len = (int)ratings.size();

    std::vector<int> candies(len, 1);

    for (int i = 1; i < len; i++) {
      if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
    }

    for (int i = len - 2; i >= 0; i--) {
      if (ratings[i] > ratings[i + 1])
        candies[i] = std::max(candies[i], candies[i + 1] + 1);
    }

    return std::accumulate(candies.begin(), candies.end(), 0);
  }
};

int main() {
  vector<int> ratings = {1, 0, 2};

  Solution solution;
  auto result = solution.candy(ratings);

  std::cout << result << std::endl;

  return 0;
}