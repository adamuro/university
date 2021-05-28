#!/usr/bin/python

def opt_dist(l, d):
  ones = []
  for i, val in enumerate(l):
    if val == 1:
      ones.append(i) 
  
  # d=0, d=1, n=0, n=1
  if d <= 1 or len(ones) <= 1:
    return abs(len(ones) - d)
  # odległość między skrajnymi jedynkami mniejsza od d
  if(ones[len(ones) - 1] - ones[0] < d):
    return d - len(ones)

  min_changes = len(l)
  for left_idx in range(len(ones) - 1):
    for right_idx in range(left_idx + 1, len(ones)):
      left = ones[left_idx]
      right = ones[right_idx]
      idx_dif = right_idx - left_idx
      dist = right - left # odległość między jedynkami
      if dist >= d:
        continue
      mid = dist - idx_dif # liczba zer (do zmiany) między jedynkami
      add = d - dist - 1 # ilość jedynek do dodania dookoła wybranych
      remove = len(ones) - 1 - idx_dif # ilość jedynek do usunięcia dookoła wybranych 
      changes = mid + add + remove # łączna liczba zmian bitowych
      if changes < min_changes:
        min_changes = changes
        if min_changes == 0:
          return min_changes
  
  brut_changes = len(ones) - 1 + d - 1
  if brut_changes < min_changes:
    return brut_changes
  return min_changes

with open("./zad4_input.txt", "r") as f:
    with open("./zad4_output.txt", "w") as out:
        for line in f:
          args = line.split()
          l = list(map(int, list(args[0])))
          d = int(args[1])
          result = opt_dist(l, d)
          out.write(str(result) + '\n')