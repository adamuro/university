from math import floor

def fastExp(a, n):
  if n == 0:
    return 1

  result = 1
  while n > 0:
    if n % 2 == 1:
      result *= a

    a *= a
    n = floor(n / 2)
  
  return result

print(fastExp(0, 4))
print(fastExp(2, 0))
print(fastExp(2, 1))
print(fastExp(2, 3))
print(fastExp(2, 4))
print(fastExp(2, 5))
print(fastExp(1, 5))
print(fastExp(3, 3))
print(fastExp(4, 4))