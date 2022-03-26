#include <iostream>
#include <complex>
#include <vector>
#include <numeric>

using Z = std::complex<double>;

Z polynomialValue(std::vector<Z> v, double x) {
  double xVal = 1;
  return std::accumulate(v.begin(), v.end(), Z(0.0, 0.0), [=](const Z &init, const Z &val) mutable {
    Z result = init + val * xVal;
    xVal *= x;
    return result;
  });
}

int main(int argc, char const *argv[]) {
  std::vector<Z> v1 {Z(1, 0), Z(1, 0), Z(1, 0)};
  std::cout << polynomialValue(v1, 2) << std::endl;

  std::vector<Z> v2 {Z(1.5, 2.0), Z(2.5, 1.0), Z(-1.0, -1.5), Z(3.0, -0.5)};
  std::cout << polynomialValue(v2, 3.5) << std::endl;

  return 0;
}
