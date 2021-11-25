#include <iostream>

using namespace std;

int binarySearch(int arr[], int l, int r, int x) {
  if (l > r) {
    return -1;
  }

  int s = (l + r) / 2;

  if (arr[s] == x) {
    return s;
  }

  if (arr[s] > x) {
    return binarySearch(arr, l, s - 1, x);
  }

  return binarySearch(arr, s + 1, r, x);
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
