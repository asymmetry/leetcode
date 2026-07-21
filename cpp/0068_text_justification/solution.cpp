#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> result;

    std::queue<string> line;
    int line_len = 0;
    for (const auto& word : words) {
      if (line_len + (int)line.size() + (int)word.size() > maxWidth) {
        if (line.size() == 1) {
          string new_line(line.front());
          line.pop();
          new_line.append(maxWidth - line_len, ' ');

          result.push_back(new_line);
        } else {
          int n_space = (maxWidth - line_len) / ((int)line.size() - 1);
          int rest = (maxWidth - line_len) % ((int)line.size() - 1);

          string new_line;
          while (!line.empty()) {
            new_line.append(line.front());
            line.pop();
            if (!line.empty()) {
              if (rest > 0) {
                new_line.append(n_space + 1, ' ');
                rest--;
              } else {
                new_line.append(n_space, ' ');
              }
            }
          };

          result.push_back(new_line);
        }

        line_len = (int)word.size();
        line.push(word);
      } else {
        line_len += (int)word.size();
        line.push(word);
      }
    }

    string new_line;
    while (!line.empty()) {
      new_line.append(line.front());
      line.pop();
      if (!line.empty()) {
        new_line.push_back(' ');
      }
    };

    if (!new_line.empty()) {
      new_line.append(maxWidth - (int)new_line.size(), ' ');
      result.push_back(new_line);
    }

    return result;
  }
};

int main() {
  vector<string> words = {"ask", "not", "what", "your", "country", "can",
                          "do",  "for", "you",  "ask",  "what",    "you",
                          "can", "do",  "for",  "your", "country"};
  int maxWidth = 16;

  Solution solution;
  auto result = solution.fullJustify(words, maxWidth);

  for (int i = 0; i < (int)result.size(); ++i) {
    std::cout << "\"" << result[i] << "\"" << std::endl;
  }

  return 0;
}