#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  string reverseVowels(string s) {
    const std::unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u',
                                             'A', 'E', 'I', 'O', 'U'};
    int l = (int)s.size();
    int left = 0;
    int right = l - 1;
    while (left < right) {
      while (left < right && vowels.find(s[left]) == vowels.end()) left++;
      if (left == right) break;
      while (left < right && vowels.find(s[right]) == vowels.end()) right--;
      if (left == right) break;
      std::swap(s[left], s[right]);
      left++;
      right--;
    }

    return s;
  }
};

int main() {
  std::string s = "IceCreAm";

  Solution solution;
  auto result = solution.reverseVowels(s);

  std::cout << result << std::endl;

  return 0;
}