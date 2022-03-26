#include <iostream>

template<int A, int B>
class GCD {
  public:
    static constexpr int value = GCD<B, A % B>::value;
    constexpr int operator() () {
      return value;
    }
};

template<int A>
class GCD<A, 0> {
  public:
    static constexpr int value = A;
    constexpr int operator() () {
      return value;
    }
};

int main(int argc, char const *argv[]) {
  std::cout << GCD<1, 23>()() << std::endl;
  std::cout << GCD<6, 23>()() << std::endl;
  std::cout << GCD<9, 27>()() << std::endl;
  std::cout << GCD<10, 24>()() << std::endl;
  std::cout << GCD<30, 12>()() << std::endl;

  return 0;
}
