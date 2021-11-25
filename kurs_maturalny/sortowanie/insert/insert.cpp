#include <iostream>

using namespace std;

void insertSort(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    int j = i - 1;
    while (j >= 0) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
      j -= 1;
    }
  }
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) cout << arr[i] << " ";
  cout << endl;
}

int main(int argc, char const *argv[]) {
  int N = 10;
  int arr[N] = {4, 6, 2, 3, 9, 1, 5, 7, 8, 0};

  insertSort(arr, N);
  printArray(arr, N);
}
