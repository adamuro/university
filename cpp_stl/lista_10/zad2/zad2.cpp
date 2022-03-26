#include <iostream>
#include <fstream>
#include <iterator>
#include <numeric>
#include <vector>

int32_t eulersFunction(uint32_t n) {
  int32_t k = 0;

  for (int i = 1; i <= n; i++) {
    if (std::gcd(n, i) == 1) k++;
  }

  return k;
}

int main(int argc, char const *argv[]) {
  const int k = 100;
  std::vector<int> eulersValues;

  for (int i = 1; i <= k; i++) {
    eulersValues.push_back(eulersFunction(i));
  }

  std::ofstream os("phi.txt");
  std::ostream_iterator<int> osit(os, "; ");
  std::copy(eulersValues.begin(), eulersValues.end(), osit);
  
  return 0;
}
