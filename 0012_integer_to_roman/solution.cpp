#include <iostream>
#include <vector>

using namespace std;

auto speedup = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}();

class Solution {
 public:
  string intToRoman(int num) {
    string result = "";

    while (num > 0) {
      if (num >= 1000) {
        result.push_back('M');
        num -= 1000;
      } else if (num >= 900) {
        result += "CM";
        num -= 900;
      } else if (num >= 500) {
        result.push_back('D');
        num -= 500;
      } else if (num >= 400) {
        result += "CD";
        num -= 400;
      } else if (num >= 100) {
        result.push_back('C');
        num -= 100;
      } else if (num >= 90) {
        result += "XC";
        num -= 90;
      } else if (num >= 50) {
        result.push_back('L');
        num -= 50;
      } else if (num >= 40) {
        result += "XL";
        num -= 40;
      } else if (num >= 10) {
        result.push_back('X');
        num -= 10;
      } else if (num >= 9) {
        result += "IX";
        num -= 9;
      } else if (num >= 5) {
        result.push_back('V');
        num -= 5;
      } else if (num >= 4) {
        result += "IV";
        num -= 4;
      } else {
        result.push_back('I');
        num -= 1;
      }
    }

    return result;
  }
};

int main() {
  int num = 1994;

  Solution solution;
  auto result = solution.intToRoman(num);

  std::cout << result << std::endl;

  return 0;
}