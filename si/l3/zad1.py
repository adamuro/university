from queue import Queue

with open("./zad_input.txt", "r") as f:
  lines = f.readlines()

# Preprocessing
y, x = map(int, lines[0].strip().split())

drawing = []
row_patterns = []
col_patterns = []
row_possible_fits = []
col_possible_fits = []

def get_possible_blocks_fits(length, start, pattern, i):
  if i == len(pattern):
    return [[0] * (length - start + 1)]

  if start + pattern[i] > length:
    return False
  
  current_fits = []
  original_start = start

  while pattern[i] + start <= length:
    next_fits = get_possible_blocks_fits(length, start + pattern[i] + 1, pattern, i + 1)
    if not next_fits:
      return current_fits
    
    prefix = [0] * (start - original_start)
    block = [1] * pattern[i]
    separator = [] if i == len(pattern) - 1 else [0]

    for next_fit in next_fits:
      current_fits.append(prefix + block + separator + next_fit)
    start += 1

  return current_fits

for i in range(y):
  drawing.append([0] * x)
for i in range(y):
  row_patterns.append(list(map(int, lines[i + 1].strip().split())))
  row_possible_fits.append(get_possible_blocks_fits(x, 0, row_patterns[i], 0))
for i in range(x):
  col_patterns.append(list(map(int, lines[i + y + 1].strip().split())))
  col_possible_fits.append(get_possible_blocks_fits(y, 0, col_patterns[i], 0))


# Wnioskowanie
def remove_impossible_rows(x, y, val):
  row_possible_fits[y] = [row_fit for row_fit in row_possible_fits[y] if row_fit[x] == val]
def remove_impossible_cols(x, y, val):
  col_possible_fits[x] = [col_fit for col_fit in col_possible_fits[x] if col_fit[y] == val]

def try_fix(x, y):
  val = row_possible_fits[y][0][x]
  if all(row_possible_fits[y][i][x] == val for i in range(len(row_possible_fits[y]))):
    drawing[y][x] = val
    remove_impossible_cols(x, y, val)
    return
  
  val = col_possible_fits[x][0][y]
  if all(col_possible_fits[x][i][y] == val for i in range(len(col_possible_fits[x]))):
    drawing[y][x] = val
    remove_impossible_rows(x, y, val)
    return

  open_points.put((x, y))

open_points = Queue()
for i in range(x):
  for j in range(y):
    open_points.put((i, j))

while not open_points.empty():
  x, y = open_points.get()
  try_fix(x, y)

with open("zad_output.txt", "w") as out:
  for row in drawing:
    for c in row:
      out.write('#' if c == 1 else '.')
    out.write('\n')
