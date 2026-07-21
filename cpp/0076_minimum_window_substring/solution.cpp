#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

bool is_good(const std::unordered_map<char, int>& map,
             const std::unordered_map<char, int>& test) {
  for (const auto& [key, value] : map) {
    if (test.find(key) == test.end() || test.at(key) < value) {
      return false;
    }
  }
  return true;
}

class Solution {
 public:
  string minWindow(string s, string t) {
    std::unordered_map<char, int> map;
    std::unordered_map<char, int> test;
    for (const auto& c : t) {
      map[c]++;
      test[c] = 0;
    }

    int l_min = 0, r_min = (int)s.size();
    bool found = false;

    int len = (int)s.size();
    int l = 0, r = 0;
    while (r < len) {
      if (map.find(s[r]) != map.end()) {
        test[s[r]]++;
      }
      if (is_good(map, test)) {
        while (l <= r && map.find(s[l]) == map.end()) {
          l++;
        }
        if (r - l + 1 < r_min - l_min + 1) {
          l_min = l;
          r_min = r;
          found = true;
        }
        test[s[l]]--;
        l++;
        test[s[r]]--;
        r--;
      }
      r++;
    }

    if (!found) {
      return "";
    }
    return s.substr(l_min, r_min - l_min + 1);
  }
};

int main() {
  std::string s = "ADOBECODEBANC";
  std::string t = "ABC";

  Solution solution;
  std::string result = solution.minWindow(s, t);

  std::cout << result << std::endl;

  return 0;
}