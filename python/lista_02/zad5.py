def kompresja(tekst):
  wynik = []
  i = 1
  powtorzenia = 1
  while i < len(tekst):
    if tekst[i] != tekst[i - 1]:
      wynik.append((powtorzenia, tekst[i - 1]))
      powtorzenia = 1
    else:
      powtorzenia += 1
    i += 1
  wynik.append((powtorzenia, tekst[i - 1]))
  return wynik

def dekompresja(tekst_skompresowany):
  wynik = ""
  for para in tekst_skompresowany:
    znak = para[0]
    licznosc = para[1]
    wynik += znak * licznosc
  return wynik

plik = open("zad5.txt")
tekst = plik.readline()

skompresowany = kompresja(tekst)
zdekompresowany = dekompresja(skompresowany)

print("Skompresowany: " + str(skompresowany))
print("Zdekompresowany: " + str(zdekompresowany))


