#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> diffWaysToCompute(string expression) {
    std::vector<int> numbers;
    std::vector<char> operators;
    size_t i = 0;
    while (i < expression.size()) {
      if (isdigit(expression[i])) {
        int num = 0;
        while (i < expression.size() && isdigit(expression[i])) {
          num = num * 10 + (expression[i] - '0');
          i++;
        }
        numbers.push_back(num);
      } else {
        operators.push_back(expression[i]);
        i++;
      }
    }

    return _diffWaysToCompute(numbers, operators);
  }

 private:
  vector<int> _diffWaysToCompute(const std::vector<int>& numbers,
                                 const std::vector<char>& operators) {
    if (operators.size() == 0) {
      return {numbers[0]};
    }

    if (operators.size() == 1) {
      std::vector<int> result;
      if (operators[0] == '+') {
        result.push_back(numbers[0] + numbers[1]);
      } else if (operators[0] == '-') {
        result.push_back(numbers[0] - numbers[1]);
      } else if (operators[0] == '*') {
        result.push_back(numbers[0] * numbers[1]);
      }
      return result;
    }

    std::vector<int> result;

    size_t oc = operators.size();
    size_t nc = numbers.size();
    for (size_t i = 0; i < oc; i++) {
      if (i == 0) {
        std::vector<int> right_numbers(numbers.begin() + 1, numbers.end());
        std::vector<char> right_operators(operators.begin() + 1,
                                          operators.end());
        auto right_result = _diffWaysToCompute(right_numbers, right_operators);
        for (auto&& n : right_result) {
          if (operators[0] == '+') {
            result.push_back(numbers[0] + n);
          } else if (operators[0] == '-') {
            result.push_back(numbers[0] - n);
          } else if (operators[0] == '*') {
            result.push_back(numbers[0] * n);
          }
        }
      } else if (i == oc - 1) {
        std::vector<int> left_numbers(numbers.begin(),
                                      numbers.begin() + nc - 1);
        std::vector<char> left_operators(operators.begin(),
                                         operators.end() - 1);
        auto left_result = _diffWaysToCompute(left_numbers, left_operators);
        for (auto&& n : left_result) {
          if (operators[oc - 1] == '+') {
            result.push_back(n + numbers[nc - 1]);
          } else if (operators[oc - 1] == '-') {
            result.push_back(n - numbers[nc - 1]);
          } else if (operators[oc - 1] == '*') {
            result.push_back(n * numbers[nc - 1]);
          }
        }
      } else {
        std::vector<int> left_numbers(numbers.begin(), numbers.begin() + i + 1);
        std::vector<char> left_operators(operators.begin(),
                                         operators.begin() + i);
        auto left_result = _diffWaysToCompute(left_numbers, left_operators);

        std::vector<int> right_numbers(numbers.begin() + i + 1, numbers.end());
        std::vector<char> right_operators(operators.begin() + i + 1,
                                          operators.end());
        auto right_result = _diffWaysToCompute(right_numbers, right_operators);

        for (auto&& ln : left_result) {
          for (auto&& rn : right_result) {
            if (operators[i] == '+') {
              result.push_back(ln + rn);
            } else if (operators[i] == '-') {
              result.push_back(ln - rn);
            } else if (operators[i] == '*') {
              result.push_back(ln * rn);
            }
          }
        }
      }
    }

    return result;
  }
};

int main() {
  std::string expression = "2-1-1";

  Solution solution;
  auto result = solution.diffWaysToCompute(expression);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i];
    if (i < result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}
