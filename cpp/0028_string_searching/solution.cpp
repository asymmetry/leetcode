#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int strStr(string haystack, string needle) {
    if (needle.size() > haystack.size()) return -1;

    int test_len = (int)haystack.size() - (int)needle.size();
    for (int i = 0; i <= test_len; i++) {
      if (haystack.substr(i, (int)needle.size()) == needle) {
        return i;
      }
    }

    return -1;
  }
};

int main() {
  string haystack = "leetcode";
  string needle = "leeto";

  Solution s;
  auto result = s.strStr(haystack, needle);

  std::cout << result << std::endl;

  return 0;
}