def bubbleSort(arr, size):
  for i in range(1, size):
    swapped = False
    for j in range(size - i):
      if arr[j] > arr[j + 1]:
        arr[j], arr[j + 1] = arr[j + 1], arr[j]
        swapped = True
    if not swapped:
      break

N = 10
arr = [4, 6, 2, 3, 9, 1, 5, 7, 8, 0]

bubbleSort(arr, N)
print(arr)