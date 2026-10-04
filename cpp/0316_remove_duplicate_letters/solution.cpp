#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string removeDuplicateLetters(string s) {
    std::vector<int> test(26, 0);
    for (const auto& ch : s) {
      int ch_i = (int)(ch - 'a');
      test[ch_i] = 1;
    }

    std::vector<char> alphabet;
    for (int i = 0; i < 26; i++) {
      if (test[i] == 1) {
        alphabet.push_back((char)((int)'a' + i));
      }
    }

    int used = 0;

    std::string result;
    addLetter(s, 0, alphabet, used, result);

    return result;
  }

 private:
  bool addLetter(const string& s, int si, const std::vector<char>& alphabet,
                 int used, string& result) {
    int sl = (int)s.size();
    int al = (int)alphabet.size();

    int all_used = (1 << al) - 1;

    if (used == all_used) {
      return true;
    } else if (si >= sl) {
      return false;
    }

    int test_used = used;
    for (int i = 0; i < al; i++) {
      if ((used & (1 << i)) > 0) continue;
      for (int j = si; j < sl; j++) {
        if (s[j] == alphabet[i]) {
          test_used |= (1 << i);
          break;
        }
      }
    }

    if (test_used != all_used) {
      return false;
    }

    for (int i = 0; i < al; i++) {
      if ((used & (1 << i)) > 0) continue;
      for (int j = si; j < sl; j++) {
        if (s[j] == alphabet[i]) {
          used |= (1 << i);
          result.push_back(alphabet[i]);
          if (addLetter(s, j + 1, alphabet, used, result)) {
            return true;
          }
          used &= ~(1 << i);
          result.pop_back();
        }
      }
    }

    return false;
  }
};

int main() {
  std::string s = "cbacdcbc";

  auto solution = new Solution();
  auto result = solution->removeDuplicateLetters(s);

  std::cout << result << std::endl;

  return 0;
}