#include <iostream>

using namespace std;

/* Obliczamy a^n */

int fastExp(int a, int n) {
  if (n == 0) {
    return 1;
  }

  if (n % 2 == 1) {
    return fastExp(a * a, n / 2) * a;
  }

  return fastExp(a * a, n / 2);
}

int main(int argc, char const *argv[]) {
  cout << fastExp(0, 4) << endl;
  cout << fastExp(2, 0) << endl;
  cout << fastExp(2, 1) << endl;
  cout << fastExp(2, 3) << endl;
  cout << fastExp(2, 4) << endl;
  cout << fastExp(2, 5) << endl;
  cout << fastExp(1, 5) << endl;
  cout << fastExp(3, 3) << endl;
  cout << fastExp(4, 4) << endl;
  return 0;
}

