def insertSort(arr, size):
  for i in range(size):
    j = i - 1
    while j >= 0:
      if arr[j] > arr[j + 1]:
        arr[j], arr[j + 1] = arr[j + 1], arr[j]
      j -= 1

N = 10
arr = [4, 6, 2, 3, 9, 1, 5, 7, 8, 0]

insertSort(arr, N)
print(arr)