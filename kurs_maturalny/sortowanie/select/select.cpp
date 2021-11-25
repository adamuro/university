#include <iostream>

using namespace std;

void selectSort(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    int minIndex = i;
    for (int j = i; j < size; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }

    swap(arr[i], arr[minIndex]);
  }
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) cout << arr[i] << " ";
  cout << endl;
}

int main(int argc, char const *argv[]) {
  int N = 10;
  int arr[N] = {4, 6, 2, 3, 9, 1, 5, 7, 8, 0};

  selectSort(arr, N);
  printArray(arr, N);
}