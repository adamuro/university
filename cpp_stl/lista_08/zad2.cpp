#include <iostream>
#include <complex>

template <typename T>
std::complex<T> gamma(std::complex<T> z, uint32_t iterations) {
  std::complex<T> result = 1;

  for (uint32_t i = 1; i <= iterations; i++) {
    result *= pow(1.0 + (1.0 / static_cast<T>(i)), z) / (1.0 + (z / static_cast<T>(i)));
  }

  return result / z;
}

template <typename T>
std::complex<T> inverseGamma(std::complex<T> z, uint32_t iterations) {
  std::complex<T> result = 1;

  constexpr T y = 0.5772156649;
  constexpr T e = exp(1.0);

  for(uint32_t i = 1; i <= iterations; i++) {
    result *=  (1.0 + (z / static_cast<T>(i))) * pow(e, -z / static_cast<T>(i));
  }

  return result * z * pow(e, y * z);
}

int main(int argc, char const *argv[]) {
  std::complex<double> z(1.0, 2.0);

  std::cout << "gamma: " << gamma(z, 100) << std::endl;
  std::cout << "odwrotność gammy: " << inverseGamma(z, 100) << std::endl;
  std::cout << "iloczyn: " << gamma(z, 100) * inverseGamma(z, 100) << std::endl;

  return 0;
}
