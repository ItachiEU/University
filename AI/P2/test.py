def bfs(pozycja):
    # tu trzeba jeszcze temporary ustawic globalne visited na startowej pozycji
    visited[pozycja[0]][pozycja[1]] = 1
    # ========
    q = collections.deque()
    vis = set()
    q.append(pozycja)
    while len(q) > 0:
        v = q.popleft()
        if v[0] - 1 >= 0 and board[v[0]-1][v[1]] == 0 and visited[v[0]-1][v[1]] == 0:
            q.append((v[0]-1, v[1]))
            vis.add((v[0]-1, v[1]))
        if v[0] + 1 < height and board[v[0]+1][v[1]] == 0 and visited[v[0]+1][v[1]] == 0:
            q.append((v[0]+1, v[1]))
            vis.add((v[0]+1, v[1]))
        if v[1] - 1 >= 0 and board[v[0]][v[1]-1] == 0 and visited[v[0]][v[1]-1] == 0:
            q.append((v[0], v[1]-1))
            vis.add((v[0], v[1]-1))
        if v[1] + 1 < width and board[v[0]][v[1]+1] == 0 and visited[v[0]][v[1]+1] == 0:
            q.append((v[0], v[1]+1))
            vis.add((v[0], v[1]+1))
    # USTAWIAM SPOWROTEM NA 0
    visited[pozycja[0]][pozycja[1]] = 0
    return len(vis)
