#include <iostream>
#include <regex>

int main() {
  std::string inputHour;
  std::regex hourRegex("([0-1][0-9]|2[0-3]):([0-5][0-9])(:[0-5][0-9])?");

  while (true) {
    std::cin >> inputHour;
    std::cout << std::regex_match(inputHour, hourRegex) << std::endl;
  }
  
  return 0;
}
