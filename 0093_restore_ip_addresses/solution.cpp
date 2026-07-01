#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> restoreIpAddresses(string s) {
    int len = (int)s.size();

    vector<string> result;

    for (int i = 1; i < len - 2; i++) {
      std::string p1 = s.substr(0, i);
      if (p1.size() > 3 || std::stoi(p1) > 255 ||
          (p1.size() > 1 && p1[0] == '0')) {
        continue;
      }

      for (int j = i + 1; j < len - 1; j++) {
        std::string p2 = s.substr(i, j - i);
        if (p2.size() > 3 || std::stoi(p2) > 255 ||
            (p2.size() > 1 && p2[0] == '0')) {
          continue;
        }

        for (int k = j + 1; k < len; k++) {
          std::string p3 = s.substr(j, k - j);
          if (p3.size() > 3 || std::stoi(p3) > 255 ||
              (p3.size() > 1 && p3[0] == '0')) {
            continue;
          }

          std::string p4 = s.substr(k, len - k);
          if (p4.size() > 3 || std::stoi(p4) > 255 ||
              (p4.size() > 1 && p4[0] == '0')) {
            continue;
          }

          result.push_back(p1 + "." + p2 + "." + p3 + "." + p4);
        }
      }
    }

    return result;
  }
};

int main() {
  string s = "25525511135";

  Solution solution;
  auto result = solution.restoreIpAddresses(s);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}