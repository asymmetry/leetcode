#include <iostream>
#include <vector>

using namespace std;

static const std::vector<std::string> below_20 = {
    "",        "One",     "Two",       "Three",    "Four",
    "Five",    "Six",     "Seven",     "Eight",    "Nine",
    "Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
    "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

static const std::vector<std::string> tens_s = {
    "",      "",      "Twenty",  "Thirty", "Forty",
    "Fifty", "Sixty", "Seventy", "Eighty", "Ninety",
};

class Solution {
 public:
  string numberToWords(int num) {
    if (num == 0) return "Zero";

    int o = num % 1000;
    num = num / 1000;
    int k = num % 1000;
    num = num / 1000;
    int m = num % 1000;
    int b = num / 1000;

    auto result = helper(o);
    if (k > 0) {
      result = helper(k) + " Thousand " + result;
    }
    if (m > 0) {
      result = helper(m) + " Million " + result;
    }
    if (b > 0) {
      result = helper(b) + " Billion " + result;
    }

    const auto start = result.find_first_not_of(" ");
    const auto end = result.find_last_not_of(" ");
    result = result.substr(start, end - start + 1);

    size_t pos = result.find("  ");
    while (pos != std::string::npos) {
      result.replace(pos, 2, " ");
      pos = result.find("  ");
    }

    return result;
  }

 private:
  std::string helper(int num) {
    int hundreds = num / 100;
    int rest = num % 100;

    std::string result;
    if (rest < 20) {
      result = below_20[rest];
    } else {
      int ones = rest % 10;
      rest = rest / 10;
      int tens = rest % 10;

      result = tens_s[tens] + " " + below_20[ones];
    }

    if (hundreds > 0) {
      result = below_20[hundreds] + " Hundred " + result;
    }

    return result;
  }
};

int main() {
  int num = 123;

  auto solution = new Solution();
  auto result = solution->numberToWords(num);

  std::cout << result << std::endl;

  return 0;
}