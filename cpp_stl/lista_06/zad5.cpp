#include <iostream>
#include <algorithm>

void generatePermutations(std::string s) {
  std::sort(s.begin(), s.end());
  do {
    std::cout << s << std::endl;
  } while (std::next_permutation(s.begin(), s.end()));
}

int main(int argc, char const *argv[]) {
  std::string s = "4213";
  generatePermutations(s);

  return 0;
}
