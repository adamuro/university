#include <iostream>
#include <iomanip>
#include <limits>

int main(int argc, char const *argv[]) {
  std::cout << "Najmniejszy dodatni float: " << std::numeric_limits<float>::min() <<
  std::endl << "Najmniejszy dodatni double: "  << std::numeric_limits<double>::min() <<
  std::endl << "Maksymalna wartość float: " << std::numeric_limits<float>::max() <<
  std::endl << "Maksymalna wartość double: " << std::numeric_limits<double>::max() <<
  std::endl << "Epsilon float: " << std::numeric_limits<float>::epsilon() <<
  std::endl << "Epsilon double: " << std::numeric_limits<double>::epsilon() << std::endl;

  return 0;
}
