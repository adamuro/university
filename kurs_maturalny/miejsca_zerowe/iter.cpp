#include <iostream>
#include <cmath>

using namespace std;

double EPSILON = 0.00001;

double f(double x) {
  return sin(x) + pow(x, 2) - pow(x, 3) - 0.5;
}

double zero(double l, double r) {
  double s = (l + r) / 2.0;

  while(abs(f(s)) > EPSILON) {
    if (f(l) * f(s) < 0) {
      r = s;
    } else {
      l = s;
    }

    s = (l + r) / 2;
  }

  return s;
}

int main(int argc, char const *argv[]) {
  cout << zero(0, 1) << endl;

  return 0;
}
