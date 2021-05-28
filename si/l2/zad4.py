from queue import Queue
import itertools

labirynth = []

with open("zad_input.txt", "r") as f:
  for line in f:
    labirynth.append(line.strip())

y = len(labirynth)
x = len(labirynth[0])

starts = set()
moves = "RDLU"
starting_path = ""

# Preprocessing labiryntu: zapamiętywanie punktów docelowych i startowych
for i in range(y):
  for j in range(x):
    if labirynth[i][j] == "S":
      starts.add((i, j))
      labirynth[i] = labirynth[i][:j] + " " + labirynth[i][j + 1:]
    if labirynth[i][j] == "B":
      starts.add((i, j))
      labirynth[i] = labirynth[i][:j] + "G" + labirynth[i][j + 1:]

def evaluate_move(position, move):
  if(move == "U"):
    return (position[0] - 1, position[1])
  elif(move == "D"):
    return (position[0] + 1, position[1])
  elif(move == "L"):
    return (position[0], position[1] - 1)
  return (position[0], position[1] + 1)

def get_move_positions(starts, move):
  positions = set()
  for start in starts:
    position = evaluate_move(start, move)   
    if labirynth[position[0]][position[1]] != "#":
      positions.add(position)
    else:
      positions.add(start)
  return positions

def mission_complete(positions):
  for position in positions:
    if labirynth[position[0]][position[1]] != "G":
      return False
  return True

# Redukcja liczby możliwych pozycji startowych
starting_sequences = list(itertools.permutations(moves))
best_sequence_path = ""
best_sequence_starts_num = x * y
best_sequence_starts = set()

for sequence in starting_sequences:
  sequence_starts = starts
  sequence_path = ""
  for move in sequence:
    for i in range(12):
      sequence_path += move
      sequence_starts = get_move_positions(sequence_starts, move)
  if len(sequence_starts) < best_sequence_starts_num:
    best_sequence_path = sequence_path
    best_sequence_starts_num = len(sequence_starts)
    best_sequence_starts = sequence_starts

starts = best_sequence_starts
starting_path = best_sequence_path

visited_states = set()
queue = Queue()
queue.put((starts, ""))

# BFS
while not queue.empty():
  state = queue.get()
  state_starts = state[0]
  state_path = state[1]

  if mission_complete(state_starts):
    # for start in state_starts:
    #   print(start)
    with open("zad_output.txt", "w") as out:
      out.write(starting_path + state_path)
      exit(0)
  
  for move in moves:
    positions = tuple(get_move_positions(state_starts, move))
    # print("----------")
    # print(move)
    # print(state_starts)
    # print(positions)
    if positions not in visited_states:
      if(len(positions) < len(state_starts)):
        queue = Queue()
        visited_states.clear()
        queue.put((positions, state_path + move))
        visited_states.add(positions)
        break
      queue.put((positions, state_path + move))
      visited_states.add(positions)
