def exponentMod(A, B, C): 
    if (A == 0): 
        return 0
    if (B == 0): 
        return 1
    y = 0
    if (B % 2 == 0): 
        y = exponentMod(A, B / 2, C) % C
        y = (y * y) % C 
    else: 
        y = A % C 
        y = (y * exponentMod(A, B - 1, C) % C) % C 
    return ((y + C) % C) 
  
t = input()
t = int(t)
for i in range(t):

    n, k, m = input().split()
    n = int(n)
    k = int(k)
    m = int(m)
    print(exponentMod(k,n,m))
