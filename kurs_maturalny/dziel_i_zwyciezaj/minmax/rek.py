from math import floor

def minMax(list, l, r):
  min, max = None, None

  if l == r:
    min = max = list[l]
  elif l == r - 1:
    if list[l] > list[r]:
      min = list[r]
      max = list[l]
    else:
      min = list[l]
      max = list[r]
  else:
    m = floor((l + r) / 2)
    lMinMax = minMax(list, l, m)
    rMinMax = minMax(list, m + 1, r)

    if lMinMax[0] < rMinMax[0]:
      min = lMinMax[0]
    else:
      min = rMinMax[0]
    
    if lMinMax[1] > rMinMax[1]:
      max = lMinMax[1]
    else:
      max = rMinMax[1]

  return (min, max)

list = [2, 56, 3, 5, -32, 11, 43, -15, 0, -1]
listMinMax = minMax(list, 0, 9)
print(str(listMinMax[0]) + " " + str(listMinMax[1]))