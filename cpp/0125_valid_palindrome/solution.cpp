#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isPalindrome(string s) {
    s.erase(std::remove_if(s.begin(), s.end(),
                           [](char c) {
                             if ((c >= 'a' && c <= 'z') ||
                                 (c >= 'A' && c <= 'Z') ||
                                 (c >= '0' && c <= '9'))
                               return false;
                             return true;
                           }),
            s.end());

    std::transform(s.begin(), s.end(), s.begin(),
                   [](char c) { return std::tolower(c); });

    return std::equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
  }
};

int main() {
  string s = "A man, a plan, a canal: Panama";

  Solution solution;
  auto result = solution.isPalindrome(s);

  std::cout << result << std::endl;

  return 0;
}