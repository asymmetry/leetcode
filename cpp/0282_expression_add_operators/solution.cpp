#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> addOperators(string num, int target) {
    std::vector<std::string> ans;
    std::string path;
    // Using long long to prevent integer overflow during intermediate
    // calculations
    dfs(0, 0, 0, num, target, path, ans);
    return ans;
  }

 private:
  void dfs(int start, long long prev, long long eval, const std::string& num,
           int target, std::string& path, std::vector<std::string>& ans) {
    // Base case: if we have processed all digits, check if evaluation matches
    // target
    if (start == num.length()) {
      if (eval == target) {
        ans.push_back(path);
      }
      return;
    }

    long long curr = 0;
    std::string curr_str = "";
    int len = path.length();

    for (int i = start; i < num.length(); ++i) {
      // Rule: skip sub-strings with leading zeros (e.g., "05")
      if (i > start && num[start] == '0') {
        break;
      }

      curr_str += num[i];
      curr = curr * 10 + (num[i] - '0');

      if (start == 0) {
        // First operand has no operator preceding it
        path += curr_str;
        dfs(i + 1, curr, curr, num, target, path, ans);
        path.resize(len);  // Backtrack
      } else {
        // Case 1: Addition '+'
        path += "+" + curr_str;
        dfs(i + 1, curr, eval + curr, num, target, path, ans);
        path.resize(len);  // Backtrack

        // Case 2: Subtraction '-'
        path += "-" + curr_str;
        dfs(i + 1, -curr, eval - curr, num, target, path, ans);
        path.resize(len);  // Backtrack

        // Case 3: Multiplication '*'
        path += "*" + curr_str;
        dfs(i + 1, prev * curr, eval - prev + (prev * curr), num, target, path,
            ans);
        path.resize(len);  // Backtrack
      }
    }
  }
};

int main() {
  std::string num = "123";
  int target = 6;

  Solution solution;
  auto result = solution.addOperators(num, target);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i + 1 < result.size()) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}