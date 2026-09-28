#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int hIndex(vector<int>& citations) {
    std::sort(citations.begin(), citations.end(), std::greater<int>());

    for (int i = 0; i < (int)citations.size(); i++) {
      if (citations[i] < i + 1) return i;
    }

    return (int)citations.size();
  }
};

int main() {
  std::vector<int> citations = {3, 0, 6, 1, 5};

  Solution solution;
  auto result = solution.hIndex(citations);

  std::cout << result << std::endl;

  return 0;
}