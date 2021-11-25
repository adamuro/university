def selectSort(arr, size):
  for i in range(size):
    minIndex = i
    for j in range(i, size):
      if arr[j] < arr[minIndex]:
        minIndex = j
    arr[i], arr[minIndex] = arr[minIndex], arr[i]

N = 10
arr = [4, 6, 2, 3, 9, 1, 5, 7, 8, 0]

selectSort(arr, N)
print(arr)