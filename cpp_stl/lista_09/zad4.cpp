#include <iostream>
#include <regex>

int main() {
  std::string inputComplex;
  std::regex complexRegex(R"(\(-?[[:digit:]]+(.[[:digit:]]+)?[\+-][[:digit:]]+(\.[[:digit:]]+)?[iI]\))");

  while(true) {
    std::cin >> inputComplex;
    std::cout << std::regex_match(inputComplex, complexRegex) << std::endl;
  }

  return 0;
}
