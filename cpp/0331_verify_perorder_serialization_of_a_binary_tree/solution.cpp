#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isValidSerialization(string preorder) {
    std::stringstream preorder_stream(preorder);
    std::string node;
    std::vector<std::string> nodes;

    while (std::getline(preorder_stream, node, ',')) {
      nodes.push_back(node);
    }

    std::vector<std::string> stack;
    for (const auto& n : nodes) {
      stack.push_back(n);
      int l = (int)stack.size();
      while (l >= 3 && stack[l - 1] == "#" && stack[l - 2] == "#" &&
             stack[l - 3] != "#") {
        stack.pop_back();
        stack.pop_back();
        stack.pop_back();
        stack.push_back("#");
        l = l - 2;
      }
    }

    return stack.size() == 1 && stack[0] == "#";
  }
};

int main() {
  string preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#";

  Solution solution;
  auto result = solution.isValidSerialization(preorder);

  std::cout << std::boolalpha << result << std::endl;

  return 0;
}