import time

def pierwsza(n):
  if n < 2:
    return False
  for i in range(2, n // 2):
    if n % i == 0:
      return False
  return True

def pierwsze_imperatywna(n):
  pierwsze = []
  for i in range(n + 1):
    if pierwsza(i):
      pierwsze.append(i)
  return pierwsze

def pierwsze_skladana(n):
  return [i for i in range(n + 1) if pierwsza(i)]

def pierwsze_funkcyjna(n):
  return list(filter(pierwsza, range(n + 1)))

start = time.time()
pierwsze_imperatywna(50000)
print(pierwsze_imperatywna(100))
print(time.time() - start)

start = time.time()
pierwsze_skladana(50000)
print(pierwsze_skladana(100))
print(time.time() - start)

start = time.time()
pierwsze_funkcyjna(50000)
print(pierwsze_funkcyjna(100))
print(time.time() - start)