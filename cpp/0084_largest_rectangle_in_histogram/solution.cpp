#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();

    stack<int> s;
    int max_area = 0;
    int i = 0;
    while (i < n) {
      if (s.empty() || heights[i] >= heights[s.top()]) {
        s.push(i++);
      } else {
        int top = s.top();
        s.pop();
        int width = s.empty() ? i : i - s.top() - 1;
        max_area = max(max_area, heights[top] * width);
      }
    }
    while (!s.empty()) {
      int top = s.top();
      s.pop();
      int width = s.empty() ? i : i - s.top() - 1;
      max_area = max(max_area, heights[top] * width);
    }

    return max_area;
  }
};

int main() {
  vector<int> heights = {2, 1, 2};

  Solution solution;
  auto result = solution.largestRectangleArea(heights);

  std::cout << result << std::endl;

  return 0;
}