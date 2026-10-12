#include <algorithm>
#include <deque>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> findItinerary(vector<vector<string>>& tickets) {
    std::unordered_map<string, std::deque<string>> map;
    for (const auto& ticket : tickets) {
      map[ticket[0]].push_back(ticket[1]);
    }

    for (auto& [k, v] : map) {
      std::sort(v.begin(), v.end());
    }

    std::vector<string> result;

    std::string cur = "JFK";
    while (!map.empty() && map[cur].size() > 0) {
      result.push_back(cur);
      cur = map[cur].front();
      map[result.back()].pop_front();
      if (map[result.back()].empty()) {
        map.erase(result.back());
      }
    }

    result.push_back(cur);
    if (map[cur].empty()) {
      map.erase(cur);
    }

    while (!map.empty()) {
      for (int i = (int)result.size() - 1; i >= 0; i--) {
        if (map.find(result[i]) != map.end()) {
          auto circle = hierholzer(map, result[i]);
          result.insert(result.begin() + i, circle.begin(), circle.end() - 1);
          break;
        }
      }
    }

    return result;
  }

 private:
  std::vector<std::string> hierholzer(
      std::unordered_map<string, std::deque<string>>& map,
      std::string& airport) {
    std::vector<std::string> result;
    std::string cur = airport;
    while (!map.empty() && map[cur].size() > 0) {
      result.push_back(cur);
      cur = map[cur].front();
      map[result.back()].pop_front();
      if (map[result.back()].empty()) {
        map.erase(result.back());
      }
    }

    result.push_back(cur);
    if (map[cur].empty()) {
      map.erase(cur);
    }

    return result;
  }
};

int main() {
  vector<vector<string>> tickets = {{"JFK", "SFO"},
                                    {"JFK", "ATL"},
                                    {"SFO", "ATL"},
                                    {"ATL", "JFK"},
                                    {"ATL", "SFO"}};

  Solution solution;
  auto result = solution.findItinerary(tickets);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}