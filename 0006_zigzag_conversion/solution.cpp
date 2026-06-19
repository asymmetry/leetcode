#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string convert(string s, int numRows) {
    if (numRows == 1) {
      return s;
    }

    int len = (int)s.size();

    std::vector<int> index;
    std::vector<int> sum(numRows + 1, 0);

    int cur = 0;
    int incl = 1;
    for (int i = 0; i < len; i++) {
      index.push_back(cur);

      sum[cur + 1]++;

      cur = cur + incl;
      if (cur == numRows - 1 || cur == 0) {
        incl = incl * (-1);
      }
    }

    for (int i = 1; i < numRows + 1; i++) {
      sum[i] += sum[i - 1];
    }

    string result(s);
    for (int i = 0; i < len; i++) {
      result[sum[index[i]]] = s[i];
      sum[index[i]]++;
    }

    return result;
  }
};

int main() {
  string s = "ab";
  int numRows = 1;

  Solution solution;
  auto result = solution.convert(s, numRows);

  std::cout << result << std::endl;

  return 0;
}