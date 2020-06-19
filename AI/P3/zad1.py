from queue import Queue
from numpy import zeros


def input_handler():
    try:
        file = open('zad_input.txt', 'r')
    except:
        print('cannot open the file.')
        exit()
    data, rows, columns = [], [], []
    for line in file:
        data.append(line.split())
    file.close()
    r, c = int(data[0][0]), int(data[0][1])
    for i in range(1, r+1):
        rows.append(list(map(int, data[i])))
    for i in range(r+1, len(data)):
        columns.append(list(map(int, data[i])))
    return (rows, columns)


def possible_settings(n, blocksizes):
    if n == 0:
        return [[]]
    if len(blocksizes) == 0:
        return [[0] * n]

    block_len = blocksizes[0]
    block = [1 for _ in range(block_len)]
    new_n = n - block_len

    if len(blocksizes[1:]) > 0:
        block += [0]
        new_n -= 1

    current_possibilities = [
        block + new_pattern for new_pattern in possible_settings(new_n, blocksizes[1:])]
    required_len = sum(blocksizes) + len(blocksizes) - 1
    if required_len < n:
        return current_possibilities + [
            [0] + pattern for pattern in possible_settings(n-1, blocksizes)
        ]
    else:
        return current_possibilities


def solution(rows, columns):
    height, width = len(rows), len(columns)
    possible_rows = [possible_settings(width, row) for row in rows]
    possible_columns = [possible_settings(
        height, column) for column in columns]

    result = zeros((height, width))
    tofix = Queue(0)  # points that are still not certain

    def eliminate_columns(y, x):
        val = result[y][x]
        possible_columns[x] = [
            column for column in possible_columns[x] if column[y] == val
        ]

    def eliminate_rows(y, x):
        val = result[y][x]
        possible_rows[y] = [
            row for row in possible_rows[y] if row[x] == val
        ]

    def point_solution(y, x, current_rows):
        test_point = current_rows[0][x]

        if all(row[x] == test_point for row in current_rows):
            result[y][x] = test_point
            eliminate_columns(y, x)
        else:
            test_point = possible_columns[x][0][y]
            if all(column[y] == test_point for column in possible_columns[x]):
                result[y][x] = test_point
                eliminate_rows(y, x)
            else:
                tofix.put((y, x))

    for y in range(height):
        current_rows = possible_rows[y]
        for x in range(width):
            point_solution(y, x, current_rows)

    while not tofix.empty():
        y, x = tofix.get()
        current_rows = possible_rows[y]
        point_solution(y, x, current_rows)

    return result


def solve():
    rows, columns = input_handler()
    res = solution(rows, columns)

    try:
        file = open('zad_output.txt', 'w')
    except:
        print('cannot open file')
        exit()

    out = ''
    for i in range(len(rows)):
        for j in range(len(columns)):
            if res[i][j] == 0:
                out += '.'
            else:
                out += '#'
        out += '\n'
    # print(out)
    file.write(out)
    file.close()


solve()
