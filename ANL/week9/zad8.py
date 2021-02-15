import matplotlib.pyplot as plt

from PIL import Image
from PIL import ImageDraw

xs = [39.5, 30, 6, 13, 63, 18.5, 48, 7, 48.5, 9, 48.5, 59, 56]
ys = [10.5, 20, 6, -12, -12.5, 17.5, 63, 25.5, 49.5, 19.5, 35.5, 32.5, 20.5]
W = [1, 2, 3, 2.5, 6, 1.5, 5, 1, 2, 1, 3, 5, 1]
ts = [i / 100 for i in range(101)]
out_xs, out_ys = [], []


def binomialCoefficient(n, k):
    if k < 0 or k > n:
        return 0
    if k == 0 or k == n:
        return 1
    k = min(k, n - k)
    c = 1
    for i in range(k):
        c = c * (n - i) / (i + 1)
    return c


def Bernstein(t, n, k):
    binom = binomialCoefficient(n, k)
    ans = binom * (t ** k) * ((1 - t) ** (n - k))

    return ans


def P(n, r):

    for t in [x / (r - 1) for x in range(0, r)]:
        num_x = 0
        for i in range(n + 1):
            num_x += xs[i] * W[i] * Bernstein(t, n, i)

        num_y = 0
        for i in range(n + 1):
            num_y += ys[i] * W[i] * Bernstein(t, n, i)

        den = 0
        for i in range(n + 1):
            den += W[i] * Bernstein(t, n, i)

        out_xs.append(num_x / den)
        out_ys.append(num_y / den)


n = 12
R = 301
P(n, R)

for i in range(len(xs)):
    if i == 11:
        plt.scatter(xs[i], ys[i], s=50)

# plt.plot(xs, ys, 'b.-')

for i in range(len(out_xs)):
    plt.scatter(out_xs[i], out_ys[i], s=3, c="red")

plt.show()
