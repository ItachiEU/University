import collections
import random


def input_handler():
    '''
    return set of starting points, set of goals and set of walls, the rest are empty spaces
    '''
    goals = set()
    walls = set()
    start = set()
    try:
        file = open('zad_input.txt', 'r')
    except:
        print('Cannot open the file')
        exit()
    plansza = []
    for line in file:
        temp = []
        for char in line:
            if char != '\n':
                temp.append(char)
        plansza.append(temp)
    file.close()
    for i in range(len(plansza)):
        for j in range(len(plansza[i])):
            if plansza[i][j] == '#':
                walls.add((i, j))
            if plansza[i][j] == 'S':
                start.add((i, j))
            if plansza[i][j] == 'G':
                goals.add((i, j))
            if plansza[i][j] == 'B':
                goals.add((i, j))
                start.add((i, j))

    return start, goals, walls


def move(positions, walls, direction):
    if direction == 'U':
        temp = set()
        for pos in positions:
            if (pos[0] - 1, pos[1]) not in walls:
                temp.add((pos[0] - 1, pos[1]))
            else:
                temp.add(pos)
        return temp, direction
    if direction == 'D':
        temp = set()
        for pos in positions:
            if (pos[0] + 1, pos[1]) not in walls:
                temp.add((pos[0] + 1, pos[1]))
            else:
                temp.add(pos)
        return temp, direction
    if direction == 'L':
        temp = set()
        for pos in positions:
            if (pos[0], pos[1] - 1) not in walls:
                temp.add((pos[0], pos[1] - 1))
            else:
                temp.add(pos)
        return temp, direction
    if direction == 'R':
        temp = set()
        for pos in positions:
            if (pos[0], pos[1] + 1) not in walls:
                temp.add((pos[0], pos[1] + 1))
            else:
                temp.add(pos)
        return temp, direction


def bfs(positions, walls, goals):
    moves = ['U', 'D', 'L', 'R']
    q = collections.deque()
    path = ''
    visited = set()
    q.append((positions.copy(), path))
    visited.add(tuple(positions))

    while len(q) > 0:
        ziutki, path = q.popleft()

        if len(ziutki) <= len(goals):
            git = True
            for ziutek in ziutki:
                if ziutek not in goals:
                    git = False
            if git == True:
                return path

        for ruch in moves:
            temp, _ = move(ziutki.copy(), walls, ruch)
            if tuple(temp) not in visited:
                q.append((temp, path + ruch))
                visited.add(tuple(temp))
    return -1


def solution(starts, goals, walls):
    '''
    pozostale pola są puste
    '''
    moves = ['U', 'D', 'L', 'R']
    # reducing the number of possible starting points
    path = 'a' * 116
    positions = set()
    while len(path) > 115:
        positions = starts.copy()
        path = ''
        counter = 0
        while len(positions) > 2 and counter < 116:
            positions, direction = move(positions, walls, random.choice(moves))
            counter += 1
            path += direction
    final_path = bfs(positions, walls, goals)

    return path + final_path


def solve():
    starts, goals, walls = input_handler()
    result = solution(starts, goals, walls)
    print(result)
    try:
        file = open('zad_output.txt', 'w')
    except:
        print('Cannot open the file')
        exit()
    file.write(result)
    file.close()


solve()
