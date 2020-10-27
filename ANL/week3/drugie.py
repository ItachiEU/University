from math import sqrt


def weak(a, b, c):
    return (-b + sqrt(b * b - 4 * a * c)) / (2 * a), (-b - sqrt(b * b - 4 * a * c)) / (2 * a)


def better(a, b, c):
    x1 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a)
    x2 = c / a * x1
    return (x1, x2)


print(weak(0.00000000042, 4200000000000, 0.00000000042))
print(better(0.00000000042, 4200000000000, 0.00000000042))
