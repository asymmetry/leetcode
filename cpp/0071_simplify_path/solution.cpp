#include <deque>
#include <iostream>

using namespace std;

class Solution {
 public:
  string simplifyPath(string path) {
    std::deque<string> parts;

    path.push_back('/');

    size_t pos = 0;
    size_t prev = 1;
    while ((pos = path.find('/', prev)) != std::string::npos) {
      if (pos > prev) {
        auto part = path.substr(prev, pos - prev);
        if (part == "..") {
          if (!parts.empty()) {
            parts.pop_back();
          }
        } else if (part != ".") {
          parts.push_back(part);
        }
      }
      prev = pos + 1;
    }

    string result = "";
    for (const auto& part : parts) {
      result.push_back('/');
      result.append(part);
    }

    if (result.empty()) {
      result.push_back('/');
    }
    return result;
  }
};

int main() {
  string path = "/home";

  Solution solution;
  auto result = solution.simplifyPath(path);

  std::cout << result << std::endl;

  return 0;
}