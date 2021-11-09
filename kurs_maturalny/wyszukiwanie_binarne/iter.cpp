#include <iostream>
#include <cmath>

using namespace std;

/* Szukamy x w tablicy arr */

int binarySearch(int arr[], int l, int r, int x) {
  while (l < r) {
    int s = ceil((l + r) / 2);
    // if (arr[s] == x) {
    //   return s;
    // }

    if (arr[s] > x) {
      r = s - 1;
    } else {
      l = s;
    }
  }

  return l;
}

int main(int argc, char const *argv[]) {
  int arr[10] {1, 3, 4, 7, 8, 10, 14, 16, 17, 20};

  cout << binarySearch(arr, 0, 9, 1) << endl;
  cout << binarySearch(arr, 0, 9, 8) << endl;
  cout << binarySearch(arr, 0, 9, 17) << endl;
  cout << binarySearch(arr, 0, 9, 20) << endl;
  cout << binarySearch(arr, 0, 9, 10) << endl;
  cout << binarySearch(arr, 0, 9, 5) << endl;
  cout << binarySearch(arr, 0, 9, 24) << endl;
  
  return 0;
}
