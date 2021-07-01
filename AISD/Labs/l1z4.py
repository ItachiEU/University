countWays = [0]*n
visited = [0]*n
distances = [0]*n
G = defaultdict(list())  # |V| + |E|


def prep(u, v):
    countWays[v] = 1
    visited[v] = 1

    dijsktra(distances, v)

    dfs(u)

    return countWays[u]


def dfs(v):
    visited[v] = true

    for neighbour of v:
        if dist[neighbour] < dist[v]:
            if visited[neighbour] != true:
                dfs(neighbour)
            countWays[v] += countWays[neighbour]
    return
