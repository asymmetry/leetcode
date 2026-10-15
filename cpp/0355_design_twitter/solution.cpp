#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Twitter {
 public:
  Twitter()
      : news_feed(std::vector<std::pair<int, int>>()),
        followed(std::unordered_map<int, std::unordered_set<int>>()) {}

  void postTweet(int userId, int tweetId) {
    news_feed.emplace_back(userId, tweetId);
  }

  vector<int> getNewsFeed(int userId) {
    auto& followees = followed[userId];
    std::vector<int> result;
    for (int j = (int)news_feed.size() - 1; j >= 0; j--) {
      if (news_feed[j].first == userId ||
          followees.find(news_feed[j].first) != followees.end()) {
        result.push_back(news_feed[j].second);
        if (result.size() >= 10) break;
      }
    }
    return result;
  }

  void follow(int followerId, int followeeId) {
    followed[followerId].insert(followeeId);
  }

  void unfollow(int followerId, int followeeId) {
    if (followed.find(followerId) != followed.end()) {
      followed[followerId].erase(followeeId);
    }
  }

 private:
  std::vector<std::pair<int, int>> news_feed;
  std::unordered_map<int, std::unordered_set<int>> followed;
};

void printNewsFeed(const vector<int>& newsFeed) {
  cout << "[";
  for (size_t i = 0; i < newsFeed.size(); ++i) {
    cout << newsFeed[i];
    if (i != newsFeed.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Twitter* obj = new Twitter();
  obj->postTweet(1, 5);
  printNewsFeed(obj->getNewsFeed(1));
  obj->follow(1, 2);
  obj->postTweet(2, 6);
  printNewsFeed(obj->getNewsFeed(1));
  obj->unfollow(1, 2);
  printNewsFeed(obj->getNewsFeed(1));

  return 0;
}