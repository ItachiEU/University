from queue import Queue

q = Queue(0)

G = {}
visited = [0]*64

def graph_build(n):
	for i in range(n):
		a, b  = input().split()
		a = int(a)
		b = int(b)
		if G.get(a, 0) == 0:
			G[a] = [b]
		else:
			G[a].append(b)
		

def bfs(start):
	q.put(start)

	while not q.empty():
		v = q.get()
		print(v)
		visited[v] = 1
		if G.get(v, 0) != 0: 
			for i in range(len(G[v])):
				if visited[G[v][i]] == 0:
					q.put(G[v][i])

n = int(input())

graph_build(n)

bfs(1)
