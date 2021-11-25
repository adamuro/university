from math import floor, ceil

def binarySearch(list, l, r, x):
  while l < r:
    s = ceil((l + r) / 2)
    # if list[s] == x:
    #   return s

    if list[s] > x:
      r = s - 1
    else:
      l = s
  
  return l

list = [1, 3, 4, 7, 8, 10, 14, 16, 17, 20]

print(binarySearch(list, 0, 9, 1))
print(binarySearch(list, 0, 9, 8))
print(binarySearch(list, 0, 9, 17))
print(binarySearch(list, 0, 9, 20))
print(binarySearch(list, 0, 9, 10))
print(binarySearch(list, 0, 9, 5))
print(binarySearch(list, 0, 9, 24))