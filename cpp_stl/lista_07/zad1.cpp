#include <iostream>
#include <random>

template <typename T>
void permutate(std::vector<T> &v) {
  std::vector<T> permutation;
  std::random_device rd;
  std::mt19937 mt(rd());

  for (int i = 1; i <= v.size(); i++) {
    std::uniform_int_distribution<int> uniform(0, v.size() - i);
    int randomIndex = uniform(mt);
    T elem = v.at(randomIndex);
    v.erase(v.begin() + randomIndex);
    v.push_back(elem);
  }
}

template <typename T>
void printVector(std::vector<T> &v) {
  for (auto val : v) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9};
  printVector(v);
  permutate(v);
  printVector(v);
  permutate(v);
  printVector(v);

  return 0;
}
