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


class Node:
    def __init__(self):
        self.mv = None
        self.s = 1.0
        self.w = 0.0
        self.sons = list()
        self.parent = self
        self.plansza = Board()


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

    def evaluate(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]
                if b == 0:
                    res -= weights[y][x]
                elif b == 1:
                    res += weights[y][x]
        return res

    def AB_move(self, depth, player):
        def absearch(state, depth, alpha, beta, player):
            if state.terminal():
                r = state.result()
                if r > 0:
                    return 1e9
                if r == 0:
                    return 0
                return -1e9
            if depth == 0:
                # return state.evaluate()
                return random.random()*10000

            options = state.moves(player)

            if player:
                value = -1e9
                for move in options:
                    new_state = Board()
                    new_state.board = deepcopy(self.board)
                    new_state.fields = set(self.fields)
                    new_state.move_list = list(self.move_list)
                    new_state.history = list(self.history)
                    new_state.do_move(move, player)
                    value = max(value, absearch(
                        new_state, depth-1, alpha, beta, 0))
                    alpha = max(alpha, value)
                    if alpha >= beta:
                        break
                return value
            else:
                value = 1e9
                for move in options:
                    new_state = Board()
                    new_state.board = deepcopy(self.board)
                    new_state.fields = set(self.fields)
                    new_state.move_list = list(self.move_list)
                    new_state.history = list(self.history)
                    new_state.do_move(move, player)
                    value = min(value, absearch(
                        new_state, depth-1, alpha, beta, 1))
                    beta = min(beta, value)
                    if alpha >= beta:
                        break
                return value

        ms = self.moves(player)

        best_move = None
        top_score = -1e9

        for move in ms:
            new_state = Board()
            new_state.board = deepcopy(self.board)
            new_state.fields = set(self.fields)
            new_state.move_list = list(self.move_list)
            new_state.history = list(self.history)
            new_state.do_move(move, player)
            # new_state = deepcopy(self)
            # new_state.do_move(move, player)

            score = absearch(new_state, depth, -1e9, 1e9, 1 - player)
            if score > top_score:
                best_move = move
                top_score = score
        return best_move

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

    def MCTS(self, player, simulations):
        order = 0
        v = Node()
        # copying board
        v.plansza.board = deepcopy(self.board)
        v.plansza.fields = set(self.fields)
        v.plansza.move_list = list(self.move_list)

        # creating edges from root
        for move in self.moves(player):
            son = Node()
            son.plansza.board = deepcopy(self.board)
            son.plansza.fields = set(self.fields)
            son.plansza.move_list = list(self.move_list)
            son.plansza.do_move(move, player)
            son.parent = v
            son.mv = move
            v.sons.append(son)

        for debug in range(simulations):
            dead_end = False
            res = 0
            # selection
            while True:
                if len(v.sons) == 0:
                    break
                if v.plansza.terminal():
                    dead_end = True
                    break
                q = PriorityQueue()
                for son in v.sons:
                    if player == 1:
                        q.put(
                            (-1.0 * (son.w / son.s + 1.4 * math.sqrt(math.log(v.s) / son.s)), order + 1, son))
                        order += 1
                    else:
                        q.put((-1.0*((son.s - son.w)/son.s + 1.4 *
                                     math.sqrt(math.log(v.s) / son.s)), order + 1, son))
                        order += 1

                v = q.get()[2]
                player = 1 - player

            # expansion
            if not dead_end:
                # expand
                for move in v.plansza.moves(player):
                    exp = Node()
                    exp.plansza.board = deepcopy(v.plansza.board)
                    exp.plansza.fields = set(v.plansza.fields)
                    exp.plansza.move_list = list(v.plansza.move_list)
                    exp.plansza.do_move(move, player)
                    exp.parent = v
                    exp.mv = move
                    v.sons.append(exp)
            # simulation
            if not dead_end:
                # simulate
                son = random.choice(v.sons)
                player = 1 - player
                move = son.plansza.random_move(player)
                res = son.plansza.simulation(1, 1000, move, player)
                if res > 0:
                    res = 1
                else:
                    res = 0
            else:
                res = v.plansza.result()
                if res > 0:
                    res = 1
                else:
                    res = 0
            # backpropagation
            while True:
                # back to start
                if v.parent == v:
                    v.s += 1
                    v.w += res
                    break
                v.s += 1
                v.w += res
                v = v.parent

        # here we choose our move
        order = 0
        q = PriorityQueue()
        for son in v.sons:
            #print(son.w / son.s)
            q.put((-1.0 * (son.w / son.s), order, son))
            order += 1
        # print("=====================")
        return q.get()[2].mv


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
