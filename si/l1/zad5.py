import random

with open("./zad5_input.txt", "r") as f:
  lines = f.readlines()

x = int(lines[0][0])
y = int(lines[0][2])

row_d = []
col_d = []
rows = []
cols = []

for i in range(x):
  row_d.append(int(lines[i + 1]))
  rows.append([0] * y)
for i in range(y):
  col_d.append(int(lines[i + x + 1]))
  cols.append([0] * x)

def opt_dist(l, d):
  min_changes = len(l)
  all_ones= l.count(1)
  for i in range(len(l) - d + 1):
    ones_in_range = 0
    for j in range(i, i + d):
      if(l[j] == 1):
        ones_in_range += 1
        min_changes = min(min_changes, all_ones - 2 * ones_in_range + d)
  return min_changes

def get_incorrect_rows():
  incorrect_rows = []
  for i in range(x):
    if(opt_dist(rows[i], row_d[i]) > 0):
      incorrect_rows.append(i)
  return incorrect_rows

def get_incorrect_cols():
  incorrect_cols = []
  for i in range(y):
    if(opt_dist(cols[i], col_d[i]) > 0):
      incorrect_cols.append(i)
  return incorrect_cols

while get_incorrect_rows() or get_incorrect_cols():
  incorrect_rows = get_incorrect_rows()
  incorrect_cols = get_incorrect_cols()

  if (random.choice([True, False]) or not incorrect_cols) and incorrect_rows:
    row = random.choice(incorrect_rows)
    row_opt_dist = opt_dist(rows[row], row_d[row])
    best_improvement = 0
    best_improvement_col = 0

    for col in range(y):
      col_opt_dist = opt_dist(cols[col], col_d[col])
      curr_val = rows[row][col]

      rows[row][col] = int(not curr_val)
      cols[col][row] = int(not curr_val)

      new_row_opt_dist = opt_dist(rows[row], row_d[row])
      new_col_opt_dist = opt_dist(cols[col], col_d[col])
      improvement = row_opt_dist - new_row_opt_dist + col_opt_dist - new_col_opt_dist

      if improvement > best_improvement:
        best_improvement = improvement
        best_improvement_col = col
      
      rows[row][col] = int(curr_val)
      cols[col][row] = int(curr_val)

    # Mała szansa na popsucie
    if random.random() > 0.3:
      rows[row][best_improvement_col] = int(not rows[row][best_improvement_col])
      cols[best_improvement_col][row] = int(not cols[best_improvement_col][row])
    else:
      rand_col = random.randint(0, y - 1)
      rows[row][rand_col] = int(not rows[row][rand_col])
      cols[rand_col][row] = int(not cols[rand_col][row])
  else:
    col = random.choice(incorrect_cols)
    col_opt_dist = opt_dist(cols[col], col_d[col])
    best_improvement = 0
    best_improvement_row = 0

    for row in range(x):
      row_opt_dist = opt_dist(rows[row], row_d[row])
      curr_val = cols[col][row]

      cols[col][row] = int(not curr_val)
      rows[row][col] = int(not curr_val)

      new_col_opt_dist = opt_dist(cols[col], col_d[col])
      new_row_opt_dist = opt_dist(rows[row], row_d[row])
      improvement = col_opt_dist - new_col_opt_dist + row_opt_dist - new_row_opt_dist

      if improvement > best_improvement:
        best_improvement = improvement
        best_improvement_row = row

      cols[col][row] = int(curr_val)
      rows[row][col] = int(curr_val)

    # Mała szansa na popsucie
    if random.random() > 0.3:
      cols[col][best_improvement_row] = int(not cols[col][best_improvement_row])
      rows[best_improvement_row][col] = int(not rows[best_improvement_row][col])
    else:
      rand_row = random.randint(0, x - 1)
      cols[col][rand_row] = int(not cols[col][rand_row])
      rows[rand_row][col] = int(not rows[rand_row][col])


out = open("zad5_output.txt", "w")
for row in rows:
  row_str = ""
  for c in row:
    if c == 1:
      row_str += "#"
    else:
      row_str += "."
  out.write(row_str + '\n')
out.close()