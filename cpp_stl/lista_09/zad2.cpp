#include <iostream>
#include <regex>

int main() {
  std::string inputDate;
  std::regex dateRegex("(((0[1-9]|[1-2][0-9]|3[0-1])-(01|03|05|07|08|10|12))|" // Miesiące z 31 dniami
                       "((0[1-9]|[1-2][0-9]|30)-(04|06|09|11))|" // Miesiące z 30 dniami
                       "((0[1-9]|1[0-9]|2[0-8])-02))" // Luty - 28 dni
                       "-([1-9][0-9]{0,3})"); // Rok 1-9999

  while(true) {
    std::cin >> inputDate;
    std::cout << std::regex_match(inputDate, dateRegex) << std::endl;
  }

  return 0;
}