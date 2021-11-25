from math import floor

def pierwiastek(x):
  l = 1
  r = x

  while l < r:
    s = floor((l + r) / 2)
    if s * s < x:
      l = s + 1
    else:
      r = s
  
  return l

print(pierwiastek(4))
print(pierwiastek(5))
print(pierwiastek(12))
print(pierwiastek(22))
print(pierwiastek(16))