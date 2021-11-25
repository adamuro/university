class Wyrazenie:
  def __init__(self, w1, w2):
    self.w1 = w1
    self.w2 = w2

  def __add__(self, wyrazenie):
    return Dodaj(self, wyrazenie)

  def __mul__(self, wyrazenie):
    return Razy(self, wyrazenie)

  # Rozszerzenie zadania B
  @staticmethod
  def uprosc(w):
    if isinstance(w, Dodaj) or isinstance(w, Minus) or isinstance(w, Razy) or isinstance(w, Podziel):
      if isinstance(w.w1, Stala) and isinstance(w.w2, Stala):
        return Stala(w.oblicz(None))
    if isinstance(w, Razy):
      if isinstance(w.w1, Stala) and w.w1.wartosc == 0:
        return Stala(0)
      if isinstance(w.w2, Stala) and w.w2.wartosc == 0:
        return Stala(0)
    if not isinstance(w, Zmienna) and not isinstance(w, Stala):
      Wyrazenie.uprosc(w.w1)
      Wyrazenie.uprosc(w.w2)


class Dodaj(Wyrazenie):
  def __init__(self, w1, w2):
    super().__init__(w1, w2)

  def __str__(self):
    return '(' + str(self.w1) + ' + ' + str(self.w2) + ')'
  
  def oblicz(self, zmienne):
    return self.w1.oblicz(zmienne) + self.w2.oblicz(zmienne)

class Minus(Wyrazenie):
  def __init__(self, w1, w2):
    super().__init__(w1, w2)

  def __str__(self):
    return '(' + str(self.w1) + ' - ' + str(self.w2) + ')'
  
  def oblicz(self, zmienne):
    return self.w1.oblicz(zmienne) - self.w2.oblicz(zmienne)

class Razy(Wyrazenie):
  def __init__(self, w1, w2):
    super().__init__(w1, w2)

  def __str__(self):
    return '(' + str(self.w1) + ' * ' + str(self.w2) + ')'
  
  def oblicz(self, zmienne):
    return self.w1.oblicz(zmienne) * self.w2.oblicz(zmienne)

class Podziel(Wyrazenie):
  def __init__(self, w1, w2):
    super().__init__(w1, w2)

  def __str__(self):
    return '(' + str(self.w1) + ' / ' + str(self.w2) + ')'
  
  def oblicz(self, zmienne):
    wartoscW2 = self.w2.oblicz(zmienne)
    if wartoscW2 == 0:
      raise ZeroDivisionError
    return self.w1.oblicz(zmienne) / wartoscW2

class Zmienna(Wyrazenie):
  def __init__(self, nazwa):
    if type(nazwa) is not str:
      raise VariableNameTypeError
    self.nazwa = nazwa

  def __str__(self):
    return self.nazwa
  
  def oblicz(self, zmienne):
    if self.nazwa not in zmienne:
      raise MissingVariableValue
    return zmienne[self.nazwa]

class Stala(Wyrazenie):
  def __init__(self, wartosc):
    if (type(wartosc) is not int) and (type(wartosc) is not float):
      raise VariableNameTypeError
    self.wartosc = wartosc

  def __str__(self):
    return str(self.wartosc)
  
  def oblicz(self, zmienne):
    return self.wartosc

class VariableNameTypeError(Exception):
  pass
class ConstantValueTypeError(Exception):
  pass
class MissingVariableValue(Exception):
  pass

w1 = Razy(Dodaj(Zmienna('x'), Stala(2)), Zmienna('y'))
w2 = Minus(Zmienna('y'), Podziel(Zmienna('x'), Stala(2)))
print(w1)
print(w1.oblicz({ 'x': 1, 'y': 2}))
print(w1 + w2)
print(w1 * w2)

w3 = Wyrazenie.uprosc(Dodaj(Stala(1), Stala(3)))
w4 = Wyrazenie.uprosc(w1 * Stala(0))

print(w3)
print(w4)