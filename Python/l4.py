# Zadanie 3

from typing import NamedTuple


class Position(NamedTuple):
    row: int
    col: int


DIM = 9

test_board = [
    [7, 8, 0, 4, 0, 0, 1, 2, 0],
    [6, 0, 0, 0, 7, 5, 0, 0, 9],
    [0, 0, 0, 6, 0, 1, 0, 7, 8],
    [0, 0, 7, 0, 4, 0, 2, 6, 0],
    [0, 0, 1, 0, 5, 0, 9, 3, 0],
    [9, 0, 4, 0, 6, 0, 0, 0, 5],
    [0, 7, 0, 3, 0, 0, 0, 1, 2],
    [1, 2, 0, 0, 0, 7, 4, 0, 0],
    [0, 4, 9, 2, 0, 6, 0, 0, 7]
]


def print_board(board: list) -> None:
    for i in range(DIM):
        if i % 3 == 0 and i != 0:
            print("--------------------------")
        for j in range(len(board[0])):
            if j % 3 == 0 and j != 0:
                print(" | ", end="")
            print(str(board[i][j]) + "\n" if j == 8 else str(
                board[i][j]) + " ", end="")


def find_empty(board: list) -> Position:
    for i in range(DIM):
        for j in range(DIM):
            if board[i][j] == 0:
                return Position(row=i, col=j)
    return None


def correct(board: list, digit: int, pos: Position) -> bool:
    for i in range(DIM):
        if board[pos.row][i] == digit and pos.col != i:
            return False

    for i in range(DIM):
        if board[i][pos.col] == digit and pos.row != i:
            return False

    for i in range(pos.row - pos.row % 3, pos.row - pos.row % 3 + 3):
        for j in range(pos.col - pos.col % 3, pos.col - pos.col % 3 + 3):
            if board[i][j] == digit and (i, j) != pos:
                return False

    return True


def solve(board: list) -> bool:
    empty_pos = find_empty(board)
    if empty_pos is None:
        return True
    else:
        row, col = empty_pos

    for digit in range(1, 10):
        if correct(board, digit, Position(row, col)):
            board[row][col] = digit

            if solve(board):
                return True

            board[row][col] = 0

    return False


print_board(test_board)
solve(test_board)
print("           |")
print("           |")
print("           |")
print("           |")
print("           |")
print("           v")
print_board(test_board)
