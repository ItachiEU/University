import sys
import math
import collections
import random
import time
# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

width, height, my_id = [int(i) for i in input().split()]

board = []
visited = []

enemy_positions = set()
my_positions = set()
mines = set()

for i in range(height):
    line = input()
    temp = []
    vis_temp = []
    for char in line:
        vis_temp.append(0)
        if char == '.':
            temp.append(0)
        else:
            temp.append(1)
    board.append(temp)
    visited.append(vis_temp)

# Write an action using print
# To debug: print("Debug messages...", file=sys.stderr)

maxik = 0
starting_x = 0
starting_y = 0

round_time = 0.0


def bfs(pozycja):
    global enemy_visited
    # tu trzeba jeszcze temporary ustawic globalne visited na startowej pozycji
    visited[pozycja[0]][pozycja[1]] = 1
    # ========
    que = collections.deque()
    vis = set()
    que.append(pozycja)
    res = 0
    while len(que) > 0:
        v = que.popleft()
        if v in mines:
            res += 1
        if v in enemy_visited:
            res -= 2
        if v[0] - 1 >= 0 and board[v[0]-1][v[1]] == 0 and visited[v[0]-1][v[1]] == 0 and (v[0]-1, v[1]) not in vis:
            que.append((v[0]-1, v[1]))
            vis.add((v[0]-1, v[1]))
        if v[0] + 1 < height and board[v[0]+1][v[1]] == 0 and visited[v[0]+1][v[1]] == 0 and (v[0]+1, v[1]) not in vis:
            que.append((v[0]+1, v[1]))
            vis.add((v[0]+1, v[1]))
        if v[1] - 1 >= 0 and board[v[0]][v[1]-1] == 0 and visited[v[0]][v[1]-1] == 0 and (v[0], v[1]-1) not in vis:
            que.append((v[0], v[1]-1))
            vis.add((v[0], v[1]-1))
        if v[1] + 1 < width and board[v[0]][v[1]+1] == 0 and visited[v[0]][v[1]+1] == 0 and (v[0], v[1]+1) not in vis:
            que.append((v[0], v[1]+1))
            vis.add((v[0], v[1]+1))
    # USTAWIAM SPOWROTEM NA 0
    visited[pozycja[0]][pozycja[1]] = 0
    return len(vis) + res


paths = set()
enemy_visited = set()

for i in range(height-1, -1, -1):
    for j in range(width-1, -1, -1):
        if board[i][j] == 0:
            enemy_positions.add((i, j))
            my_positions.add((i, j))
            paths.add((((-1, -1), (i, j)), (i, j)))
        if board[i][j] == 0:
            temp = bfs((i, j))
            temp_y = i
            temp_x = j
            if temp > maxik:
                maxik = temp
                starting_x = temp_x
                starting_y = temp_y

visited[starting_y][starting_x] = 1


print(starting_x, starting_y)

basic_sector = set([(p, q) for p in range(5) for q in range(5)])


def generate_torpedo(pos):
    t = set()
    for i in range(max(0, pos[0]-4), min(height, pos[0]+5)):
        for j in range(max(0, pos[1]-4), min(width, pos[1]+5)):
            if abs(pos[0] - i) + abs(pos[1] - j) <= 4:
                t.add((i, j))
    return t


def choose_sector(enemies):
    maxik = 0
    result = 0
    for i in range(1, 10):
        sector = i
        x_factor = (sector - 1) % 3
        y_factor = (sector + 2) // 3 - 1
        this_sector = set()
        for square in basic_sector:
            this_sector.add((square[0]+y_factor*5, square[1]+x_factor*5))
        temp = len(enemies.intersection(this_sector))
        if temp > maxik:
            maxik = temp
            result = i
    return result


def update_enemy(enemy_positions, move, sector=0):
    if move == 'N':
        temp = set()
        for pos in enemy_positions:
            if pos[0]-1 >= 0 and board[pos[0]-1][pos[1]] == 0:
                temp.add((pos[0]-1, pos[1]))
        return temp
    if move == 'S':
        temp = set()
        for pos in enemy_positions:
            if pos[0]+1 < height and board[pos[0]+1][pos[1]] == 0:
                temp.add((pos[0]+1, pos[1]))
        return temp
    if move == 'E':
        temp = set()
        for pos in enemy_positions:
            if pos[1]+1 < width and board[pos[0]][pos[1]+1] == 0:
                temp.add((pos[0], pos[1]+1))
        return temp
    if move == 'W':
        temp = set()
        for pos in enemy_positions:
            if pos[1]-1 >= 0 and board[pos[0]][pos[1]-1] == 0:
                temp.add((pos[0], pos[1]-1))
        return temp
    if move == 'SURFACE':
        sector = int(sector)
        x_factor = (sector - 1) % 3
        y_factor = (sector + 2) // 3 - 1
        this_sector = set()
        for square in basic_sector:
            this_sector.add((square[0]+y_factor*5, square[1]+x_factor*5))

        global enemy_visited
        global paths
        paths.clear()
        enemy_visited.clear()
        t = enemy_positions.intersection(this_sector)
        for pos in t:
            paths.add((((-1, -1), (pos[0], pos[1])), (pos[0], pos[1])))
        return t

    if move == 'TORPEDO':
        t = generate_torpedo(sector)
        #print('t w torpedo: ', t, file=sys.stderr)
        return enemy_positions.intersection(t)

    if move == 'SILENCE':
        t = set()
        for pos in enemy_positions:
            temp = set([(pos[0] + p, pos[1] + q)
                        for p in range(-4, 5) for q in range(-4, 5)])
            t = t.union(temp)
        temp = set()
        for pos in t:
            if pos[0] < 0 or pos[0] >= height or pos[1] < 0 or pos[1] >= width or board[pos[0]][pos[1]] == 1:
                continue
            else:
                temp.add(pos)
        return temp
    if move == 'TRIGGER':
        t = set()
        for i in range(sector[0]-1, sector[0]+2):
            for j in range(sector[1]-1, sector[1]+2):
                t.add((i, j))
        return enemy_positions.difference(t)


def update_after_mine(enemy_positions, hit, mine, last_move):
    #print(mine, hit, file=sys.stderr)
    t = set()
    for i in range(mine[0]-1, mine[0]+2):
        for j in range(mine[1]-1, mine[1]+2):
            if (i, j) != mine:
                t.add((i, j))
    if hit == 2:
        t = set()
        t.add(mine)
        return t
    elif hit == 1:
        return enemy_positions.intersection(t)
    elif hit == 0:
        t.add(mine)
        return enemy_positions.difference(t)


def update_after_torpedo(enemy_positions, hit, torpedo, last_move):
    if last_move == -1:
        return enemy_positions
    t = set()
    for i in range(torpedo[0]-1, torpedo[0]+2):
        for j in range(torpedo[1]-1, torpedo[1]+2):
            if (i, j) != torpedo:
                t.add((i+last_move[0], j+last_move[1]))
    if hit == 2:
        t = set()
        t.add((torpedo[0] + last_move[0], torpedo[1] + last_move[1]))
        return t
    elif hit == 1:
        return enemy_positions.intersection(t)
    elif hit == 0:
        t.add((torpedo[0]+last_move[0], torpedo[1]+last_move[1]))
        return enemy_positions.difference(t)


def update_me(my_positions, move, sector=0, opponent_orders=0):
    if move == 'N':
        temp = set()
        for pos in my_positions:
            if pos[0]-1 >= 0 and board[pos[0]-1][pos[1]] == 0:
                temp.add((pos[0]-1, pos[1]))
        return temp
    if move == 'S':
        temp = set()
        for pos in my_positions:
            if pos[0]+1 < height and board[pos[0]+1][pos[1]] == 0:
                temp.add((pos[0]+1, pos[1]))
        return temp
    if move == 'E':
        temp = set()
        for pos in my_positions:
            if pos[1]+1 < width and board[pos[0]][pos[1]+1] == 0:
                temp.add((pos[0], pos[1]+1))
        return temp
    if move == 'W':
        temp = set()
        for pos in my_positions:
            if pos[1]-1 >= 0 and board[pos[0]][pos[1]-1] == 0:
                temp.add((pos[0], pos[1]-1))
        return temp
    if move == 'SURFACE':
        sector = int(sector)
        x_factor = (sector - 1) % 3
        y_factor = (sector + 2) // 3 - 1
        this_sector = set()
        for square in basic_sector:
            this_sector.add((square[0]+y_factor*5, square[1]+x_factor*5))
        return my_positions.intersection(this_sector)

    if move == 'TORPEDO':
        t = generate_torpedo(sector)
        return my_positions.intersection(t)

    if move == 'SILENCE':
        t = set()
        for pos in my_positions:
            temp = set([(pos[0] + p, pos[1] + q)
                        for p in range(-4, 5) for q in range(-4, 5)])
            t = t.union(temp)
        temp = set()
        for pos in t:
            if pos[0] < 0 or pos[0] >= height or pos[1] < 0 or pos[1] >= width or board[pos[0]][pos[1]] == 1:
                continue
            else:
                temp.add(pos)
        return temp
    if move == 'ENEMY_TORPEDO':
        start = -1
        fi = ''
        sec = ''
        for word in opponent_orders.split():
            if word == 'TORPEDO':
                start = 0
            elif start == 0:
                sec = word
                start += 1
            elif start == 1:
                fi = word
                start = 2
            elif start == 2:
                break
        t = set()
        fi = int(fi)
        sec = int(sec)
        for i in range(fi-1, fi+2):
            for j in range(sec-1, sec+2):
                if (fi, sec) != (i, j):
                    t.add((i, j))
        if sector == 2:
            t = set()
            t.add((fi, sec))
            return t
        elif sector == 1:
            return my_positions.intersection(t)
        else:
            t.add((fi, sec))
            return my_positions.difference(t)
    if move == 'ENEMY_TRIGGER':
        start = -1
        fi = ''
        sec = ''
        for word in opponent_orders.split():
            if word == 'TRIGGER':
                start = 0
            elif start == 0:
                sec = word
                start += 1
            elif start == 1:
                fi = word
                start = 2
            elif start == 2:
                break
        fi = int(fi)
        sec = int(sec)
        t = set()
        for i in range(fi-1, fi+2):
            for j in range(sec-1, sec+2):
                if (fi, sec) != (i, j):
                    t.add((i, j))
        if sector == 2:
            t = set()
            t.add((fi, sec))
            return t
        elif sector == 1:
            return my_positions.intersection(t)
        else:
            t.add((fi, sec))
            return my_positions.difference(t)


def update_paths(type_move, about_move=0):
    global paths
    if type_move == 'MOVE':
        if about_move == 'N':
            temp = set()
            for el in paths:
                pos = el[1]
                if pos[0]-1 >= 0 and board[pos[0]-1][pos[1]] == 0:
                    tempik = set(el[0])
                    if (pos[0]-1, pos[1]) not in tempik:
                        tempik.add((pos[0]-1, pos[1]))
                        temp.add((tuple(tempik), (pos[0]-1, pos[1])))
            paths = temp
        if about_move == 'S':
            temp = set()
            for el in paths:
                pos = el[1]
                if pos[0]+1 < height and board[pos[0]+1][pos[1]] == 0:
                    tempik = set(el[0])
                    if (pos[0]+1, pos[1]) not in tempik:
                        tempik.add((pos[0]+1, pos[1]))
                        temp.add((tuple(tempik), (pos[0]+1, pos[1])))
            paths = temp
        if about_move == 'E':
            temp = set()
            for el in paths:
                pos = el[1]
                if pos[1]+1 < width and board[pos[0]][pos[1]+1] == 0:
                    tempik = set(el[0])
                    if (pos[0], pos[1]+1) not in tempik:
                        tempik.add((pos[0], pos[1]+1))
                        temp.add((tuple(tempik), (pos[0], pos[1]+1)))
            paths = temp
        if about_move == 'W':
            temp = set()
            for el in paths:
                pos = el[1]
                if pos[1]-1 >= 0 and board[pos[0]][pos[1]-1] == 0:
                    tempik = set(el[0])
                    if (pos[0], pos[1]-1) not in tempik:
                        tempik.add((pos[0], pos[1]-1))
                        temp.add((tuple(tempik), (pos[0], pos[1]-1)))
            paths = temp
    if type_move == 'SILENCE':
        temp = set()
        print('IN SILENCE', len(paths), file=sys.stderr, flush=True)
        if len(paths) > 400:
            global enemy_visited
            global enemy_positions
            paths.clear()
            enemy_visited.clear()
            for pos in enemy_positions:
                paths.add((((-1, -1), (pos[0], pos[1])), (pos[0], pos[1])))
            return
        start = time.time()
        for path in paths:
            pos = path[1]
            print(path[1], file=sys.stderr, flush=True)
            for dist in range(0, 5):
                if dist == 0:
                    temp.add(path)
                else:
                    # DODAĆ WSZYSTKIE PO DRODZE NIE TYLKO OSTATNI!!!!
                    if pos[0] + dist < height and board[pos[0]+dist][pos[1]] == 0:
                        tempik = set(path[0])
                        if (pos[0] + dist, pos[1]) not in tempik:
                            tempik.add((pos[0]+dist, pos[1]))
                            temp.add((tuple(tempik), (pos[0]+dist, pos[1])))
                    if pos[0] - dist >= 0 and board[pos[0]-dist][pos[1]] == 0:
                        tempik = set(path[0])
                        if (pos[0] - dist, pos[1]) not in tempik:
                            tempik.add((pos[0]-dist, pos[1]))
                            temp.add((tuple(tempik), (pos[0]-dist, pos[1])))
                    if pos[1] + dist < width and board[pos[0]][pos[1]+dist] == 0:
                        tempik = set(path[0])
                        if (pos[0], pos[1] + dist) not in tempik:
                            tempik.add((pos[0], pos[1]+dist))
                            temp.add((tuple(tempik), (pos[0], pos[1]+dist)))
                    if pos[1] - dist >= 0 and board[pos[0]][pos[1]-dist] == 0:
                        tempik = set(path[0])
                        if (pos[0], pos[1] - dist) not in tempik:
                            tempik.add((pos[0], pos[1]-dist))
                            temp.add((tuple(tempik), (pos[0], pos[1]-dist)))
            end = time.time()
            global round_time
            round_time = end - start
            if end - start >= 0.040:
                paths = temp
                break
        paths = temp
        #print('GITARA SIEMA', file=sys.stderr, flush = True)


def ruch(opponent_orders, enemy_positions):
    start = -1
    for word in opponent_orders.split():
        if word == 'MOVE':
            start = 0
        elif start == 0:
            enemy_positions = update_enemy(enemy_positions.copy(), word)
            update_paths('MOVE', word)
            return enemy_positions


def torpeda(opponent_orders, enemy_positions):
    start = -1
    for word in opponent_orders.split():
        if word == 'TORPEDO':
            start = 0
        elif start == 0:
            sec = word
            start += 1
        elif start == 1:
            fi = word
            start = 2
        elif start == 2:
            break
    enemy_positions = update_enemy(
        enemy_positions.copy(), 'TORPEDO', (int(fi), int(sec)))
    return enemy_positions


def cicho(opponent_orders, enemy_positions):
    enemy_positions = update_enemy(enemy_positions.copy(), 'SILENCE')
    update_paths('SILENCE')
    return enemy_positions


def powierzchnia(opponent_orders, enemy_positions):
    start = -1
    for word in opponent_orders.split():
        if word == 'SURFACE':
            start = 0
        elif start == 0:
            enemy_positions = update_enemy(
                enemy_positions.copy(), 'SURFACE', word)
            return enemy_positions


def dummy(opponent_orders, enemy_positions):
    return enemy_positions


def torpedo_target(enemy_positions, me, my_life, opp_life):
    best_i = -1
    best_j = -1
    maxik = 0
    q = collections.deque()
    vis = set()
    q.append((me, 0))
    while len(q) > 0:
        v, d = q.popleft()
        temp = 0
        t = set()
        for p in range(v[0]-1, v[0]+2):
            for r in range(v[1]-1, v[1]+2):
                t.add((p, r))
        for position in enemy_positions:
            if position in t:
                if position == v:
                    temp += 1
                temp += 1
        if temp > maxik:
            best_i = v[0]
            best_j = v[1]
            maxik = temp
        if v[0] - 1 >= 0 and (v[0] - 1, v[1]) not in vis and board[v[0] - 1][v[1]] == 0 and d + 1 <= 4:
            q.append(((v[0] - 1, v[1]), d + 1))
            vis.add((v[0] - 1, v[1]))
        if v[0] + 1 < 15 and (v[0] + 1, v[1]) not in vis and board[v[0] + 1][v[1]] == 0 and d + 1 <= 4:
            q.append(((v[0] + 1, v[1]), d + 1))
            vis.add((v[0] + 1, v[1]))
        if v[1]-1 >= 0 and (v[0], v[1]-1) not in vis and board[v[0]][v[1]-1] == 0 and d + 1 <= 4:
            q.append(((v[0], v[1]-1), d + 1))
            vis.add((v[0], v[1]-1))
        if v[1] + 1 < 15 and (v[0], v[1]+1) not in vis and board[v[0]][v[1]+1] == 0 and d + 1 <= 4:
            q.append(((v[0], v[1]+1), d + 1))
            vis.add((v[0], v[1]+1))
    #print(maxik, file=sys.stderr)
    return (best_i, best_j)


def mine_target(pos, enemy_positions, mines):
    s = list()
    s.append((100, (-1, -1), 'W'))

    if pos[0] + 1 < height and board[pos[0]+1][pos[1]] == 0 and (pos[0]+1, pos[1]) not in mines:
        t = set()
        temp = 0
        for i in range(pos[0]+1-1, pos[0]+1+2):
            for j in range(pos[1]-1, pos[1]+2):
                t.add((i, j))
        for mine in mines:
            if mine in t:
                temp += 1
        s.append((temp, (pos[0]+1, pos[1]), 'S'))
    if pos[0] - 1 >= 0 and board[pos[0]-1][pos[1]] == 0 and (pos[0]-1, pos[1]) not in mines:
        t = set()
        temp = 0
        for i in range(pos[0]-1-1, pos[0]-1+2):
            for j in range(pos[1]-1, pos[1]+2):
                t.add((i, j))
        for mine in mines:
            if mine in t:
                temp += 1
        s.append((temp, (pos[0]-1, pos[1]), 'N'))
    if pos[1]-1 >= 0 and board[pos[0]][pos[1]-1] == 0 and (pos[0], pos[1]-1) not in mines:
        t = set()
        temp = 0
        for i in range(pos[0]-1, pos[0]+2):
            for j in range(pos[1]-1-1, pos[1]-1+2):
                t.add((i, j))
        for mine in mines:
            if mine in t:
                temp += 1
        s.append((temp, (pos[0], pos[1]-1), 'W'))
    if pos[1]+1 < width and board[pos[0]][pos[1]+1] == 0 and (pos[0], pos[1]+1) not in mines:
        t = set()
        temp = 0
        for i in range(pos[0]-1, pos[0]+2):
            for j in range(pos[1]+1-1, pos[1]+1+2):
                t.add((i, j))
        for mine in mines:
            if mine in t:
                temp += 1
        s.append((temp, (pos[0], pos[1]+1), 'E'))
    s.sort()
    #print(s[0], file=sys.stderr)
    mines.add(s[0][1])
    return s[0][2]


last_move = -1
my_move = -1
reveal = -1
my_hp = -1
silence = 0
torp = 0
target_x = -1
target_y = -1
last_dir = 0
runda = 0
# game loop
while True:
    x, y, my_life, opp_life, torpedo_cooldown, sonar_cooldown, silence_cooldown, mine_cooldown = [
        int(i) for i in input().split()]
    runda += 1

    if my_move == 'TRIGGER' and len(enemy_positions) > 1:
        if his_life > opp_life and (my_life == my_hp):
            enemy_positions = update_after_mine(
                enemy_positions.copy(), his_life - opp_life, that_mine, last_move)
        elif my_life != my_hp:
            pass
        else:
            enemy_positions = update_after_mine(
                enemy_positions.copy(), 0, that_mine, last_move)

    print('last move:', last_move, file=sys.stderr)
    if torp == 'TORPEDA' and len(enemy_positions) > 1:
        if his_life > opp_life and (my_life == my_hp):
            enemy_positions = update_after_torpedo(
                enemy_positions.copy(), his_life - opp_life, (target_y, target_x), last_move)
        elif my_life != my_hp:
            pass
        else:
            enemy_positions = update_after_torpedo(
                enemy_positions.copy(), 0, (target_y, target_x), last_move)

    torp = 0
    my_move = -1
    silence = 0
    if my_life < my_hp:
        silence = my_hp - my_life

    sonar_result = input()
    opponent_orders = input()
    print(opponent_orders, file=sys.stderr)

    opponent_orders = opponent_orders.replace('|', ' ')
    #print(opponent_orders, file=sys.stderr)
    # saving the last move (need to add the silence)
    start = -1
    for word in opponent_orders.split():
        if word == 'MOVE':
            start = 0
        elif start == 0:
            if word == 'N':
                last_move = (-1, 0)
            if word == 'S':
                last_move = (1, 0)
            if word == 'W':
                last_move = (0, -1)
            if word == 'E':
                last_move = (0, 1)
            break

    if 'MOVE' not in opponent_orders:
        last_move = -1
    funkcje = {'MOVE': ruch, 'SILENCE': cicho,
               'TORPEDO': torpeda, 'SURFACE': powierzchnia}

    # ustawianie mozliwych pozycji przeciwnika
    for word in opponent_orders.split():
        if word == 'TORPEDO':
            my_positions = update_me(
                my_positions.copy(), 'ENEMY_TORPEDO', silence, opponent_orders)
        if word == 'TRIGGER':
            my_positions = update_me(
                my_positions.copy(), 'ENEMY_TRIGGER', silence, opponent_orders)
        if my_life >= opp_life and my_life > 2:
            if word == 'TRIGGER':
                start = -1
                fi = -1
                sec = -1
                for new_word in opponent_orders.split():
                    if new_word == 'TRIGGER':
                        start = 0
                    elif start == 0:
                        sec = int(new_word)
                        start = 1
                    elif start == 1:
                        fi = int(new_word)
                        break
                enemy_positions = update_enemy(
                    enemy_positions.copy(), 'TRIGGER', (fi, sec))
        enemy_positions = funkcje.get(word, dummy)(
            opponent_orders, enemy_positions.copy())

    print('PRZED WHILE', file=sys.stderr, flush=True)
    #print('enemy pos', enemy_positions, file=sys.stderr, flush = True)
    # SETTING ENEMY VISITED AND ELIMINATING HIS PATHS:
    start = time.time()
    if round_time <= 0.01:
        while True:
            print("test", file=sys.stderr, flush=True)
            # UPDATING PATHS
            temp = set()
            for path in paths:
                if path[1] in enemy_positions:
                    temp.add(path)
            paths = temp
            # FINDING THE POINTS THAT WERE VISITED 100%
            # SET A TIME LIMIT HEREEE
            for path in paths:
                pozycje = set(path[0])
                for el in pozycje:
                    end = time.time()
                    if (end - start) + round_time >= 0.02:
                        paths.clear()
                        enemy_visited.clear()
                        for pos in enemy_positions:
                            paths.add(
                                (((-1, -1), (pos[0], pos[1])), (pos[0], pos[1])))
                        break
                    found = True
                    for new_path in paths:
                        if el not in set(new_path[0]) or el == new_path[1]:
                            found = False
                            break
                    if found:
                        enemy_visited.add(el)
                break
            end = time.time()
            if (end - start) + round_time >= 0.02:
                break
            # DELETING THE PATHS THAT DON'T HAVE THE VISITED ONES
            temp = set()
            for pos in enemy_visited:
                for path in paths:
                    if pos in path[0]:
                        temp.add(path)
            paths = temp
            # UPDATING ENEMY POSITIONS
            temp = set()
            for pos in enemy_positions:
                if pos not in enemy_visited:
                    temp.add(pos)
            end = time.time()
            if len(temp) == len(enemy_positions) or (end - start) + round_time >= 0.02:
                # or (end - start) > 0.03:
                enemy_positions = temp
                break
            enemy_positions = temp

    print('Enemy positions: ', len(enemy_positions), file=sys.stderr)
    print(enemy_positions, file=sys.stderr)
    print(enemy_visited, file=sys.stderr)
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)
    move = ''
    options = []
    #closest = []
    # FIGURING OUT POSSIBLE MOVES
    if (y + 1 < height) and board[y+1][x] == 0 and visited[y+1][x] == 0:
        closest = 1e9
        for enemy in enemy_positions:
            closest = min(closest, abs(y+1 - enemy[0]) + abs(x - enemy[1]))

        val = bfs((y+1, x)) + \
            len(update_me(my_positions.copy(), 'S'))  # + closest
        # if len(enemy_positions) <=10 and torpedo_cooldown > 0:
        #     for pos in enemy_positions:
        #         if abs(y+1 - pos[0]) + abs(x - pos[1]) <=4:
        #             val -= 1
        # if last_dir == 'S':
        #     val -= 2
        check = 0
        for i in range(1, 5):
            if y+1+i < height and board[y+1+i][x] == 0 and visited[y+1+i][x] == 0:
                visited[y+i][x] = 1
                if bfs((y+1+i, x)) > 50:
                    check = i
                else:
                    visited[y+i][x] = 0
                    break
            else:
                break
        for i in range(1, i+1):
            visited[y+i][x] = 0
        #closest.append((close,(y+1, x), 'S'))
        options.append((val, (y+1, x), 'S', check))
    if y - 1 >= 0 and board[y-1][x] == 0 and visited[y-1][x] == 0:
        closest = 1e9
        for enemy in enemy_positions:
            closest = min(closest, abs(y-1 - enemy[0]) + abs(x - enemy[1]))
        val = bfs((y-1, x)) + \
            len(update_me(my_positions.copy(), 'N'))  # + closest
        # if len(enemy_positions) <= 10 and torpedo_cooldown > 0:
        #     for pos in enemy_positions:
        #         if abs(y-1 - pos[0]) + abs(x - pos[1]) <=4:
        #             val -= 1
        # if last_dir == 'N':
        #     val -= 2
        check = 0
        for i in range(1, 5):
            if y-1-i >= 0 and board[y-1-i][x] == 0 and visited[y-1-i][x] == 0:
                visited[y-i][x] = 1
                if bfs((y-1-i, x)) > 50:
                    check = i
                else:
                    visited[y-i][x] = 0
                    break
            else:
                break
        for i in range(1, i+1):
            visited[y-i][x] = 0
        #closest.append((close,(y-1, x), 'N'))
        options.append((val, (y-1, x), 'N', check))
    if x - 1 >= 0 and board[y][x-1] == 0 and visited[y][x-1] == 0:
        closest = 1e9
        for enemy in enemy_positions:
            closest = min(closest, abs(y - enemy[0]) + abs(x - 1 - enemy[1]))
        val = bfs((y, x-1)) + \
            len(update_me(my_positions.copy(), 'W'))  # + closest
        # if len(enemy_positions) <= 10 and torpedo_cooldown > 0:
        #     for pos in enemy_positions:
        #         if abs(y - pos[0]) + abs(x - 1 - pos[1]) <=4:
        #             val -= 1
        # if last_dir == 'W':
        #     val -= 2
        check = 0
        for i in range(1, 5):
            if x-1-i >= 0 and board[y][x-1-i] == 0 and visited[y][x-1-i] == 0:
                visited[y][x-i] = 1
                if bfs((y, x-i-1)) > 50:
                    check = i
                else:
                    visited[y][x-i] = 0
                    break
            else:
                break
        for i in range(1, i+1):
            visited[y][x-i] = 0
        #closest.append((close,(y, x-1), 'W'))
        options.append((val, (y, x-1), 'W', check))
    if x+1 < width and board[y][x+1] == 0 and visited[y][x+1] == 0:
        closest = 1e9
        for enemy in enemy_positions:
            closest = min(closest, abs(y - enemy[0]) + abs(x + 1 - enemy[1]))
        val = bfs((y, x+1)) + \
            len(update_me(my_positions.copy(), 'E'))  # + closest
        # if len(enemy_positions) <= 10 and torpedo_cooldown > 0:
        #     for pos in enemy_positions:
        #         if abs(y - pos[0]) + abs(x + 1 - pos[1]) <=4:
        #             val -= 1
        # if last_dir == 'E':
        #     val -= 2
        check = 0
        for i in range(1, 5):
            if x+i+1 < width and board[y][x+i+1] == 0 and visited[y][x+i+1] == 0:
                visited[y][x+i] = 1
                if bfs((y, x+1+i)) > 50:
                    check = i
                else:
                    visited[y][x+i] = 0
                    break
            else:
                break
        for i in range(1, i+1):
            visited[y][x+i] = 0
        #closest.append((close,(y, x+1), 'E'))
        options.append((val, (y, x+1), 'E', check))
    maxik = 0
    #print(options, file=sys.stderr)
    power = ''
    if len(options) == 0 or (runda > 90 and my_life >= 2):
        move = 'SURFACE'
        runda = 0
        my_positions = update_me(
            my_positions.copy(), 'SURFACE', (y//5) * 3 + x // 5 + 1)
    else:
        options.sort(reverse=True)
        if torpedo_cooldown > 0:
            power = 'TORPEDO'
        elif silence_cooldown > 0:
            power = 'SILENCE'
        elif mine_cooldown > 0:
            power = 'MINE'

        #print('my positions: ', len(my_positions), file=sys.stderr)
        #print(my_positions, file=sys.stderr)
        last_dir = options[0][2]

        if (len(my_positions) <= 4 or silence > 0 or (my_life <= 2 and len(mines) > 15)) and silence_cooldown == 0:
            if options[0][3] > 0:
                ile = random.randint(1, options[0][3])
                move = f'SILENCE {options[0][2]} {ile}'
                visited[options[0][1][0]][options[0][1][1]] = 1
                # ZMIENIC VISITEDYYYY!!!!!!
                if options[0][2] == 'N':
                    for i in range(1, ile):
                        visited[options[0][1][0]-i][options[0][1][1]] = 1
                if options[0][2] == 'S':
                    for i in range(1, ile):
                        visited[options[0][1][0]+i][options[0][1][1]] = 1
                if options[0][2] == 'W':
                    for i in range(1, ile):
                        visited[options[0][1][0]][options[0][1][1]-i] = 1
                if options[0][2] == 'E':
                    for i in range(1, ile):
                        visited[options[0][1][0]][options[0][1][1]+i] = 1
            else:
                move = f'SILENCE {options[0][2]} 1'
                visited[options[0][1][0]][options[0][1][1]] = 1
            my_positions = update_me(my_positions.copy(), 'SILENCE')
        # ELSE
        else:
            move = 'MOVE ' + options[0][2]
            visited[options[0][1][0]][options[0][1][1]] = 1
        maxik = 0
        final_pos = (0, 0)
        ziomale_miny = 0
        for pos in enemy_positions:
            if pos in mines or (pos[0]-1, pos[1]) in mines or (pos[0], pos[1]-1) in mines or (pos[0]+1, pos[1]) in mines or (pos[0], pos[1]+1) in mines or (pos[0]-1, pos[1]-1) in mines or (pos[0]+1, pos[1]+1) in mines or (pos[0]-1, pos[1]+1) in mines or (pos[0]+1, pos[1]-1) in mines:
                ziomale_miny += 1
        if (len(enemy_positions) <= 3 or (len(enemy_positions) <= 7 and silence_cooldown == 0) or (len(enemy_positions) <= 5 and len(my_positions) == 1)) and torpedo_target(enemy_positions.copy(), (y, x), my_life, opp_life) != (-1, -1) and torpedo_cooldown == 0:
            # FIND OUT WHERE TO SHOOT THE TORPEDO
            target_y, target_x = torpedo_target(
                enemy_positions.copy(), (y, x), my_life, opp_life)
            if silence_cooldown == 0:
                move = f'TORPEDO {target_x} {target_y}| SILENCE {options[0][2]} {options[0][3]}'
                visited[options[0][1][0]][options[0][1][1]] = 1
                # ZMIENIC VISITEDYYYY!!!!!!
                if options[0][2] == 'N':
                    for i in range(1, options[0][3]):
                        visited[options[0][1][0]-i][options[0][1][1]] = 1
                if options[0][2] == 'S':
                    for i in range(1, options[0][3]):
                        visited[options[0][1][0]+i][options[0][1][1]] = 1
                if options[0][2] == 'W':
                    for i in range(1, options[0][3]):
                        visited[options[0][1][0]][options[0][1][1]-i] = 1
                if options[0][2] == 'E':
                    for i in range(1, options[0][3]):
                        visited[options[0][1][0]][options[0][1][1]+i] = 1
                torp = 'TORPEDO'
                my_positions = update_me(
                    my_positions.copy(), 'TORPEDO', (target_y, target_x))
                my_positions = update_me(my_positions.copy(), 'SILENCE')
            else:
                move = f'TORPEDO {target_x} {target_y}|' + move
                torp = 'TORPEDO'
                my_positions = update_me(
                    my_positions.copy(), 'TORPEDO', (target_y, target_x))
        elif (len(mines) > 0 and len(enemy_positions) <= 10) or (ziomale_miny > 0 and len(enemy_positions)/ziomale_miny < 1.5):
            '''or (ziomale_miny > 0 and len(enemy_positions)/ziomale_miny < 1.5)'''
            for mine in mines:
                counter = 0
                t = set()
                for i in range(mine[0]-1, mine[0]+2):
                    for j in range(mine[1]-1, mine[1]+2):
                        t.add((i, j))
                for pos in enemy_positions:
                    if pos in t:
                        if pos == mine:
                            counter += 1
                        counter += 1
                if counter > maxik and (abs(mine[0] - y) + abs(mine[1] - x)) > 2:
                    maxik = counter
                    final_pos = mine
            #print("DETONUJE: ", maxik, file=sys.stderr)
            if (len(enemy_positions) > 1 and maxik > 1) or (len(enemy_positions) == 1 and maxik > 0):
                move = f'TRIGGER {final_pos[1]} {final_pos[0]}|' + move
                mines.remove(final_pos)
                my_move = 'TRIGGER'
                his_life = opp_life
                that_mine = final_pos
        if mine_cooldown == 0:
            target = mine_target((y, x), enemy_positions.copy(), mines)
            move = f'MINE {target}|' + move
            power = 'MINE'

    #print(move, file=sys.stderr)
    if move != 'SURFACE' and 'SILENCE' not in move:
        move += f' {power}'
        my_positions = update_me(my_positions.copy(), options[0][2])
        print(move)
    elif move == 'SURFACE':
        maxik = 0
        final_pos = (0, 0)
        for mine in mines:
            counter = 0
            t = set()
            for i in range(mine[0]-1, mine[0]+2):
                for j in range(mine[1]-1, mine[1]+2):
                    t.add((i, j))
            for pos in enemy_positions:
                if pos in t:
                    counter += 1
            if counter > maxik and (abs(mine[0] - y) + abs(mine[1] - x)) > 2:
                maxik = counter
                final_pos = mine
        #print("DETONUJE: ", maxik, file=sys.stderr)
        if maxik > 0:
            move = f'TRIGGER {final_pos[1]} {final_pos[0]}|' + move
            mines.remove(final_pos)
            my_move = 'TRIGGER'
            his_life = opp_life
            that_mine = final_pos
        print(move)
        for i in range(height):
            for j in range(width):
                visited[i][j] = 0
        visited[y][x] = 1
    elif 'SILENCE' in move:
        print(move)
    my_hp = my_life
    round_time = 0.0
