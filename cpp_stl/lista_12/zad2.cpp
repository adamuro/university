#include <iostream>

template<int N>
class Factorial {
  public:
    static constexpr int value = N * Factorial<N - 1>::value;
    constexpr int operator() () {
      return value;
    }
};

template<>
class Factorial<0> {
  public:
    static constexpr int value = 1;
    constexpr int operator() () {
      return value;
    }
};

template <int N, int K>
class Binomial {
  public:
    static constexpr int value = Factorial<N>::value / (Factorial<K>::value * Factorial<N - K>::value);
    constexpr int operator() () {
      return value;
    }
};

int main(int argc, char const *argv[]) {
  std::cout << Binomial<0, 0>()() << std::endl;
  std::cout << Binomial<3, 0>()() << std::endl;
  std::cout << Binomial<5, 2>()() << std::endl;
  std::cout << Binomial<8, 3>()() << std::endl;
  std::cout << Binomial<3, 3>()() << std::endl;

  return 0;
}

