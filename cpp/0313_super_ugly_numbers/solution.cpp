#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct Item {
  int value;
  int index;
  int prime;

  bool operator<(const Item& other) const { return value < other.value; }
  bool operator>(const Item& other) const { return value > other.value; }
};

class Solution {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    std::vector<int> nums;
    nums.push_back(1);

    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;
    for (int i = 0; i < (int)primes.size(); i++) {
      Item item = {1 * primes[i], 0, primes[i]};
      pq.push(item);
    }

    for (int i = 1; i < n; i++) {
      Item next = pq.top();
      pq.pop();

      printf("Next value: %d, Index: %d, Prime: %d\n", next.value, next.index,
             next.prime);

      if (next.value == nums.back()) {
        int next_value = std::numeric_limits<int>::max();
        if (next.index + 1 < (int)nums.size() &&
            nums[next.index + 1] <= next_value / next.prime)
          next_value = nums[next.index + 1] * next.prime;
        Item item = {next_value, next.index + 1, next.prime};
        pq.push(item);
        i--;
        continue;
      }

      nums.push_back(next.value);
      int next_value = std::numeric_limits<int>::max();
      if (nums[next.index + 1] <= next_value / next.prime)
        next_value = nums[next.index + 1] * next.prime;
      Item item = {next_value, next.index + 1, next.prime};
      pq.push(item);
    }

    return nums.back();
  }
};

int main() {
  int n = 12;
  std::vector<int> primes = {2, 7, 13, 19};

  auto solution = new Solution();
  auto result = solution->nthSuperUglyNumber(n, primes);

  std::cout << result << std::endl;

  return 0;
}