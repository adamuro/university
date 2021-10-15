def is_palindrom(text):
  special_chars = " .,:;!?()'\""
  text = text.lower()
  for special_char in special_chars:
    text = text.replace(special_char, '')
  return text == text[::-1]

print(is_palindrom("kajak"))
print(is_palindrom("Kobyła ma mały bok"))
print(is_palindrom("To nie jest palindom"))
print(is_palindrom("Eine güldne, gute Tugend: Lüge nie"))
