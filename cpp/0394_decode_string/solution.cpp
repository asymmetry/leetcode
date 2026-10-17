#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  string decodeString(string s) {
    int len = (int)s.size();
    std::string result;
    int repeat = 0;
    for (int i = 0; i < len; i++) {
      if (s[i] >= 'a' && s[i] <= 'z') {
        result.push_back(s[i]);
      } else if (s[i] == '[') {
        int start = i + 1;
        int count = 1;
        i++;
        while (true) {
          if (s[i] == '[') count++;
          if (s[i] == ']') count--;
          if (count == 0) break;
          i++;
        }
        int end = i;
        auto inner = decodeString(s.substr(start, end - start));
        for (int i = 0; i < repeat; i++) {
          result.append(inner);
        }
      } else if (s[i] >= '0' && s[i] <= '9') {
        int start = i;
        while (s[i] >= '0' && s[i] <= '9') i++;
        int end = i;
        repeat = std::stoi(s.substr(start, end - start));
        i--;
      }
    }
    return result;
  }
};

int main() {
  std::string s = "2[abc]3[cd]ef";

  Solution solution;
  auto result = solution.decodeString(s);

  std::cout << result << std::endl;

  return 0;
}