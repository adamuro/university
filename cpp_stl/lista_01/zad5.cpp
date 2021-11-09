#include <iostream>

auto nthLucasNumber(uint32_t n) {
  if (n <= 0) return 2;
  if (n == 1) return 1;

  return nthLucasNumber(n - 1) + nthLucasNumber(n - 2);
}

int main(int argc, char const *argv[])
{
  std::cout << nthLucasNumber(10) << std::endl;
  return 0;
}
