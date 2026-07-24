#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

class Solution {
 public:
  string largestNumber(vector<int>& nums) {
    std::vector<std::string> strs;
    for (const int n : nums) {
      strs.push_back(std::to_string(n));
    }

    std::sort(strs.begin(), strs.end(),
              [](std::string_view a, std::string_view b) {
                int la = (int)a.size();
                int lb = (int)b.size();
                int li = std::min(la, lb);
                for (int i = 0; i < li; i++) {
                  if (a[i] > b[i]) return true;
                  if (a[i] < b[i]) return false;
                }

                std::string aa(a);
                aa.append(b);
                std::string bb(b);
                bb.append(a);
                if (aa > bb) return true;

                return false;
              });

    std::string result;
    for (const std::string& s : strs) {
      result.append(s);
    }

    return result[0] == '0' ? "0" : result;
  }
};

int main() {
  vector<int> nums = {3, 30, 34, 5, 9};

  Solution solution;
  auto result = solution.largestNumber(nums);

  std::cout << result << std::endl;

  return 0;
}