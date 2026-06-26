#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minDistance(string word1, string word2) {
    int len1 = (int)word1.size();
    int len2 = (int)word2.size();

    if (len1 == 0) return (int)word2.size();
    if (len2 == 0) return (int)word1.size();

    vector<vector<int>> dists(len1 + 1, vector<int>(len2 + 1, 0));
    for (int i = 1; i <= len1; i++) dists[i][0] = i;
    for (int j = 1; j <= len2; j++) dists[0][j] = j;

    for (int i = 1; i <= len1; i++) {
      for (int j = 1; j <= len2; j++) {
        dists[i][j] = std::min(dists[i - 1][j] + 1, dists[i][j - 1] + 1),
        dists[i][j] = std::min(dists[i - 1][j - 1] + 1, dists[i][j]);
        if (word1[i - 1] == word2[j - 1])
          dists[i][j] = std::min(dists[i - 1][j - 1], dists[i][j]);
      }
    }

    return dists[len1][len2];
  }
};

int main() {
  string word1 = "horse";
  string word2 = "ros";

  Solution solution;
  auto result = solution.minDistance(word1, word2);

  std::cout << result << std::endl;

  return 0;
}