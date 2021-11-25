from math import floor

def binarySearch(list, l, r, x):
  if l > r:
    return -1

  s = floor((l + r) / 2)

  if list[s] == x:
    return s
  
  if list[s] > x:
    return binarySearch(list, l, s - 1, x)

  return binarySearch(list, s + 1, r, x)

list = [1, 3, 4, 7, 8, 10, 14, 16, 17, 20]

print(binarySearch(list, 0, 9, 1))
print(binarySearch(list, 0, 9, 8))
print(binarySearch(list, 0, 9, 17))
print(binarySearch(list, 0, 9, 20))
print(binarySearch(list, 0, 9, 10))
print(binarySearch(list, 0, 9, 5))
print(binarySearch(list, 0, 9, 24))