from math import sin

EPSILON = 0.00001

def f(x):
  return sin(x) + x**2 - x**3 - 0.5

def zero(l, r):
  s = (l + r) / 2

  while abs(f(s)) > EPSILON:
    if f(l) * f(s) < 0:
      r = s
    else:
      l = s
    s = (l + r) / 2
  
  return s

print(zero(0, 1))