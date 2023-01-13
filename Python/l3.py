from typing import Callable
from tabulate import tabulate
from math import sqrt, floor
from timeit import timeit


def compare_funcs(imp: Callable, comp: Callable, func: Callable, ns: list, numbers: int = 5000) -> None:
    print(tabulate([[f'{n}:', timeit(lambda: imp(n), number=numbers), timeit(lambda: comp(n), number=numbers), timeit(lambda: func(n), number=numbers)]
                    for n in ns], headers=['n', 'imperatywna', 'skladana', 'funkcyjna']))

# Zadanie 1


def is_prime(n: int) -> bool:
    divides = [i for i in range(2, floor(sqrt(n))+1) if n %
               i == 0 and i != n]
    return len(divides) == 0 and n != 1


def pierwsze_imperatywna(n: int) -> list:
    res = []
    for i in range(2, n + 1):
        if is_prime(i):
            res.append(i)
    return res


def pierwsze_skladana(n: int) -> list:
    return [i for i in range(2, n + 1) if is_prime(i)]


def pierwsze_funkcyjna(n: int) -> list:
    return list(filter(is_prime, range(2, n+1)))


print("Zadanie 1:")
compare_funcs(pierwsze_imperatywna, pierwsze_skladana,
              pierwsze_funkcyjna, list(range(10, 101, 10)))

# Zadanie 2


def is_perfect(n: int) -> bool:
    divides = [i for i in range(1, floor(sqrt(n))+1) if n %
               i == 0]
    divides += [n // i for i in divides if i != 1 and i * i != n]
    return sum(divides) == n

# print(is_perfect(36))
# print(is_perfect(28))


def drugie_imperatywna(n: int) -> list:
    res = []
    for i in range(2, n + 1):
        if is_perfect(i):
            res.append(i)
    return res


def drugie_skladana(n: int) -> list:
    return [i for i in range(2, n + 1) if is_perfect(i)]


def drugie_funkcyjna(n: int) -> list:
    return list(filter(is_perfect, range(2, n+1)))


print("Zadanie 2:")
compare_funcs(drugie_imperatywna, drugie_skladana,
              drugie_funkcyjna, [28, 100, 496, 700], numbers=2000)
