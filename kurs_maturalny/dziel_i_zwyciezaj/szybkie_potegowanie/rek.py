from math import floor

def fastExp(a, n):
  if n == 0:
    return 1

  if n % 2 == 1:
    return fastExp(a * a, floor(n / 2)) * a

  return fastExp(a * a, floor(n / 2))

print(fastExp(0, 4))
print(fastExp(2, 0))
print(fastExp(2, 1))
print(fastExp(2, 3))
print(fastExp(2, 4))
print(fastExp(2, 5))
print(fastExp(1, 5))
print(fastExp(3, 3))
print(fastExp(4, 4))