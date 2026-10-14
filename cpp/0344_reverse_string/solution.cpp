#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void reverseString(vector<char>& s) {
    int l = (int)s.size();
    if (l == 1) return;

    int left = 0;
    int right = l - 1;
    while (left < right) {
      std::swap(s[left], s[right]);
      left++;
      right--;
    }
  }
};

int main() {
  std::vector<char> s = {'h', 'e', 'l', 'l', 'o'};

  Solution solution;
  solution.reverseString(s);

  std::cout << "[";
  for (size_t i = 0; i < s.size(); i++) {
    std::cout << s[i];
    if (i < s.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}