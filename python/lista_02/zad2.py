def pierwiastek(n):
  i = 0
  suma = 0
  while suma <= n:
    i += 1
    suma += (2 * i) - 1

  return i - 1

print(pierwiastek(4))
print(pierwiastek(9))
print(pierwiastek(256))
print(pierwiastek(23))