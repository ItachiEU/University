import math as m
import numpy as np


def cube(x):
    if x >= 0:
        return x**(1/3)
    elif x < 0:
        return -(abs(x)**(1/3))


def cardano(q, r):
    return cube(r + m.sqrt(q ** 3 + r ** 2)) + cube(r - m.sqrt(q ** 3 + r ** 2))


def cardano_better(q, r):
    if r > q:
        return cube(r + m.sqrt(q ** 3 + r ** 2)) + cube((- q ** 3) / (r + m.sqrt(q ** 3 + r ** 2)))
    else:
        return (2 * r) / (cube((r + m.sqrt(q ** 3 + r ** 2)) ** 2) + q + ((q ** 2) / cube((r + m.sqrt(q ** 3 + r ** 2)) ** 2)))


print(cardano(pow(10, 6), pow(10, - 10)))
print(cardano_better(pow(10, 6), pow(10, -10)))
