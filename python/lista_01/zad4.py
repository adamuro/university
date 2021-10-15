import random

ORZEL = 0
RESZKA = 1

def flip():
  return ORZEL if random.random() > 0.5 else RESZKA

def flip_until(number, coin_side):
  flips = 0
  in_a_row = 0

  while in_a_row < number:
    flips += 1
    if flip() == coin_side:
      in_a_row += 1
    else:
      in_a_row = 0

  return flips

def experiment(number, in_a_row, coin_side = ORZEL):
  flips = 0

  for i in range(number):
    flips += flip_until(in_a_row, coin_side)

  average = flips // number
  print("Średnia: " + str(average))

experiment(30000, 3)