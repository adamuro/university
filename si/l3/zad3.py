import sys

def V(i,j):
    return 'V%d_%d' % (i,j)
    
def domains(Vs):
    return [ q + ' in 1..9' for q in Vs ]
    
def all_different(Qs):
    return 'all_distinct([' + ', '.join(Qs) + '])'
    
def get_column(j):
    return [V(i,j) for i in range(9)] 
            
def get_raw(i):
    return [V(i,j) for j in range(9)] 
                        
def horizontal():   
    return [ all_different(get_raw(i)) for i in range(9)]

def vertical():
    return [all_different(get_column(j)) for j in range(9)]

# Dodane
def squares():
  return [all_different(get_square(i, j)) for i in [0, 3, 6] for j in [0, 3, 6]]

def print_constraints(Cs, indent, d):
    position = indent
    print (indent * ' ', end='', file=output)
    for c in Cs:
        print (c + ',', end=' ', file=output)
        position += len(c)
        if position > d:
            position = indent
            print (file=output)
            print (indent * ' ', end='', file=output)

def get_square(x, y):
    return [V(i, j) for i in range(x, x + 3) for j in range(y, y + 3)]
      
def sudoku(assigments):
    variables = [ V(i,j) for i in range(9) for j in range(9)]
    
    print (':- use_module(library(clpfd)).', file=output)
    print ('solve([' + ', '.join(variables) + ']) :- ', file=output)
    
    
    cs = domains(variables) + vertical() + horizontal() + squares()
    for i,j,val in assigments:
        cs.append( '%s #= %d' % (V(i,j), val) )
    
    print_constraints(cs, 4, 70),
    print (file=output)
    print ('    labeling([ff], [' +  ', '.join(variables) + ']).' , file=output)
    print (file=output)
    print (':- solve(X), write(X), nl.', file=output)       

if __name__ == "__main__":
    txt = open('zad_input.txt').readlines()
    output = open('zad_output.txt', 'w')
    raw = 0
    triples = []
    
    for x in txt:
        x = x.strip()
        if len(x) == 9:
            for i in range(9):
                if x[i] != '.':
                    triples.append( (raw,i,int(x[i])) ) 
        raw += 1          
    sudoku(triples)
    
"""
89.356.1.
3...1.49.
....2985.
9.7.6432.
.........
.6389.1.4
.3298....
.78.4....
.5.637.48

53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79

3.......1
4..386...
.....1.4.
6.924..3.
..3......
......719
........6
2.7...3..
"""    
