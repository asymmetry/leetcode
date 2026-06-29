#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> grayCode(int n) {
    int len = 1;
    for (int i = 0; i < n; i++) {
      len = len * 2;
    }
    vector<int> result{0};
    vector<bool> used(len, false);
    used[0] = true;

    for (int i = 1; i < len; i++) {
      int cur = result[i - 1];
      for (int j = 0; j < n; j++) {
        int next = cur ^ (1 << j);
        if (!used[next]) {
          result.push_back(next);
          used[next] = true;
          break;
        }
      }
    }

    return result;
  }
};

int main() {
  int n = 4;

  Solution s;
  auto result = s.grayCode(n);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); i++) {
    std::cout << result[i];
    if (i != (int)result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}