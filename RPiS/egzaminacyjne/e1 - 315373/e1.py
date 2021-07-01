import math as m

pi = m.pi


def doubleSilnia(n):
    if n == 0 or n == 1:
        return 1
    return n * doubleSilnia(n-2)


def Silnia(n):
    if n == 1 or n == 0:
        return 1
    return n * Silnia(n-1)


def tStudent(k, t):
    licznik = 1
    mianownik = 1
    if k % 2 == 1:
        licznik = Silnia((k+1)/2 - 1)
        mianownik = pow(k*pi*pi, 1/2) * doubleSilnia(k-2) / pow(2, (k-1)/2)
    else:
        licznik = doubleSilnia(k - 1)/pow(2, k/2)
        mianownik *= pow(k, 1/2)*Silnia(k/2 - 1)

    ulamek = licznik / mianownik

    def f(x):
        return ulamek * pow(1 + x**2/k, -(k+1)/2)

    def trapezy(n):
        result = 0
        h = abs(t) / n
        for i in range(n):
            x = i * h
            result += h * (f(x) + f(x + h))/2
        if t < 0:
            return 0.5 - result
        return result + 0.5

    def romberg(n):
        h = [0]*(n+1)
        r = [[0]*(n+1) for i in range(n+1)]
        for i in range(1, n + 1):
            h[i] = abs(t) / pow(2, i-1)

        r[1][1] = h[1] / 2 * (f(0) + f(t))

        for i in range(2, n + 1):
            wsp = 0
            for j in range(1, pow(2, i-2) + 1):
                wsp += f((2*j - 1) * h[i])
            r[i][1] = 0.5 * (r[i-1][1] + h[i-1] * wsp)

        for i in range(2, n+1):
            for j in range(2, i+1):
                r[i][j] = r[i][j-1] + (r[i][j-1]-r[i-1][j-1]) / (pow(4, j-1)-1)

        if t < 0:
            return 0.5 - r[n][n]
        return r[n][n] + 0.5

    for i in range(4, 12):
        n = pow(2, i)

        print(f"Wynik dla trapezów: {trapezy(n)} przy {n} punktach.")

        print(f"Wynik dla romberga: {romberg(i)} przy {n} punktach.")

        print("------------------------------------------------------")


print("Dla k = 3 i t = 0.25:")
tStudent(3, 0.25)
