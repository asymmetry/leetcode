#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool validUtf8(vector<int>& data) {
    int state = 0;
    for (auto byte : data) {
      if (byte < 0 || byte > 255) return false;
      if ((byte & 0x80) == 0) {
        if (state != 0) return false;
        state = 0;
      } else if ((byte & 0xe0) == 0xc0) {
        if (state != 0) return false;
        state = 1;  // expecting 1 more byte in the sequence
      } else if ((byte & 0xf0) == 0xe0) {
        if (state != 0) return false;
        state = 2;  // expecting 2 more bytes in the sequence
      } else if ((byte & 0xf8) == 0xf0) {
        if (state != 0) return false;
        state = 3;  // expecting 3 more bytes in the sequence
      } else if ((byte & 0xc0) == 0x80) {
        if (state == 0) return false;
        state--;
      } else {
        return false;
      }
    }
    return state == 0;
  }
};

int main() {
  std::vector<int> data = {197, 130, 1};

  Solution solution;
  auto result = solution.validUtf8(data);

  std::cout << std::boolalpha << result << std::endl;

  return 0;
}