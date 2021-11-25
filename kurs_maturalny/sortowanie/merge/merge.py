from math import floor

def merge(arr, l, m, r):
  lSize = m - l + 1
  rSize = r - m

  # lArr = [arr[i] for i in range(l, l + lSize)]
  # rArr = [arr[i] for i in range(m + 1, m + 1 + rSize)]
  lArr = []
  rArr = []

  for i in range(lSize):
    lArr.append(arr[l + i])

  for i in range(rSize):
    rArr.append(arr[m + 1 + i])

  lIndex = 0
  rIndex = 0

  for i in range(lSize + rSize):
    if rIndex >= rSize or (lIndex < lSize and lArr[lIndex] < rArr[rIndex]):
      arr[l + i] = lArr[lIndex]
      lIndex += 1
    else:
      arr[l + i] = rArr[rIndex]
      rIndex += 1

def mergeSort(arr, l, r):
  if l >= r:
    return
  
  m = floor((l + r) / 2)

  mergeSort(arr, l, m)
  mergeSort(arr, m + 1, r)
  merge(arr, l, m, r)

N = 10
arr = [4, 6, 2, 3, 9, 1, 5, 7, 8, 0]

mergeSort(arr, 0, N - 1)
print(arr)
