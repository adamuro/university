#include <iostream>
#include <set>

using StringSet = std::set<std::string>;

int main(int argc, char const *argv[]) {
  StringSet strings {"jeden", "dwa", "trzy", "cztery"};

  for (auto &&string : strings) {
    std::cout << string << std::endl;
  }

  return 0;
}
