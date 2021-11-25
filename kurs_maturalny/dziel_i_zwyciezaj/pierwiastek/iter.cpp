#include <iostream>

using namespace std;

int pierwiastek(int x) {
  int l = 1;
  int r = x;
  
  while (l < r) {
    int s = (l + r) / 2;
    if (s * s < x) {
      l = s + 1;
    } else {
      r = s;
    }
  }

  return l;
}

int main(int argc, char const *argv[]) {
  cout << pierwiastek(4) << endl;
  cout << pierwiastek(5) << endl;
  cout << pierwiastek(12) << endl;
  cout << pierwiastek(22) << endl;
  cout << pierwiastek(16) << endl;

  return 0;
}
