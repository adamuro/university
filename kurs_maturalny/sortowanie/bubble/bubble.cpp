#include <iostream>

using namespace std;

void bubbleSort(int arr[], int size) {
  for (int i = 1; i < size; i++) {
    bool swapped = false;
    for (int j = 0; j < size - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) {
      break;
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

  bubbleSort(arr, N);
  printArray(arr, N);

  return 0;
}
