#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Node {
 public:
  int val;
  vector<Node*> neighbors;
  Node() {
    val = 0;
    neighbors = vector<Node*>();
  }
  Node(int _val) {
    val = _val;
    neighbors = vector<Node*>();
  }
  Node(int _val, vector<Node*> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};

Node* createGraph(const vector<vector<int>>& adjList) {
  int len = (int)adjList.size();

  vector<Node*> nodes(len, nullptr);
  for (int i = 0; i < len; i++) {
    nodes[i] = new Node(i + 1);
  }

  for (int i = 0; i < len; i++) {
    for (int j : adjList[i]) {
      nodes[i]->neighbors.push_back(nodes[j - 1]);
    }
  }

  return len > 0 ? nodes[0] : nullptr;
}

void printGraph(Node* node) {
  if (node == nullptr) return;

  unordered_set<Node*> visited;
  vector<Node*> nodes = {node};

  vector<vector<int>> result;

  while (!nodes.empty()) {
    Node* curr = nodes.back();
    nodes.pop_back();

    if (visited.find(curr) != visited.end()) continue;
    visited.insert(curr);

    vector<int> vals;
    for (auto* neighbor : curr->neighbors) {
      nodes.push_back(neighbor);
      vals.push_back(neighbor->val);
    }
    result.push_back(vals);
  }

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << "[";
    for (size_t j = 0; j < result[i].size(); j++) {
      std::cout << result[i][j];
      if (j < result[i].size() - 1) std::cout << ",";
    }
    std::cout << "]";
    if (i < result.size() - 1) std::cout << ",";
  }
  std::cout << "]";
}

class Solution {
 public:
  Node* cloneGraph(Node* node) {
    if (node == nullptr) return nullptr;

    std::unordered_set<Node*> visited;
    std::vector<Node*> nodes = {node};

    std::unordered_map<Node*, Node*> cloned;

    while (!nodes.empty()) {
      Node* curr = nodes.back();
      nodes.pop_back();

      if (visited.find(curr) != visited.end()) continue;
      visited.insert(curr);

      Node* cloned_curr;
      if (cloned.find(curr) == cloned.end()) {
        cloned_curr = new Node(curr->val);
        cloned[curr] = cloned_curr;
      } else {
        cloned_curr = cloned[curr];
      }

      for (auto* neighbor : curr->neighbors) {
        nodes.push_back(neighbor);

        if (cloned.find(neighbor) == cloned.end()) {
          Node* cloned_neighbor = new Node(neighbor->val);
          cloned[neighbor] = cloned_neighbor;
          cloned_curr->neighbors.push_back(cloned_neighbor);
        } else {
          cloned_curr->neighbors.push_back(cloned[neighbor]);
        }
      }
    }

    return cloned[node];
  }
};

int main() {
  vector<vector<int>> adjList = {
      {2, 4},
      {1, 3},
      {2, 4},
      {1, 3},
  };
  Node* graph = createGraph(adjList);

  Solution solution;
  auto result = solution.cloneGraph(graph);

  printGraph(result);
  std::cout << std::endl;

  return 0;
}