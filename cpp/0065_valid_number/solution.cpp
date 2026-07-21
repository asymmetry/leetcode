#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isNumber(string s) {
    std::unordered_set<char> digits = {'0', '1', '2', '3', '4',
                                       '5', '6', '7', '8', '9'};
    std::unordered_set<char> signs = {'+', '-'};

    std::vector<std::unordered_map<char, int>> states = {
        {{'s', 1}, {'d', 2}, {'.', 3}},  // 0. start with 'blank'
        {{'d', 2}, {'.', 3}},            // 1. 'sign'
        {{'d', 2}, {'.', 4}, {'e', 6}},  // 2. 'digit' before 'dot'
        {{'d', 5}},                      // 3. 'dot' (no digit before it)
        {{'d', 5}, {'e', 6}},  // 4. 'dot' (at least one digit before it)
        {{'d', 5}, {'e', 6}},  // 5. 'digit' (after 'dot', before 'e')
        {{'s', 7}, {'d', 8}},  // 6. 'e'
        {{'d', 8}},            // 7. 'sign'
        {{'d', 8}},            // 8. 'digit' (after 'e')
    };

    int state = 0;

    while (!s.empty() && s.front() == ' ') {
      s.erase(s.begin());
    }
    while (!s.empty() && s.back() == ' ') {
      s.pop_back();
    }

    for (char c : s) {
      if (digits.count(c) != 0) {
        c = 'd';
      } else if (signs.count(c) != 0) {
        c = 's';
      } else if (c == 'e' || c == 'E') {
        c = 'e';
      } else if (c == '.') {
        c = '.';
      } else {
        return false;
      }

      if (states[state].count(c) == 0) {
        return false;
      }

      state = states[state][c];
    }

    if (state == 2 || state == 4 || state == 5 || state == 8) {
      return true;
    }
    return false;
  }
};

int main() {
  string s = "123.45e+6";

  Solution solution;
  auto result = solution.isNumber(s);

  std::cout << result << std::endl;

  return 0;
}