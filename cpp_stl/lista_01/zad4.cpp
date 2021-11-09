#include <iostream>

enum class Name: uint16_t {
  Adam,
  Basia,
  Celina,
  Dariusz,
};

void greet(const std::string &greeting, const Name &name) {
  switch (name) {
    case Name::Adam:
      std::cout << greeting << " Adam" << std::endl;
      break;
    case Name::Basia:
      std::cout << greeting << " Basia" << std::endl;
      break;
    case Name::Celina:
      std::cout << greeting << " Celina" << std::endl;
      break;
    case Name::Dariusz:
      std::cout << greeting << " Dariusz" << std::endl;
      break;
    default:
      break;
  }
}

int main(int argc, char const *argv[]) {
  greet("Dzień dobry", Name::Adam);
  greet("Witaj", Name::Celina);

  return 0;
}
