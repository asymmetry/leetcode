#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> readBinaryWatch(int turnedOn) {
    std::vector<std::string> result;

    for (int h = 0; h < 12; ++h) {
      for (int m = 0; m < 60; ++m) {
        if (__builtin_popcount(h) + __builtin_popcount(m) == turnedOn) {
          char buffer[6];
          snprintf(buffer, sizeof(buffer), "%d:%02d", h, m);
          result.push_back(buffer);
        }
      }
    }

    return result;
  }
};

int main() {
  int turnedOn = 3;

  Solution solution;
  auto result = solution.readBinaryWatch(turnedOn);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); ++i) {
    if (i > 0) std::cout << ",";
    std::cout << result[i];
  }
  std::cout << "]" << std::endl;

  return 0;
}