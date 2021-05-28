import random

HANDS_N = 10000

STRAIGHT_FLUSH = 8
FOUR = 7
FULL = 6
FLUSH = 5
STRAIGHT = 4
THREE = 3
TWO_PAIRS = 2
PAIR = 1
HIGHCARD = 0

talia_figuranta = [
  [1, 1], [1, 2], [1, 3], [1, 4],
  [2, 1], [2, 2], [2, 3], [2, 4],
  [3, 1], [3, 2], [3, 3], [3, 4],
  [4, 1], [4, 2], [4, 3], [4, 4]
]

talia_blotkarza = [
  [1, 1], [1, 2], [1, 3], [1, 4],
  [2, 1], [2, 2], [2, 3], [2, 4],
  [3, 1], [3, 2], [3, 3], [3, 4],
  [4, 1], [4, 2], [4, 3], [4, 4],
  [5, 1], [5, 2], [5, 3], [5, 4],
  [6, 1], [6, 2], [6, 3], [6, 4],
  [7, 1], [7, 2], [7, 3], [7, 4],
  [8, 1], [8, 2], [8, 3], [8, 4],
  [9, 1], [9, 2], [9, 3], [9, 4]
]

def card_val(card):
  return card[0]

def card_colour(card):
  return card[1]

def get_values(cards):
  vals = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0, 9: 0}
  for card in cards:
    vals[card_val(card)] += 1
  return vals.values()

def straight(cards):
  cards.sort(key=card_val)
  for i in range(4):
    if card_val(cards[i]) + 1 != card_val(cards[i + 1]):
      return False
  return True

def flush(cards):
  for i in range(4):
    if card_colour(cards[i]) != card_colour(cards[i + 1]):
      return False
  return True

def four(cards):
  values = get_values(cards)
  return 4 in values

def three(cards):
  values = get_values(cards)
  return 3 in values

def full(cards):
  values = get_values(cards)
  return 3 in values and 2 in values

def two_pairs(cards):
  values = get_values(cards)
  pairs = 0
  for value in values:
    if value == 2:
      pairs += 1
  return pairs == 2

def pair(cards):
  values = get_values(cards)
  return 2 in values

def hand(cards):
  if straight(cards) and flush(cards):
    return STRAIGHT_FLUSH
  if four(cards):
    return FOUR
  if full(cards):
    return FULL
  if flush(cards):
    return FLUSH
  if straight(cards):
    return STRAIGHT
  if three(cards):
    return THREE
  if two_pairs(cards):
    return TWO_PAIRS
  if pair(cards):
    return PAIR
  return HIGHCARD

def get_figurant_hands():
  hands = [0] * 9
  for m in range(12):
    for a in range(m + 1, 13):
      for s in range (a + 1, 14):
        for n in range(s + 1, 15):
          for o in range(n + 1, 16):
            cards = [talia_figuranta[m], talia_figuranta[a], talia_figuranta[s], talia_figuranta[n], talia_figuranta[o]]
            hands[hand(cards)] += 1
  return hands

def get_blotkarz_hands():
  hands = [0] * 9
  for i in range(32):
    for j in range(i + 1, 33):
      for k in range (j + 1, 34):
        for l in range(k + 1, 35):
          for o in range(l + 1, 36):
            cards = [talia_blotkarza[i], talia_blotkarza[j], talia_blotkarza[k], talia_blotkarza[l], talia_blotkarza[o]]
            hands[hand(cards)] += 1
  return hands

blotkarz_hands = get_blotkarz_hands()
figurant_hands = get_figurant_hands()
blotkarz_wins = 0

for i in range(1, 9):
  for j in range(i):
    blotkarz_wins += blotkarz_hands[i] * figurant_hands[j]

blotkarz_chance = blotkarz_wins / 1646701056
figurant_chance = 1 - blotkarz_chance

print("Prawdopodobieństwo wygranej blotkarza: " + str(blotkarz_chance))
print("Prawdopodobieństwo wygranej figuranta: " + str(figurant_chance))


# for i in range(HANDS_N):
#   figurant = random.sample(talia_figuranta, 5)
#   blotkarz = random.sample(talia_blotkarza, 5)
#   figurant_hand = hand(figurant)
#   blotkarz_hand = hand(blotkarz)
#   print("Figurant: " + str(figurant) + " - " + str(figurant_hand))
#   print("Blotkarz: " + str(blotkarz) + " - " + str(blotkarz_hand))
#   if hand(figurant) >= hand(blotkarz):
#     figurant_wins += 1
#     print("Figurant wygrywa")
#   else:
#     blotkarz_wins += 1
#     print("Blotkarz wygrywa")

# print("Figurant: " + str(figurant_wins))
# print("Blotkarz: " + str(blotkarz_wins))