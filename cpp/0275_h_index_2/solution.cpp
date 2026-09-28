#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int hIndex(vector<int>& citations) {
    int n = (int)citations.size();
    int l = 0;
    int r = n - 1;

    while (l < r) {
      int m = (l + r) / 2;

      if (citations[m] >= (n - m)) {
        r = m;
      } else {
        l = m + 1;
      }
    }

    if (citations[l] >= n - l) {
      return n - l;
    } else {
      return 0;
    }
  }
};

int main() {
  std::vector<int> citations = {0, 1};

  Solution solution;
  auto result = solution.hIndex(citations);

  std::cout << result << std::endl;

  return 0;
}