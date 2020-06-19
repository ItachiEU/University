from queue import PriorityQueue
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

    odleglosci = preprocessing(plansza, walls, goals)
    return start, goals, walls, odleglosci


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


def bfs(pos, walls, goals, result):
    visited = set()
    q = collections.deque()
    q.append((pos, 0))
    visited.add(pos)
    result[pos[0]][pos[1]] = 0
    while len(q) > 0:
        v, d = q.popleft()

        result[v[0]][v[1]] = min(d, result[v[0]][v[1]])

        if ((v[0] - 1, v[1]) not in walls) and ((v[0] - 1, v[1]) not in visited):
            q.append(((v[0]-1, v[1]), d+1))
            visited.add((v[0] - 1, v[1]))
        if ((v[0] + 1, v[1]) not in walls) and ((v[0] + 1, v[1]) not in visited):
            q.append(((v[0]+1, v[1]), d+1))
            visited.add((v[0] + 1, v[1]))

        if ((v[0], v[1]-1) not in walls) and ((v[0], v[1]-1) not in visited):
            q.append(((v[0], v[1]-1), d+1))
            visited.add((v[0], v[1]-1))

        if ((v[0], v[1]+1) not in walls) and ((v[0], v[1]+1) not in visited):
            q.append(((v[0], v[1]+1), d+1))
            visited.add((v[0], v[1] + 1))


def preprocessing(plansza, walls, goals):
    n = len(plansza)
    m = len(plansza[0])
    odleglosci = []
    for i in range(n):
        temp = []
        for j in range(m):
            temp.append(1e9)
        odleglosci.append(temp)

    for i in range(len(plansza)):
        for j in range(len(plansza[i])):
            if plansza[i][j] == 'G' or plansza[i][j] == 'B':
                bfs((i, j), walls, goals, odleglosci)
    return odleglosci


def evaluate(positions, goals, odleglosci):
    min_dist = 0
    for pos in positions:
        min_dist = max(min_dist, odleglosci[pos[0]][pos[1]])
    return min_dist


def astar(positions, walls, goals, odleglosci):
    moves = ['U', 'D', 'L', 'R']
    q = PriorityQueue(0)
    counter = 1
    path = ''
    visited = set()
    # priority, draw_solver, positions, path
    q.put((0, 0, positions.copy(), path))
    visited.add(tuple(positions))

    while not q.empty():
        _, _, ziutki, path = q.get()

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
                val = evaluate(temp, goals, odleglosci)
                d = len(path)
                counter += 1
                q.put((val + d, counter, temp, path + ruch))
                visited.add(tuple(temp))
    return -1


def solve():
    starts, goals, walls, odleglosci = input_handler()
    result = astar(starts, walls, goals, odleglosci)
    print(result)
    try:
        file = open('zad_output.txt', 'w')
    except:
        print('Cannot open the file')
        exit()
    file.write(result)
    file.close()


solve()
