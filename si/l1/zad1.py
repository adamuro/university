import numpy as np
from queue import Queue

debug = False

current_player = "white"
wk = [0, 0] # white king
wr = [0, 0] # white rook
bk = [0, 0] # black king


def draw_board(wk, wr, bk):
  for i in range(8):
    for j in range(8):
      if wk == [i, j]:
        print("WK ", end='')
      elif wr == [i, j]:
        print("WR ", end='')
      elif bk == [i, j]:
        print("BK ", end='')
      else:
        print("__ ", end='')
    print("\n", end='')
  print("")

def get_pos(square_str):
  return [ord(square_str[0]) - 97, int(square_str[1]) - 1]

def get_pos_str():
  pos_str = current_player + " "
  pos_str += chr(wk[0] + 97) + str(wk[1] + 1) + " "
  pos_str += chr(wr[0] + 97) + str(wr[1] + 1) + " "
  pos_str += chr(bk[0] + 97) + str(bk[1] + 1)
  return pos_str

def mate_in_one():
  if wk[0] == bk[0]:
    if (wk[1] == 5 and bk[1] == 7) or (wk[1] == 2 and bk[1] == 0):
      if abs(wr[0] - bk[0]) > 1:
        return True
  if wk[1] == bk[1]:
    if (wk[0] == 5 and bk[0] == 7) or (wk[0] == 2 and bk[0] == 0):
      if abs(wr[1] - bk[1]) > 1:
        return True
  return False

def get_white_king_moves():
  moves = []
  moves.append([wk[0] + 1, wk[1]])
  moves.append([wk[0] - 1, wk[1]])
  moves.append([wk[0], wk[1] - 1])
  moves.append([wk[0], wk[1] + 1])
  moves.append([wk[0] - 1, wk[1] - 1])
  moves.append([wk[0] - 1, wk[1] + 1])
  moves.append([wk[0] + 1, wk[1] - 1])
  moves.append([wk[0] + 1, wk[1] + 1])
  return moves

def get_black_king_moves():
  moves = []
  moves.append([bk[0] - 1, bk[1]])
  moves.append([bk[0] + 1, bk[1]])
  moves.append([bk[0], bk[1] - 1])
  moves.append([bk[0], bk[1] + 1])
  moves.append([bk[0] - 1, bk[1] - 1])
  moves.append([bk[0] - 1, bk[1] + 1])
  moves.append([bk[0] + 1, bk[1] - 1])
  moves.append([bk[0] + 1, bk[1] + 1])
  return moves

def get_white_rook_moves():
  moves = []
  moves.append([wr[0] + 4, wr[1]])
  moves.append([wr[0] - 4, wr[1]])
  moves.append([wr[0], wr[1] + 4])
  moves.append([wr[0], wr[1] - 4])
  return moves

def legal_position():
  if wk[0] > 7 or wk[1] > 7 or bk[0] > 7 or bk[1] > 7 or wr[0] > 7 or wr[1] > 7:
    return False
  if wk[0] < 0 or wk[1] < 0 or bk[0] < 0 or bk[1] < 0 or wr[0] < 0 or wr[1] < 0:
    return False
  if bk[0] == wr[0]:
    if not (wk[0] == bk[0] and (bk[1] > wk[1] > wr[1] or bk[1] < wk[1] < wr[1])):
      return False
  if bk[1] == wr[1]:
    if not (wk[1] == bk[1] and (bk[0] > wk[0] > wr[0] or bk[0] < wk[0] < wr[0])):
      return False
  if wk[0] == wr[0] and wk[1] == wr[1]:
    return False
  if bk[0] == wr[0] and bk[0] == wr[0]:
    return False
  if abs(wk[0] - bk[0]) <= 1 and abs(wk[1] - bk[1]) <= 1:
    return False
  return True

def draw_moves(pos_str, prev_states):
  if prev_states[pos_str] != None:
    draw_moves(prev_states[pos_str], prev_states)
  position = pos_str.split()
  wk = get_pos(position[1])
  wr = get_pos(position[2])
  bk = get_pos(position[3])
  draw_board(wk, wr, bk)

with open("./zad1_input.txt", "r") as f:
  with open("./zad1_output.txt", "w") as out:
    for line in f:
      visited_states = set()
      prev_states = {line: None}
      queue = Queue(0)
      queue.put([line, 0, False])

      while not queue.empty():
        # state = [position, move number, rook moves]
        state = queue.get()
        position = state[0].split()
        current_player = position[0]
        rook_moved = state[2]
        wk = get_pos(position[1])
        wr = get_pos(position[2])
        bk = get_pos(position[3])
        original_wk = wk

        # mate in one
        if current_player == "white" and mate_in_one():
          if debug:
            draw_moves(get_pos_str(), prev_states)
          out.write(str(state[1] + 1) + "\n")
          break
        else:
          # white to move
          if current_player == "white":
            current_player = "black"
            # move white king
            for move in get_white_king_moves():
              wk = move
              pos_str = get_pos_str()
              if legal_position() and pos_str not in visited_states:
                queue.put([pos_str, state[1] + 1, rook_moved])
                prev_states[pos_str] = state[0]
                visited_states.add(state[0])
            # move white rook
            if not rook_moved and abs(wr[0] - bk[0]) < 3 or abs(wr[1] - bk[1]) < 3:
              wk = original_wk
              for move in get_white_rook_moves():
                wr = move
                pos_str = get_pos_str()
                if legal_position() and pos_str not in visited_states:
                  queue.put([pos_str, state[1] + 1, True])
                  prev_states[pos_str] = state[0]
                  visited_states.add(state[0])
          # black to move
          else:
            current_player = "white"
            # move black king
            for move in get_black_king_moves():
              bk = move
              pos_str = get_pos_str()
              if legal_position() and pos_str not in visited_states:
                queue.put([pos_str, state[1] + 1, rook_moved])
                prev_states[pos_str] = state[0]
                visited_states.add(state[0])
