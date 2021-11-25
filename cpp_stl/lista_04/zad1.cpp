#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>

template <typename T>
class PrintInRange {
private:
  T a, b;
public:
  PrintInRange(T _a, T _b) : a(_a), b(_b) {}

  void operator () (const T val) {
    if (val > a && val < b) {
      std::cout << val << " ";
    }
  }
};

template <typename T>
class PrintEveryNth {
private:
  int k, p;
  int i = 0;
public:
  PrintEveryNth(int _k, int _p) : k(_k), p(_p) {}

  void operator () (const T val) {
    if (i >= p && (i - p) % k == 0) {
      std::cout << val << " ";
    }
    i++;
  }
};

template <typename T>
class Average {
private:
  int i = 0;
public:
  T operator () (const T &init, const T &val) {
    return (init * i) / ++i + val / i;
  }
};

template <typename C, typename T>
auto MinMax(const C &collection) {
  auto min = collection.begin();
  auto max = collection.begin();
  auto i = collection.begin();

  std::for_each(collection.begin(), collection.end(), [&](T val) {
    if (val < *min) {
      min = i;
    } else if (val > *max) {
      max = i;
    }
    i++;
  });

  return std::make_pair(min, max);
}

template <typename T>
class Concatenate {
public:
  T operator () (const T &init, const T &val) {
    return init + val;
  }
};


int main(int argc, char const *argv[]) {
  std::vector<double> v { -99.01, -16.3, -4.0, -1.113, 0.0, 0.2, 1.1, 4.2, 6.9, 21.24, 55.555 };
  std::list<std::string> l { "asd", "br843", "c45gg", "dddd", "eeEEEeeEeEEeee", "un4g473", "jds"};
  std::set<int> s {-24, -9, -5, -2, 0, 3, 4, 8, 100, 222 };

  std::cout << "a) Wypisz wszystkie wartości z zadanego zakresu (większe od a i mniejsze od b)" << std::endl;
  std::for_each(v.begin(), v.end(), PrintInRange<double>(-10.0, 10.0));
  std::cout << std::endl;
  std::for_each(l.begin(), l.end(), PrintInRange<std::string>("b", "f"));
  std::cout << std::endl;
  std::for_each(s.begin(), s.end(), PrintInRange<int>(-10, 10));
  std::cout << std::endl;

  std::cout << "b) Wypisz co k-tą wartość zaczynając od pozycji p-tej" << std::endl;
  std::for_each(v.begin(), v.end(), PrintEveryNth<double>(1, 0));
  std::cout << std::endl;
  std::for_each(l.begin(), l.end(), PrintEveryNth<std::string>(2, 1));
  std::cout << std::endl;
  std::for_each(s.begin(), s.end(), PrintEveryNth<int>(3, 3));
  std::cout << std::endl;

  std::cout << "c) Wyznacz średnią arytmetyczną (dotyczy kolekcji z liczbami)" << std::endl;
  std::cout << std::accumulate(v.begin(), v.end(), 0.0, Average<double>()) << std::endl;
  std::cout << std::accumulate(s.begin(), s.end(), 0, Average<int>()) << std::endl;

  auto vMinMax = MinMax<std::vector<double>, double>(v);
  auto lMinMax = MinMax<std::list<std::string>, std::string>(l);
  auto sMinMax = MinMax<std::set<int>, int>(s);

  std::cout << "d) Wyznacz element minimalny i maksymalny (zwróć parę iteratorów)" << std::endl;
  std::cout << *vMinMax.first << " " << *vMinMax.second << std::endl;
  std::cout << *lMinMax.first << " " << *lMinMax.second << std::endl;
  std::cout << *sMinMax.first << " " << *sMinMax.second << std::endl;

  std::cout << "e) Wyznacz sumę (konkatenację dla łańcuchów znakowych) wszystkich elementów" << std::endl;
  std::cout << std::accumulate(v.begin(), v.end(), 0.0, Concatenate<double>()) << std::endl;
  std::cout << std::accumulate(l.begin(), l.end(), std::string(), Concatenate<std::string>()) << std::endl;
  std::cout << std::accumulate(s.begin(), s.end(), 0, Concatenate<int>()) << std::endl;

  return 0;
}
