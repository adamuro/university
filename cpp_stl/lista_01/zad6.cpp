#include <iostream>
#include <cmath>

int main(int argc, char const *argv[]) {
  double a, b, c;

  std::cin >> a >> b >> c;

  if (double delta = (b * b) - (4 * a * c); delta == 0.0) {
    std::cout << -b / (2 * a) << std::endl;
  } else if (delta > 0.0) {
    std::cout << (-b - sqrt(delta)) / (2 * a) << " ";
    std::cout << (-b + sqrt(delta)) / (2 * a) << std::endl;
  } else {
    std::cout << "Brak pierwiastków rzeczywistych" << std::endl;
  }

  return 0;
}
