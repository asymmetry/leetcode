#include <iostream>
#include <vector>

using namespace std;

class SummaryRanges {
 public:
  SummaryRanges() : values(std::vector<int>(10001, 0)) {}

  void addNum(int value) { values[value] = 1; }

  vector<vector<int>> getIntervals() {
    vector<vector<int>> intervals;
    int i = 0;
    while (i < values.size()) {
      if (values[i] == 1) {
        int start = i;
        while (i < values.size() && values[i] == 1) {
          i++;
        }
        intervals.push_back({start, i - 1});
      } else {
        i++;
      }
    }
    return intervals;
  }

 private:
  std::vector<int> values;
};

void printIntervals(const vector<vector<int>>& intervals) {
  cout << "[";
  for (size_t i = 0; i < intervals.size(); ++i) {
    cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]";
    if (i != intervals.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  SummaryRanges* obj = new SummaryRanges();
  obj->addNum(1);
  printIntervals(obj->getIntervals());
  obj->addNum(3);
  printIntervals(obj->getIntervals());
  obj->addNum(7);
  printIntervals(obj->getIntervals());
  obj->addNum(2);
  printIntervals(obj->getIntervals());
  obj->addNum(6);
  printIntervals(obj->getIntervals());

  return 0;
}