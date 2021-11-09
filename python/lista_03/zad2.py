import time

def doskonale_imperatywna(n):
  doskonale = []
  for i in range(1, n + 1):
    dzielniki = []
    for j in range(1, i):
      if i % j == 0:
        dzielniki.append(j)
    suma_dziel = 0
    for dzielnik in dzielniki:
      suma_dziel += dzielnik
    if suma_dziel == i:
      doskonale.append(i)
  return doskonale

def doskonale_skladana(n):
  dzielniki = [[j for j in range(1, i) if i % j == 0] for i in range(n + 1)]
  return [i for i in range(2, n + 1) if i == [suma for suma in [0] for dzielnik in (dzielniki[i]) for suma in [suma + dzielnik]][-1]]

def doskonale_funkcyjna(n):
  doskonala = lambda i: sum(list(filter(lambda x: i % x == 0, range(1, i)))) == i
  return list(filter(doskonala, range(1, n + 1)))

start = time.time()
print(doskonale_imperatywna(10000))
print(time.time() - start)

start = time.time()
print(doskonale_skladana(10000))
print(time.time() - start)

start = time.time()
print(doskonale_funkcyjna(10000))
print(time.time() - start)