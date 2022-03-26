#include <iostream>

template<int N>
class LucasNumber {
  public:
    static constexpr int value = LucasNumber<N - 1>::value + LucasNumber<N - 2>::value;
    constexpr int operator() (){
      return value;
    }
};

template<>
class LucasNumber<0> {
  public:
    static constexpr int value = 2;
    constexpr int operator() (){
      return value;
    }
};

template<>
class LucasNumber<1> {
  public:
    static constexpr int value = 1;
    constexpr int operator() (){
      return value;
    }
};

int main(int argc, char const *argv[]) {
  std::cout << LucasNumber<0>()() << std::endl;
  std::cout << LucasNumber<1>()() << std::endl;
  std::cout << LucasNumber<5>()() << std::endl;
  std::cout << LucasNumber<20>()() << std::endl;

  return 0;
}
