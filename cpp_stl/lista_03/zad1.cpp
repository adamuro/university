#include <iostream>
#include <limits>

int main(int argc, char const *argv[]) {
  std::cout << "Max: " << std::numeric_limits<long long>::max() <<
  std::endl << "Min: " << std::numeric_limits<long long>::min() <<
  std::endl << "Liczba bitów: " << std::numeric_limits<long long>::digits <<
  std::endl << "Liczba cyfr dziesiętnych: " << std::numeric_limits<long long>::digits10 << std::endl;
  
  return 0;
}
