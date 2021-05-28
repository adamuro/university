from queue import PriorityQueue
from itertools import permutations

warehouse = []

with open("zad_input.txt", "r") as f:
  for line in f:
    warehouse.append(line.strip())

y = len(warehouse)
x = len(warehouse[0])

moves = "RDLU"

position = (0, 0)
boxes = []
goals = []

# Preprocessing
for i in range(y):
  for j in range(x):
    if warehouse[i][j] == "K":
      position = (i, j)
    if warehouse[i][j] == "B":
      boxes.append((i, j))
    if warehouse[i][j] == "G":
      goals.append((i, j))
    if warehouse[i][j] == "*":
      boxes.append((i, j))
      goals.append((i, j))
    if warehouse[i][j] == "+":
      position = (i, j)
      goals.append((i, j))

# Zmiana stanu po wykonaniu ruchu
def evaluate_move(state, move):
  state_moves = state[0]
  state_position = state[1]
  state_boxes = state[2]
  
  dx = 0
  dy = 0
  if move == "U":
    dy = -1
  if move == "D":
    dy = 1
  if move == "L":
    dx = -1
  if move == "R":
    dx = 1
  
  new_position = (state_position[0] + dy, state_position[1] + dx)
  if warehouse[new_position[0]][new_position[1]] == "W":
    return False
  
  if new_position in state_boxes:
    new_box_position = (state_position[0] + 2 * dy, state_position[1] + 2 * dx)
    if warehouse[new_box_position[0]][new_box_position[1]] == "W" or new_box_position in state_boxes:
      return False

    new_boxes = [new_box_position if box == new_position else box for box in state_boxes]
    return (state_moves + move, new_position, new_boxes)

  return (state_moves + move, new_position, state_boxes)

def job_done(boxes):
  for box in boxes:
    if box not in goals:
      return False
  return True

# Minimalna odległość permutacji skrzyń od punktów docelowych
def heuristics(boxes):
  min_distance = x * y * len(boxes)
  for boxes_perm in permutations(boxes):
    distance = 0
    for i in range(len(goals)):
      distance += abs(goals[i][0] - boxes_perm[i][0]) + abs(goals[i][1] - boxes_perm[i][1])
    min_distance = min(min_distance, distance)
  
  return min_distance

visited = set()
queue = PriorityQueue()

queue.put((heuristics(boxes), ("", position, tuple(sorted(boxes)))))

while not queue.empty():
  state = queue.get()[1]
  state_moves = state[0]
  state_position = state[1]
  state_boxes = state[2]

  if job_done(state_boxes):
    with open("zad_output.txt", "w") as out:
      out.write(state_moves)
      exit(0)

  for move in moves:
    new_state = evaluate_move(state, move)
    if new_state:
      new_state_moves = new_state[0]
      new_state_position = new_state[1]
      new_state_boxes = new_state[2]
      sorted_boxes = tuple(sorted(new_state_boxes))
      if (new_state_position, sorted_boxes) not in visited:
        queue.put((len(state_moves) + heuristics(new_state_boxes), new_state))
        visited.add((new_state_position, sorted_boxes))