#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<double> calcEquation(vector<vector<string>>& equations,
                              vector<double>& values,
                              vector<vector<string>>& queries) {
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>
        map;

    int len = (int)equations.size();
    for (int i = 0; i < len; i++) {
      map[equations[i][0]].push_back({equations[i][1], values[i]});
      map[equations[i][1]].push_back({equations[i][0], 1.0 / values[i]});
    }

    std::unordered_set<std::string> visited;

    std::vector<double> result;
    for (const auto& query : queries) {
      if (map.find(query[0]) == map.end() || map.find(query[1]) == map.end()) {
        result.push_back(-1.0);
        continue;
      }

      if (query[0] == query[1]) {
        result.push_back(1.0);
        continue;
      }

      visited.clear();
      result.push_back(dfs(map, query[0], query[1], 1.0, visited));
    }

    return result;
  }

 private:
  double dfs(const std::unordered_map<
                 std::string, std::vector<std::pair<std::string, double>>>& map,
             const std::string& start, const std::string& stop, double length,
             std::unordered_set<std::string> visited) {
    if (start == stop) return length;

    for (const auto& edge : map.at(start)) {
      if (visited.find(edge.first) != visited.end()) continue;
      visited.insert(start);
      double val = dfs(map, edge.first, stop, length * edge.second, visited);
      if (val > 0.0) return val;
      visited.erase(start);
    }

    return -1.0;
  }
};

int main() {
  std::vector<std::vector<string>> equations = {{"a", "b"}, {"b", "c"}};
  std::vector<double> values = {2.0, 3.0};
  std::vector<std::vector<string>> queries = {
      {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};

  Solution solution;
  auto result = solution.calcEquation(equations, values, queries);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i];
    if (i != result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}