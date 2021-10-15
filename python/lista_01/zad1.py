import decimal as d

VAT = 0.23

def vat_faktura(lista):
  return sum(lista) * (1 + VAT)

def vat_paragon(lista):
  return sum([price * (1 + VAT) for price in lista])

zakupy = [0.2, 0.5, 4.59, 6, 0.56, 2.39, 0.1]
print(vat_faktura(zakupy) == vat_paragon(zakupy))

def vat_faktura_decimal(lista):
  sum = 0
  for price in lista:
    sum += price
  return sum * d.Decimal(str(1 + VAT))

def vat_paragon_decimal(lista):
  sum = 0
  for price in lista:
    sum += price * d.Decimal(str(1 + VAT))
  return sum

zakupy_decimal = [d.Decimal("0.2"), d.Decimal("0.5"), d.Decimal("4.59"), d.Decimal("6"), d.Decimal("0.1")]
print(vat_faktura_decimal(zakupy_decimal) == vat_paragon_decimal(zakupy_decimal))