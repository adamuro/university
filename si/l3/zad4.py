def var(i, j):
  return 'B_%d_%d' % (i, j)

def domains(variables):
  for var in variables:
    writeln(var + ' in 0..1,')

def horizontal_sums(rows, C):
  for i, row in enumerate(rows):
    row_variables = [var(i, j) for j in range(C)]
    writeln('sum([' + ', '.join(row_variables) + '], #=, ' + str(row) + '),')

def vertical_sums(cols, R):
  for j, col, in enumerate(cols):
    col_variables = [var(i, j) for i in range(R)]
    writeln('sum([' + ', '.join(col_variables) + '], #=, ' + str(col) + '),')

# Nie może wystąpić poniższy układ
# 0 1 0
def horizontal_points(R, C):
  for i in range(R):
    writeln(var(i, 0) + ' #= 1 #==> ' + var(i, 1) + ' #= 1,')
    writeln(var(i, C - 1) + ' #= 1 #==> ' + var(i, C - 2) + ' #= 1,')
    for j in range(C - 2):
      left = var(i, j)
      mid = var(i, j + 1)
      right = var(i, j + 2)
      
      writeln(mid + ' #= 1 #==> ' + left + ' + ' + right + ' #> 0,')

# Nie może wystąpić poniższy układ
# 0
# 1
# 0
def vertical_points(R, C):
  for j in range(C):
    writeln(var(0, j) + ' #= 1 #==> ' + var(1, j) + ' #= 1,')
    writeln(var(R - 1, j) + ' #= 1 #==> ' + var(R - 2, j) + ' #= 1,')
    for i in range(R - 2):
      left = var(i, j)
      mid = var(i + 1, j)
      right = var(i + 2, j)
      
      writeln(mid + ' #= 1 #==> ' + left + ' + ' + right + ' #> 0,')

# Nie mogą wystąpić poniższe układy
# 1 0 | 0 1 | 1 0 | 0 1 | 1 1 | 1 1
# 0 1 | 1 0 | 1 1 | 1 1 | 0 1 | 1 0
def rectangles(R, C):
  for i in range(R - 1):
    for j in range(C - 1):
      top_left = var(i, j)
      bot_left = var(i + 1, j)
      top_right = var(i, j + 1)
      bot_right = var(i + 1, j + 1)

      writeln(top_left + ' + ' + bot_right + ' #= 2 #<==> ' + top_right + ' + ' + bot_left + ' #= 2,')
  
def assigments(triples):
  for x, y, val in triples:
    writeln(var(x, y) + ' #= ' + str(val) + ',')  

def storms(rows, cols, triples):
  writeln(':- use_module(library(clpfd)).')
  
  R = len(rows)
  C = len(cols)
  
  variables = [ var(i,j) for i in range(R) for j in range(C)]

  writeln('solve([' + ', '.join(variables) + ']) :- ')
  
  writeln('')
  domains(variables)
  writeln('')
  horizontal_sums(rows, C)
  writeln('')
  vertical_sums(cols, R)
  writeln('')
  horizontal_points(R, C)
  writeln('')
  vertical_points(R, C)
  writeln('')
  rectangles(R, C)
  writeln('')
  assigments(triples)
  writeln('')
  
  writeln('')
  writeln('    labeling([ff], [' +  ', '.join(variables) + ']).' )
  writeln('')
  writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")

def writeln(s):
  output.write(s + '\n')

txt = open('zad_input.txt').readlines()
output = open('zad_output.txt', 'w')

rows = list(map(int, txt[0].split()))
cols = list(map(int, txt[1].split()))
triples = []

for i in range(2, len(txt)):
  if txt[i].strip():
    triples.append(list(map(int, txt[i].split())))

storms(rows, cols, triples)            
        

