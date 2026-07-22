#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int compareVersion(string version1, string version2) {
    auto ver1 = splitVersion(version1);
    auto ver2 = splitVersion(version2);

    if (ver1.size() < ver2.size()) {
      ver1.insert(ver1.end(), ver2.size() - ver1.size(), 0);
    }
    if (ver1.size() > ver2.size()) {
      ver2.insert(ver2.end(), ver1.size() - ver2.size(), 0);
    }

    for (size_t i = 0; i < ver1.size(); ++i) {
      if (ver1[i] < ver2[i]) return -1;
      if (ver1[i] > ver2[i]) return 1;
    }

    return 0;
  }

  std::vector<int> splitVersion(string version) {
    size_t len = version.size();

    std::vector<int> result;

    size_t begin = 0;
    size_t pos = 0;
    while ((pos = version.find('.', begin)) != std::string::npos) {
      int v = std::stoi(version.substr(begin, pos - begin));
      result.push_back(v);
      begin = pos + 1;
    }
    if (begin < version.size()) {
      int v = std::stoi(version.substr(begin, len - begin));
      result.push_back(v);
    }

    return result;
  }
};

int main() {
  string version1 = "1.01";
  string version2 = "1.001";

  Solution solution;
  auto result = solution.compareVersion(version1, version2);

  std::cout << result << std::endl;

  return 0;
}