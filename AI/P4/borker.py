import random
import math
from queue import PriorityQueue

M = 8


def initial_board():
    B = [[None] * M for i in range(M)]
    B[3][3] = 1
    B[4][4] = 1
    B[3][4] = 0
    B[4][3] = 0
    return B


CORNERS = {(0, 0), (0, M - 1), (M - 1, 0), (M - 1, M - 1)}

BAD = {(1, 0), (0, 1), (1, 1), (M-2, 0), (M-2, 1), (M-1, 1),
       (M - 1, M - 2), (M - 2, M - 1), (M - 2, M - 2), (0, M - 2), (1, M - 2), (1, M - 1)}

FIRST_LAYER = {(i, 1) for i in range(1, M-1)} | {(i, M-2) for i in range(1, M-1)
                                                 } | {(1, i) for i in range(1, M - 1)} | {(M - 2, i) for i in range(1, M - 1)}

SECOND_LAYER = {(i, 2) for i in range(2, M-2)} | {(i, M-3) for i in range(2, M-2)
                                                  } | {(2, i) for i in range(2, M-2)} | {(M-3, i) for i in range(2, M-2)}


weights = (
    (400, -100, 100, 50, 50, 100, -100, 400),
    (-100, -200, -50, -50, -50, -50, -200, -100),
    (100, -50, 100, 0, 0, 100, -50, 100),
    (50, -50, 0, 0, 0, 0, -50, 50),
    (50, -50, 0, 0, 0, 0, -50, 50),
    (100, -50, 100, 0, 0, 100, -50, 100),
    (-100, -200, -50, -50, -50, -50, -200, -100),
    (400, -100, 100, 50, 50, 100, -100, 400))


def deepcopy(board):
    return [list(row) for row in board]


class Board:
    dirs = [(0, 1), (1, 0), (-1, 0), (0, -1),
            (1, 1), (-1, -1), (1, -1), (-1, 1)]

    def __init__(self):
        self.board = initial_board()
        self.fields = set()
        self.move_list = []
        self.history = []
        for i in range(M):
            for j in range(M):
                if self.board[i][j] == None:
                    self.fields.add((j, i))

    def draw(self):
        for i in range(M):
            res = []
            for j in range(M):
                b = self.board[i][j]
                if b == None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res))
        print()

    def moves(self, player):
        res = []
        for (x, y) in self.fields:
            if any(self.can_beat(x, y, direction, player) for direction in Board.dirs):
                res.append((x, y))
        if not res:
            return [None]
        return res

    def can_beat(self, x, y, d, player):
        dx, dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x, y) == 1-player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x, y) == player

    def get(self, x, y):
        if 0 <= x < M and 0 <= y < M:
            return self.board[y][x]
        return None

    def do_move(self, move, player):
        self.history.append([x[:] for x in self.board])
        self.move_list.append(move)

        if move == None:
            return
        x, y = move
        x0, y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        for dx, dy in self.dirs:
            x, y = x0, y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x, y) == 1-player:
                to_beat.append((x, y))
                x += dx
                y += dy
            if self.get(x, y) == player:
                for (nx, ny) in to_beat:
                    self.board[ny][nx] = player

    def result(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]
                if b == 0:
                    res -= 1
                elif b == 1:
                    res += 1
        return res

    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] == None

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return [None]

    def montecarlo(self, player):
        ms = self.moves(player)

        corners = CORNERS & set(ms)

        if corners:
            return random.choice(list(corners))

        search = [move for move in ms if move not in BAD]

        fl = FIRST_LAYER & set(search)

        if fl:
            return random.choice(list(fl))

        sl = SECOND_LAYER & set(search)

        if sl:
            return random.choice(list(sl))

        return max(search if search else ms, key=lambda x: self.simulation(6, 10, x, player))

    def simulation(self, n, moves_forward, move, player):
        total_score = 0
        curr_state = Board()
        curr_state.board = deepcopy(self.board)
        curr_state.fields = set(self.fields)
        curr_state.move_list = list(self.move_list)
        curr_state.history = list(self.history)
        curr_state.do_move(move, player)
        for _ in range(n):
            new_state = Board()
            new_state.board = deepcopy(curr_state.board)
            new_state.fields = set(curr_state.fields)
            new_state.move_list = list(curr_state.move_list)
            new_state.history = list(curr_state.history)
            new_player = 1 - player

            for _ in range(moves_forward):
                m = new_state.random_move(new_player)
                new_state.do_move(m, new_player)
                new_player = 1-new_player
                if new_state.terminal():
                    break
            total_score += new_state.result()
        return total_score


our_losses = 0
games = 1000
for i in range(1, games+1):

    player = 0
    B = Board()

    while True:
        # B.draw()
        if not player:
            # our move function
            m = B.random_move(player)
            #m = B.MCTS(player, 500)
            #m = B.AB_move(3, player)
        else:
            m = B.montecarlo(player)
            #m = B.random_move(player)
            #m = B.MCTS(player, 500)

        B.do_move(m, player)
        player = 1-player
        if B.terminal():
            break

    r = B.result()
    # print(r)
    if r < 0:
        our_losses += 1
    if i % 100 == 0:
        # B.draw()
        print(f"Games played: {i} Games lost: {our_losses}")

print(f"Games played: {games} Games lost: {our_losses}")
