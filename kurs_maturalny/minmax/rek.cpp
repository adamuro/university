#include <iostream>

using namespace std;

/* Szukamy najmniejszego i największego elementu w tablicy arr */

/* Pierwszy element pary będzie min, drugi max */
pair<int, int> minMax(int arr[], int l, int r) {
  int min, max;

  if (l == r) {
    min = max = arr[l];
  } else if (l == r - 1) {
    if (arr[l] > arr[r]) {
      min = arr[r];
      max = arr[l];
    } else {
      min = arr[l];
      max = arr[r];
    }
  } else {
    int m = (l + r) / 2;
    pair<int, int> lMinMax = minMax(arr, l, m);
    pair<int, int> rMinMax = minMax(arr, m + 1, r);

    if (lMinMax.first < rMinMax.first) {
      min = lMinMax.first;
    } else {
      min = rMinMax.first;
    }
    
    if (lMinMax.second > rMinMax.second) {
      max = lMinMax.second;
    } else {
      max = rMinMax.second;
    }
  }
  
  return make_pair(min, max);
}

int main(int argc, char const *argv[]) {
  int arr[10] = {2, 56, 3, 5, -32, 11, 43, -15, 0, -1};

  pair<int, int> arrMinMax = minMax(arr, 0, 9);
  cout << arrMinMax.first << " " << arrMinMax.second << endl;

  return 0;
}
