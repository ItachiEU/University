import copy
from queue import PriorityQueue
from queue import Queue


def input_handler():
    try:
        file = open('zad_input.txt', 'r')
    except:
        print('cannot open the file')
    plansza = []
    for line in file:
        temp = []
        for char in line:
            if char != '\n':
                temp.append(char)
        plansza.append(temp)
    file.close()
    return plansza


def find_start(plansza):
    for i in range(len(plansza)):
        for j in range(len(plansza[i])):
            if plansza[i][j] == 'K' or plansza[i][j] == '+':
                return (i, j)


def check_win(bloki, goals):
    '''
    return True if the given state is a winning one
    '''
    for blok in bloki:
        git = False
        for goal in goals:
            if blok[0] == goal[0] and blok[1] == goal[1]:
                git = True
                break
        if git == False:
            return False
    return True


def find_blocks(plansza):
    '''
    returns array of blocks and set of goals and set of walls
    '''
    bloki = []
    goals = set()
    walls = set()
    for i in range(len(plansza)):
        for j in range(len(plansza[i])):
            if plansza[i][j] == 'B' or plansza[i][j] == '*':
                bloki.append((i, j))
            if plansza[i][j] == 'G' or plansza[i][j] == '*':
                goals.add((i, j))
            if plansza[i][j] == 'W':
                walls.add((i, j))
    return (bloki, goals)


def evaluate(bloki, goals, player):
    '''
    heurystyka
    '''
    min_dist = 1e9

    for blok in bloki:
        act_dist = abs(player[0] - blok[0]) + abs(player[1] - blok[1])
        temp = 1e9
        for goal in goals:
            temp = min(temp, abs(blok[0] - goal[0]) + abs(blok[1] - goal[1]))
        min_dist = min(min_dist, temp + act_dist)
    return min_dist


def solution(plansza):
    '''
    return the array of moves that give the correct soulution
    '''
    visited = set()
    # poczatkowa pozycja gracza
    start = find_start(plansza)
    q = PriorityQueue(0)
    moves = []
    gcount = 0
    blocks, goals, walls = find_blocks(plansza)
    path = ''
    q.put((0, 0, blocks[:], start, path))
    while not q.empty():
        priority, count, bloki, pos, path = q.get()
        if check_win(bloki, goals) == True:
            return moves

        for blok in bloki:
            new_bloki, path = legal_move(bloki[:], 'u', walls, pos, path)
            prio = evaluate(new_bloki, goals, pos)
            gcount += 1
            q.put((prio, gcount, new_bloki[:], (pos[0]-1, pos[1]), path))


def solve():
    plansza = input_handler()
    result = solution(plansza.copy())
    res = ''.join(result)
    print(len(res))
    try:
        file = open('zad_output.txt', 'w')
    except:
        print('cannot open the file')
    file.write(res)
    file.close()


solve()
