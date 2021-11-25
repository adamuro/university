#include <iostream>

using namespace std;

void merge(int arr[], int l, int m, int r) {
  int lSize = m - l + 1;
  int rSize = r - m;

  int lArr[lSize];
  int rArr[rSize];

  for (int i = 0; i < lSize; i++) {
    lArr[i] = arr[l + i];
  }

  for (int i = 0; i < rSize; i++) {
    rArr[i] = arr[m + 1 + i];
  }

  int lIndex = 0;
  int rIndex = 0;

  for (int i = 0; i < lSize + rSize; i++) {
    if (rIndex >= rSize || (lIndex < lSize && lArr[lIndex] < rArr[rIndex])) {
      arr[l + i] = lArr[lIndex];
      lIndex += 1;
    } else {
      arr[l + i] = rArr[rIndex];
      rIndex += 1;
    }
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l >= r) {
    return;
  }

  int m = (l + r) / 2;

  mergeSort(arr, l, m);
  mergeSort(arr, m + 1, r);
  merge(arr, l, m, r);
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) cout << arr[i] << " ";
  cout << endl;
}

int main(int argc, char const *argv[]) {
  int N = 10;
  int arr[N] = {4, 6, 2, 3, 9, 1, 5, 7, 8, 0};

  mergeSort(arr, 0, N - 1);
  printArray(arr, N);
}

