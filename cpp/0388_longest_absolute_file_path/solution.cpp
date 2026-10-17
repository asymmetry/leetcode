#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthLongestPath(string input) {
    std::vector<int> stack;
    int maxLen = 0;
    int curLen = 0;
    int level = 0;
    for (int i = 0; i < (int)input.size(); i++) {
      if (input[i] == '\n') {
        int count = 0;
        while (i + 1 < (int)input.size() && input[i + 1] == '\t') {
          count++;
          i++;
        }
        level = count;
        while (!stack.empty() && (int)stack.size() > level) {
          curLen -= stack.back();
          stack.pop_back();
        }
        level = 0;
      } else {
        int start = i;
        while (i < (int)input.size() && input[i] != '\n') i++;
        int len = i - start;
        if (std::find(input.begin() + start, input.begin() + start + len,
                      '.') != input.begin() + start + len) {
          maxLen = std::max(maxLen, curLen + len + (int)stack.size());
        } else {
          stack.push_back(len);
          curLen += len;
        }
        i--;
      }
    }
    return maxLen;
  }
};

int main() {
  std::string input =
      "dir\n\tsubdir1\n\t\tfile1."
      "ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";

  Solution solution;
  auto result = solution.lengthLongestPath(input);

  std::cout << result << std::endl;

  return 0;
}