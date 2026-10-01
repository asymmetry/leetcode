#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string getHint(string secret, string guess) {
    int counter_s[10] = {};
    int counter_g[10] = {};

    int a = 0;
    int b = 0;
    size_t len = secret.size();
    for (size_t i = 0; i < len; i++) {
      if (secret[i] == guess[i]) {
        a++;
        continue;
      }
      counter_s[secret[i] - '0']++;
      counter_g[guess[i] - '0']++;
    }

    for (int i = 0; i < 10; i++) {
      if (counter_g[i] > 0) b += std::min(counter_g[i], counter_s[i]);
    }

    return std::to_string(a) + "A" + std::to_string(b) + "B";
  }
};

int main() {
  string secret = "1807";
  string guess = "7810";

  Solution solution;
  auto result = solution.getHint(secret, guess);

  std::cout << result << std::endl;

  return 0;
}