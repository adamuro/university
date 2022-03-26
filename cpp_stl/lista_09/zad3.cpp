#include <iostream>
#include <regex>

int main() {
  std::string inputCity;
  std::regex cityRegex("([[:upper:]][[:lower:]]*)" // Pierwsze słowo
                       "(([[:space:]]+|-)[[:upper:]][[:lower:]]*)*"); // Kolejne słowa

  while(true) {
    std::getline(std::cin, inputCity);
    std::cout << std::regex_match(inputCity, cityRegex) << std::endl;
  }

  return 0;
}
