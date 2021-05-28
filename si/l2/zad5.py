from queue import PriorityQueue, Queue

labirynth = []

with open("zad_input.txt", "r") as f:
  for line in f:
    labirynth.append(line.strip())

y = len(labirynth)
x = len(labirynth[0])

starts = set()
moves = "RDLU"
dest_positions = []
dest_distances = {}

# Preprocessing labiryntu: zapamiętywanie punktów docelowych i startowych
for i in range(y):
  for j in range(x):
    dest_distances[(i, j)] = x * y
    if labirynth[i][j] == "S":
      starts.add((i, j))
      labirynth[i] = labirynth[i][:j] + " " + labirynth[i][j + 1:]
    elif labirynth[i][j] == "G":
      dest_positions.append((i, j))
    elif labirynth[i][j] == "B":
      starts.add((i, j))
      dest_positions.append((i, j))
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

# === HEURYSTYKA === #

# Odległość bruklińska
# def calculate_dest(dest_pos, position):
#   return abs(dest_pos[0] - position[0]) + abs(dest_pos[1] - position[1])
# for i in range(y):
#   for j in range(x):
#     for dest_pos in dest_positions:
#       dest_distances[(i, j)] = min(dest_distances[(i, j)], calculate_dest(dest_pos, (i, j)))

# Odległość BFS
for dest_pos in dest_positions:
  queue = Queue()
  visited = set()
  queue.put((dest_pos, 0))
  while not queue.empty():
    state = queue.get()
    position = state[0]
    distance = state[1]
    dest_distances[position] = min(dest_distances[position], distance)
    for move in moves:
      new_position = evaluate_move(position, move)
      if labirynth[new_position[0]][new_position[1]] != "#" and new_position not in visited:
        queue.put((new_position, distance + 1))
        visited.add(new_position)

# Heurystyka optymistyczna
# def heuristics(starts):
#   longest_distance = 0
#   for start in starts:
#     longest_distance = max(longest_distance, dest_distances[start])
#   return longest_distance

# Heurystyka niedopuszczalna
def heuristics(starts):
  st_niedop = 4
  distances = sorted([dest_distances[start] for start in starts])
  total_distance = 0
  return sum(distances[-st_niedop:])

visited_states = set()
queue = PriorityQueue()
queue.put((heuristics(starts), (starts, "")))

while not queue.empty():
  state = queue.get()
  state_starts = state[1][0]
  state_path = state[1][1]

  if mission_complete(state_starts):
    # for start in state_starts:
    #   print(start)
    with open("zad_output.txt", "w") as out:
      print("Długość ścieżki: " + str(len(state_path)))
      out.write(state_path)
      exit(0)
  
  for move in moves:
    positions = tuple(get_move_positions(state_starts, move))
    # print("----------")
    # print(move)
    # print(state_starts)
    # print(positions)
    if positions not in visited_states:
      queue.put((len(state_path) + heuristics(positions) + 1, (positions, state_path + move)))
      visited_states.add(positions)