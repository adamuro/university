#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iomanip>

double average(std::vector<double> v) {
  return std::accumulate(v.begin(), v.end(), 0.0) / static_cast<double>(v.size());
}

double standardDeviation(std::vector<double> v) {
  double avg = average(v);
  double deviationSum = std::accumulate(v.begin(), v.end(), 0.0, [avg](const double sum, const double n) {
    return sum + (n - avg) * (n - avg);
  });

  return sqrt(deviationSum / v.size());
}


int main(int argc, char const *argv[]) {
  std::vector<double> v;

  std::istream_iterator<double> isit(std::cin);
  std::istream_iterator<double> eos;

  std::for_each(isit, eos, [&](const double n) {
    v.push_back(n);
  });

  std::cout << std::setprecision(3) << std::fixed;
  std::cout << "Średnia: " << average(v) << std::endl;
  std::cout << "Odchylenie standardowe: " << standardDeviation(v) << std::endl;

  return 0;
}
