import random
import os
import sys
import copy
import math
from queue import PriorityQueue


class WrongMove(Exception):
    pass


def deepcopy(board):
    return [list(row) for row in board]


class Node:
    def __init__(self):
        self.mv = None
        self.s = 1.0
        self.w = 0.0
        self.sons = list()
        self.parent = self
        self.game = Jungle()


class Jungle:
    PIECE_VALUES = {
        0: 4,
        1: 1,
        2: 2,
        3: 3,
        4: 5,
        5: 7,
        6: 8,
        7: 10
    }
    MAXIMAL_PASSIVE = 30
    DENS_DIST = 0.1
    MX = 7
    MY = 9
    traps = {(2, 0), (4, 0), (3, 1), (2, 8), (4, 8), (3, 7)}
    ponds = {(x, y) for x in [1, 2, 4, 5] for y in [3, 4, 5]}
    dens = [(3, 8), (3, 0)]
    dirs = [(0, 1), (1, 0), (-1, 0), (0, -1)]

    rat, cat, dog, wolf, jaguar, tiger, lion, elephant = range(8)

    def __init__(self):
        self.board = self.initial_board()
        self.pieces = {0: {}, 1: {}}

        for y in range(Jungle.MY):
            for x in range(Jungle.MX):
                C = self.board[y][x]
                if C:
                    pl, pc = C
                    self.pieces[pl][pc] = (x, y)
        self.curplayer = 0
        self.peace_counter = 0
        self.winner = None

    def initial_board(self):
        pieces = """
        L.....T
        .D...C.
        R.J.W.E
        .......
        .......
        .......
        e.w.j.r
        .c...d.
        t.....l
        """

        B = [x.strip() for x in pieces.split() if len(x) > 0]
        T = dict(zip('rcdwjtle', range(8)))

        res = []
        for y in range(9):
            raw = 7 * [None]
            for x in range(7):
                c = B[y][x]
                if c != '.':
                    if 'A' <= c <= 'Z':
                        player = 1
                    else:
                        player = 0
                    raw[x] = (player, T[c.lower()])
            res.append(raw)
        return res

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return None

    def can_beat(self, p1, p2, pos1, pos2):
        if pos1 in Jungle.ponds and pos2 in Jungle.ponds:
            return True  # rat vs rat
        if pos1 in Jungle.ponds:
            return False  # rat in pond cannot beat any piece on land
        if p1 == Jungle.rat and p2 == Jungle.elephant:
            return True
        if p1 >= p2:
            return True
        if pos2 in Jungle.traps:
            return True
        return False

    def pieces_comparison(self):
        for i in range(7, -1, -1):
            ps = []
            for p in [0, 1]:
                if i in self.pieces[p]:
                    ps.append(p)
            if len(ps) == 1:
                return ps[0]
        return None

    def rat_is_blocking(self, player_unused, pos, dx, dy):
        x, y = pos
        nx = x + dx
        for player in [0, 1]:
            if Jungle.rat not in self.pieces[1-player]:
                continue
            rx, ry = self.pieces[1-player][Jungle.rat]
            if (rx, ry) not in self.ponds:
                continue
            if dy != 0:
                if x == rx:
                    return True
            if dx != 0:
                if y == ry and abs(x-rx) <= 2 and abs(nx-rx) <= 2:
                    return True
        return False

    def draw(self):
        TT = {0: 'rcdwjtle', 1: 'RCDWJTLE'}
        for y in range(Jungle.MY):

            L = []
            for x in range(Jungle.MX):
                b = self.board[y][x]
                if b:
                    pl, pc = b
                    L.append(TT[pl][pc])
                else:
                    L.append('.')
            print(''.join(L))
        print('')

    def moves(self, player):
        res = []
        for p, pos in self.pieces[player].items():
            x, y = pos
            for (dx, dy) in Jungle.dirs:
                pos2 = (nx, ny) = (x+dx, y+dy)
                if 0 <= nx < Jungle.MX and 0 <= ny < Jungle.MY:
                    if Jungle.dens[player] == pos2:
                        continue
                    if pos2 in self.ponds:
                        if p not in (Jungle.rat, Jungle.tiger, Jungle.lion):
                            continue
                        # if self.board[ny][nx] is not None:
                        #    continue  # WHY??
                        if p == Jungle.tiger or p == Jungle.lion:
                            if dx != 0:
                                dx *= 3
                            if dy != 0:
                                dy *= 4
                            if self.rat_is_blocking(player, pos, dx, dy):
                                continue
                            pos2 = (nx, ny) = (x+dx, y+dy)
                    if self.board[ny][nx] is not None:
                        pl2, piece2 = self.board[ny][nx]
                        if pl2 == player:
                            continue
                        if not self.can_beat(p, piece2, pos, pos2):
                            continue
                    res.append((pos, pos2))
        return res

    def victory(self, player):
        oponent = 1-player
        if len(self.pieces[oponent]) == 0:
            self.winner = player
            return True

        x, y = self.dens[oponent]
        if self.board[y][x]:
            #print ('tu')
            # self.draw()
            self.winner = player
            return True

        if self.peace_counter >= Jungle.MAXIMAL_PASSIVE:
            r = self.pieces_comparison()
            if r is None:
                self.winner = 1  # draw is second player's victory
            else:
                self.winner = r
            return True
        return False

    def do_move(self, m):
        self.curplayer = 1 - self.curplayer
        if m is None:
            return
        pos1, pos2 = m
        x, y = pos1

        # TUTAJ NIE MOZE ROZPAKOWAC KIEDY JEST NONE !!!
        pl, pc = self.board[y][x]

        x2, y2 = pos2
        if self.board[y2][x2]:  # piece taken!
            pl2, pc2 = self.board[y2][x2]
            del self.pieces[pl2][pc2]
            self.peace_counter = 0
        else:
            self.peace_counter += 1

        self.pieces[pl][pc] = (x2, y2)
        self.board[y2][x2] = (pl, pc)
        self.board[y][x] = None

    def agent_move(self, player):
        ms = self.moves(player)
        og_player = player
        best_value = -1e9
        best_move = None
        for move in ms:
            new_game = Jungle()
            new_game.board = deepcopy(self.board)
            new_game.pieces = copy.deepcopy(self.pieces)
            new_game.curplayer = self.curplayer
            new_game.peace_counter = self.peace_counter
            new_game.winner = self.winner
            new_game.do_move(move)
            #print("before simulation: ", 1-player)
            value = simulate(new_game, 10, og_player)
            if value > best_value:
                best_value = value
                best_move = move

        return best_move

    def agent_move2(self, player, rounds):
        ms = self.moves(player)
        og_player = player
        best_value = -1e9
        if rounds < 10:
            best_value = 1e9
        best_move = None
        for move in ms:
            new_game = Jungle()
            new_game.board = deepcopy(self.board)
            new_game.pieces = copy.deepcopy(self.pieces)
            new_game.curplayer = self.curplayer
            new_game.peace_counter = self.peace_counter
            new_game.winner = self.winner
            new_game.do_move(move)
            if rounds < 10:
                value = evaluate(new_game, og_player)
                if value < best_value:
                    best_value = value
                    best_move = move
                continue
            #print("before simulation: ", 1-player)
            value = simulate(new_game, 10, og_player, True)
            if value > best_value:
                best_value = value
                best_move = move

        return best_move

    def heura(self, player):
        ms = self.moves(player)
        og_player = player

        best_value = 1e9
        best_move = None
        for move in ms:
            new_game = Jungle()
            new_game.board = deepcopy(self.board)
            new_game.pieces = copy.deepcopy(self.pieces)
            new_game.curplayer = self.curplayer
            new_game.peace_counter = self.peace_counter
            new_game.winner = self.winner
            new_game.do_move(move)
            value = evaluate(new_game, og_player)
            if value < best_value:
                best_value = value
                best_move = move

        return best_move

    def MCTS(self, og_player, simulations):
        order = 0
        player = og_player
        v = Node()
        # copying board
        v.game.board = deepcopy(self.board)
        v.game.pieces = copy.deepcopy(self.pieces)
        v.game.curplayer = self.curplayer
        v.game.peace_counter = self.peace_counter
        v.game.winner = self.winner

        # creating edges from root
        for move in self.moves(player):
            son = Node()
            son.game.board = deepcopy(self.board)
            son.game.pieces = copy.deepcopy(self.pieces)
            son.game.curplayer = self.curplayer
            son.game.peace_counter = self.peace_counter
            son.game.winner = self.winner
            son.game.do_move(move)
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
                if v.game.victory(player) or v.game.victory(1-player):
                    dead_end = True
                    break
                q = PriorityQueue()
                for son in v.sons:
                    if player == og_player:
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
            for move in v.game.moves(player):
                exp = Node()
                exp.game.board = deepcopy(v.game.board)
                exp.game.pieces = copy.deepcopy(v.game.pieces)
                exp.game.curplayer = v.game.curplayer
                exp.game.peace_counter = v.game.peace_counter
                exp.game.winner = v.game.winner
                exp.game.do_move(move)
                exp.parent = v
                exp.mv = move
                v.sons.append(exp)

        # simulation
        if not dead_end:
            # simulate
            son = random.choice(v.sons)
            player = 1 - player
            #move = son.game.random_move(player)
            res = max(simulate(son.game, 100, og_player), res)
            if res >= 100:
                res = 1
            else:
                res = 0
        else:
            res = v.game.winner
            if res == og_player:
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


def evaluate(game, player):
    res = 0
    for i in range(7, -1, -1):
        if i in game.pieces[player]:
            pos = game.pieces[player].get(i, None)
            res += abs(pos[0] - game.dens[1 - player][0]) + \
                abs(pos[1] - game.dens[1 - player][1])

    return res


def simulate(game, n, og_player):
    total_score = 0

    for _ in range(n):
        # COPY GAME HERE
        new_game = Jungle()
        new_game.board = deepcopy(game.board)
        # print (game.board)
        # print(new_game.board)
        new_game.pieces = copy.deepcopy(game.pieces)
        # print(game.pieces)
        new_game.curplayer = game.curplayer
        new_game.peace_counter = game.peace_counter
        new_game.winner = game.winner
        player = game.curplayer
        #print("in simulation: ", player)

        while True:
            m = new_game.random_move(player)
            # print(m)
            new_game.do_move(m)
          #   Game.draw()
          #   print('==========================')
            if new_game.victory(player) or new_game.victory(1-player):
                break
            player = 1 - player

        r = new_game.winner

        if r == og_player:
            total_score += 100
        else:
            total_score -= 1

    return total_score


our_losses = 0
games = 1000
for i in range(1, games+1):
    AGENT = random.choice([0, 1])

    player = 0
    Game = Jungle()
    r = None
    while True:
        counter = 0
        if not player:
            if AGENT == 1:
                #m = Game.random_move(player)
                #m = Game.agent_move2(player, counter)
                m = Game.agent_move(player)
            else:
                #m = Game.agent_move(player)
                m = Game.agent_move2(player, counter)
                #m = Game.heura(player)
                #m = Game.MCTS(player, 10000)
        else:
            if AGENT == 0:
                #m = Game.random_move(player)
                #m = Game.agent_move2(player, counter)
                m = Game.agent_move(player)
            else:
                #m = Game.agent_move(player)
                m = Game.agent_move2(player, counter)
                #m = Game.heura(player)
                #m = Game.MCTS(player, 10000)

        Game.do_move(m)
        #   Game.draw()
        #   print('==========================')
        if Game.victory(player) or Game.victory(1-player):
            break
        player = 1 - player
        counter += 1

    if Game.winner != AGENT:
        our_losses += 1
    if i % 10 == 0:
        # B.draw()
        print(f"Games played: {i} Games lost: {our_losses}")

print(f"Games played: {games} Games lost: {our_losses}")
