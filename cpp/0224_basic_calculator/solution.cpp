#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int calculate(string s) {
    int ans = 0;
    long long number = 0;
    int sign = 1;
    std::vector<int> st;

    for (char c : s) {
      if (std::isdigit(c)) {
        number = number * 10 + (c - '0');
      } else if (c == '+') {
        ans += sign * number;
        number = 0;
        sign = 1;
      } else if (c == '-') {
        ans += sign * number;
        number = 0;
        sign = -1;
      } else if (c == '(') {
        // Push the current result and then the sign
        st.push_back(ans);
        st.push_back(sign);
        // Reset for the inner parenthetical expression
        ans = 0;
        sign = 1;
      } else if (c == ')') {
        ans += sign * number;
        number = 0;

        ans *= st.back();
        st.pop_back();  // Pop and multiply by the stored sign
        ans += st.back();
        st.pop_back();  // Pop and add the accumulated outer result
      }
    }

    // Add the final trailing number if any exists
    ans += sign * number;
    return ans;
  }
};

int main() {
  std::string s = "1 + 1";

  Solution solution;
  auto result = solution.calculate(s);

  std::cout << result << std::endl;

  return 0;
}