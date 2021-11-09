#include <iostream>
#include <ratio>

// template<int n>
// auto HarmonicNumber() {
//     if constexpr (n == 1) {
//         return std::ratio<1, 1>();
//     } else {
//         return std::ratio_add<std::ratio<1, n>, decltype(HarmonicNumber<n - 1>())>();
//     }
// }

template<intmax_t n>
class HarmonicNumber {
  public:
    static constexpr intmax_t num = std::ratio_add<HarmonicNumber<n - 1>, std::ratio<1, n>>::num;
    static constexpr intmax_t den = std::ratio_add<HarmonicNumber<n - 1>, std::ratio<1, n>>::den;
};

template<>
class HarmonicNumber<1> {
  public:
    static constexpr intmax_t num = std::ratio<1, 1>::num;
    static constexpr intmax_t den = std::ratio<1, 1>::den;
};

int main(int argc, char const *argv[]) {
  std::cout << HarmonicNumber<1>::num << " / " << HarmonicNumber<1>::den << std::endl;
  std::cout << HarmonicNumber<2>::num << " / " << HarmonicNumber<2>::den << std::endl;
  std::cout << HarmonicNumber<3>::num << " / " << HarmonicNumber<3>::den << std::endl;
  std::cout << HarmonicNumber<4>::num << " / " << HarmonicNumber<4>::den << std::endl;
  std::cout << HarmonicNumber<5>::num << " / " << HarmonicNumber<5>::den << std::endl;
  std::cout << HarmonicNumber<6>::num << " / " << HarmonicNumber<6>::den << std::endl;
  std::cout << HarmonicNumber<7>::num << " / " << HarmonicNumber<7>::den << std::endl;
  std::cout << HarmonicNumber<8>::num << " / " << HarmonicNumber<8>::den << std::endl;
  std::cout << HarmonicNumber<9>::num << " / " << HarmonicNumber<9>::den << std::endl;

  std::cout << HarmonicNumber<46>::num << " / " << HarmonicNumber<46>::den << std::endl;

  // std::cout << decltype(HarmonicNumber<46>())::num << " / " << decltype(HarmonicNumber<46>())::den << std::endl;
  return 0;
}
