#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

auto mostCommonElements(std::vector<int> v) {
  std::unordered_map<int, int> map;
  std::vector<std::pair<int, int>> result;

  std::for_each(v.begin(), v.end(), [&map](int n) {
    map[n]++;
  });

  for (auto &element : map) {
    int key = element.first;
    int val = element.second;

    result.push_back(std::make_pair(key, val));
  }

  auto maxOccurencesPair = std::max_element(result.begin(), result.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) {
    return p1.second < p2.second;
  });

  auto eraseIterator = std::partition(result.begin(), result.end(), [&maxOccurencesPair](std::pair<int, int> p) {
    return p.second == maxOccurencesPair->second;
  });

  result.erase(eraseIterator, result.end());

  return result;
}

void printVector(std::vector<std::pair<int, int>> v) {
  for (auto &p : v) {
    std::cout << p.first << ": " << p.second << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  std::vector<int> v {1, 5, 1, 3, 1, 5, 4, 4, 2, 4, 1, 4, 2, 5};
  printVector(mostCommonElements(v));

  return 0;
}
