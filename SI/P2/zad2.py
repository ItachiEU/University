import collections
import copy


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


def legal_move(state, player, kierunek):
    if kierunek == 'u':
        # Only correct situations are (empty space, goal) right above or B followed by (empty space, goal) or * followed by (empty space, goal)
        # FIRST SITUTATION
        if state[player[0]-1][player[1]] == '.' or state[player[0]-1][player[1]] == 'G':
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                if state[player[0]-1][player[1]] == '.':
                    state[player[0]-1][player[1]] = 'K'
                else:
                    state[player[0]-1][player[1]] = '+'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                if state[player[0]-1][player[1]] == '.':
                    state[player[0]-1][player[1]] = 'K'
                else:
                    state[player[0]-1][player[1]] = '+'
            return state

        # second situation
        if state[player[0]-1][player[1]] == 'B' and (state[player[0]-2][player[1]] == '.' or state[player[0]-2][player[1]] == 'G'):
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                state[player[0]-1][player[1]] = 'K'
                if state[player[0]-2][player[1]] == '.':
                    state[player[0]-2][player[1]] = 'B'
                else:
                    state[player[0]-2][player[1]] = '*'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                state[player[0]-1][player[1]] = 'K'
                if state[player[0]-2][player[1]] == '.':
                    state[player[0]-2][player[1]] = 'B'
                else:
                    state[player[0]-2][player[1]] = '*'
            return state
        # third situation
        if state[player[0]-1][player[1]] == '*' and (state[player[0]-2][player[1]] == '.' or state[player[0]-2][player[1]] == 'G'):
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                state[player[0]-1][player[1]] = '+'
                if state[player[0]-2][player[1]] == '.':
                    state[player[0]-2][player[1]] = 'B'
                else:
                    state[player[0]-2][player[1]] = '*'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                state[player[0]-1][player[1]] = '+'
                if state[player[0]-2][player[1]] == '.':
                    state[player[0]-2][player[1]] = 'B'
                else:
                    state[player[0]-2][player[1]] = '*'
            return state
        # none of the above
        return -1
    if kierunek == 'd':
        # Only correct situations are (empty space, goal) right above or B followed by (empty space, goal) or * followed by (empty space, goal)
        # FIRST SITUTATION
        if state[player[0]+1][player[1]] == '.' or state[player[0]+1][player[1]] == 'G':
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                if state[player[0]+1][player[1]] == '.':
                    state[player[0]+1][player[1]] = 'K'
                else:
                    state[player[0]+1][player[1]] = '+'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                if state[player[0]+1][player[1]] == '.':
                    state[player[0]+1][player[1]] = 'K'
                else:
                    state[player[0]+1][player[1]] = '+'
            return state

        # second situation
        if state[player[0]+1][player[1]] == 'B' and (state[player[0]+2][player[1]] == '.' or state[player[0]+2][player[1]] == 'G'):
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                state[player[0]+1][player[1]] = 'K'
                if state[player[0]+2][player[1]] == '.':
                    state[player[0]+2][player[1]] = 'B'
                else:
                    state[player[0]+2][player[1]] = '*'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                state[player[0]+1][player[1]] = 'K'
                if state[player[0]+2][player[1]] == '.':
                    state[player[0]+2][player[1]] = 'B'
                else:
                    state[player[0]+2][player[1]] = '*'
            return state
        # third situation
        if state[player[0]+1][player[1]] == '*' and (state[player[0]+2][player[1]] == '.' or state[player[0]+2][player[1]] == 'G'):
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                state[player[0]+1][player[1]] = '+'
                if state[player[0]+2][player[1]] == '.':
                    state[player[0]+2][player[1]] = 'B'
                else:
                    state[player[0]+2][player[1]] = '*'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                state[player[0]+1][player[1]] = '+'
                if state[player[0]+2][player[1]] == '.':
                    state[player[0]+2][player[1]] = 'B'
                else:
                    state[player[0]+2][player[1]] = '*'
            return state
        # none of the above
        return -1
    if kierunek == 'l':
        # Only correct situations are (empty space, goal) right above or B followed by (empty space, goal) or * followed by (empty space, goal)
        # FIRST SITUTATION
        if state[player[0]][player[1]-1] == '.' or state[player[0]][player[1]-1] == 'G':
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                if state[player[0]][player[1]-1] == '.':
                    state[player[0]][player[1]-1] = 'K'
                else:
                    state[player[0]][player[1]-1] = '+'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                if state[player[0]][player[1]-1] == '.':
                    state[player[0]][player[1]-1] = 'K'
                else:
                    state[player[0]][player[1]-1] = '+'
            return state

        # second situation
        if state[player[0]][player[1]-1] == 'B' and (state[player[0]][player[1]-2] == '.' or state[player[0]][player[1]-2] == 'G'):
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                state[player[0]][player[1]-1] = 'K'
                if state[player[0]][player[1]-2] == '.':
                    state[player[0]][player[1]-2] = 'B'
                else:
                    state[player[0]][player[1]-2] = '*'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                state[player[0]][player[1]-1] = 'K'
                if state[player[0]][player[1]-2] == '.':
                    state[player[0]][player[1]-2] = 'B'
                else:
                    state[player[0]][player[1]-2] = '*'
            return state
        # third situation
        if state[player[0]][player[1]-1] == '*' and (state[player[0]][player[1]-2] == '.' or state[player[0]][player[1]-2] == 'G'):
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                state[player[0]][player[1]-1] = '+'
                if state[player[0]][player[1]-2] == '.':
                    state[player[0]][player[1]-2] = 'B'
                else:
                    state[player[0]][player[1]-2] = '*'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                state[player[0]][player[1]-1] = '+'
                if state[player[0]][player[1]-2] == '.':
                    state[player[0]][player[1]-2] = 'B'
                else:
                    state[player[0]][player[1]-2] = '*'
            return state
        # none of the above
        return -1
    if kierunek == 'r':
        # Only correct situations are (empty space, goal) right above or B followed by (empty space, goal) or * followed by (empty space, goal)
        # FIRST SITUTATION
        if state[player[0]][player[1]+1] == '.' or state[player[0]][player[1]+1] == 'G':
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                if state[player[0]][player[1]+1] == '.':
                    state[player[0]][player[1]+1] = 'K'
                else:
                    state[player[0]][player[1]+1] = '+'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                if state[player[0]][player[1]+1] == '.':
                    state[player[0]][player[1]+1] = 'K'
                else:
                    state[player[0]][player[1]+1] = '+'
            return state

        # second situation
        if state[player[0]][player[1]+1] == 'B' and (state[player[0]][player[1]+2] == '.' or state[player[0]][player[1]+2] == 'G'):
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                state[player[0]][player[1]+1] = 'K'
                if state[player[0]][player[1]+2] == '.':
                    state[player[0]][player[1]+2] = 'B'
                else:
                    state[player[0]][player[1]+2] = '*'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                state[player[0]][player[1]+1] = 'K'
                if state[player[0]][player[1]+2] == '.':
                    state[player[0]][player[1]+2] = 'B'
                else:
                    state[player[0]][player[1]+2] = '*'
            return state
        # third situation
        if state[player[0]][player[1]+1] == '*' and (state[player[0]][player[1]+2] == '.' or state[player[0]][player[1]+2] == 'G'):
            if state[player[0]][player[1]] == 'K':
                state[player[0]][player[1]] = '.'
                state[player[0]][player[1]+1] = '+'
                if state[player[0]][player[1]+2] == '.':
                    state[player[0]][player[1]+2] = 'B'
                else:
                    state[player[0]][player[1]+2] = '*'

            if state[player[0]][player[1]] == '+':
                state[player[0]][player[1]] = 'G'
                state[player[0]][player[1]+1] = '+'
                if state[player[0]][player[1]+2] == '.':
                    state[player[0]][player[1]+2] = 'B'
                else:
                    state[player[0]][player[1]+2] = '*'
            return state
        # none of the above
        return -1


def check_win(state):
    for i in range(len(state)):
        for j in range(len(state[i])):
            if state[i][j] == 'B':
                return False
    return True


def check_sense(state):
    for i in range(len(state)):
        for j in range(len(state[i])):
            if state[i][j] == 'B':
                if (state[i-1][j] == 'W' and state[i][j-1] == 'W') or (state[i-1][j] == 'W' and state[i][j+1] == 'W') or (state[i+1][j] == 'W' and state[i][j-1] == 'W') or (state[i-1][j] == 'W' and state[i][j+1] == 'W'):
                    return False
    return True


def solution(plansza):
    visited = dict()
    start = find_start(plansza)
    q = collections.deque()
    moves = []
    q.put((plansza, start, moves))
    while len(q) > 0:
        state, pos, moves = q.popleft()
        # print(moves)
        visited[tuple(tuple(row) for row in state)] = visited.get(
            tuple(tuple(row) for row in state), 0) + 1

        if check_win(state) == True:
            return moves
        if check_sense(state) == False:
            continue

        new_state = legal_move(copy.deepcopy(state), pos, 'u')
        if not new_state == -1:
            if visited.get(tuple(tuple(row) for row in new_state), 0) < 1:
                q.append((new_state, (pos[0]-1, pos[1]), moves + ['U']))

        new_state = legal_move(copy.deepcopy(state), pos, 'd')
        if not new_state == -1:
            if visited.get(tuple(tuple(row) for row in new_state), 0) < 1:
                q.append((new_state, (pos[0]+1, pos[1]), moves + ['D']))

        new_state = legal_move(copy.deepcopy(state), pos, 'l')
        if not new_state == -1:
            if visited.get(tuple(tuple(row) for row in new_state), 0) < 1:
                q.append((new_state, (pos[0], pos[1]-1), moves + ['L']))

        new_state = legal_move(copy.deepcopy(state), pos, 'r')
        if not new_state == -1:
            if visited.get(tuple(tuple(row) for row in new_state), 0) < 1:
                q.put((new_state, (pos[0], pos[1]+1), moves + ['R']))
    return -1


def solve():
    plansza = input_handler()
    result = solution(plansza.copy())
    res = ''.join(result)
    try:
        file = open('zad_output.txt', 'w')
    except:
        print('cannot open the file')
    file.write(res)
    file.close()


solve()
