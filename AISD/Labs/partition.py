
def partition(t, l, r):
    pivot = t[r]
    i = l
    for j in range(l, r+1):
        print(j, t)
        if t[j] < pivot:
            t[i], t[j] = t[j], t[i]  # swap
            i += 1
    t[i], t[r] = t[r], t[i]
    return i


t = [6, 3, 1, 7, 0, 10, 2, 9, 4, 5]

print(partition(t, 0, 9))
print(t)
