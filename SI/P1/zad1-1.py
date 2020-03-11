from queue import Queue

try:
	fhandle = open("test.txt", 'r')
except:
	print("No such file.")
	exit()

pozycje = {'a': 1, 'b': 2, 'c':3, 'd': 4, 'e': 5, 'f': 6, 'g':7, 'h': 8}

q = Queue(0)

def check(state):
	#if rook and bk in the same row / column -> check
	if state[1][0] == state[2][0] or state[1][1] == state[2][1]:
		return True 
	return False

def legal_state(state):
	#check if inbound
	for i in range(3):
		if state[i][0] < 1 or state[i][0] > 8 or state[i][1] < 1 or state[i][1] > 8:
			return False
	#check if kings are neighbours
	if abs(state[0][0] - state[2][0]) <= 1 and abs(state[0][1] - state[2][1]) <= 1:
		return False
	if check(state) and state[3] =='white':
		return False
	if state[0][0] == state[1][0] and state[0][1] == state[1][1]:
		return False
	if state[0][0] == state[2][0] and state[0][1] == state[2][1]:
		return False
	return True

#print(legal_state([(6, 2), (1, 2), (6, 2), 'black']))

def possible_moves(figure, state):
	#rozwazyc reszte przypadkow
	#result = set ()
	if figure == 'wKing':
		pos = state[0]
		return [(pos[0]-1, pos[1]-1),(pos[0]-1, pos[1]),(pos[0]-1, pos[1]+1),(pos[0], pos[1]-1),(pos[0], pos[1]+1),(pos[0]+1, pos[1]-1),(pos[0]+1, pos[1]),(pos[0]+1, pos[1]+1)]
	if figure == 'wRook':
		result = set()
		for x in range(1,9):
			git = True
			curr_pos = state[1]
			pos = (x, curr_pos[1])

			if (pos[0] == state[2][0] and pos[1] < state[2][1] and state[1][1] > state[2][1]) or (pos[0] == state[2][0] and pos[1] > state[2][1] and state[1][1] < state[2][1]) or (pos[1] == state[2][1] and pos[0] < state[2][0] and state[1][0] > state[2][0]) or (pos[1] == state[2][1] and pos[0] > state[2][0] and state[1][0] < state[2][0]):
				git = False
			if (pos[0] == state[0][0] and pos[1] < state[0][1] and state[1][1] > state[0][1]) or (pos[0] == state[0][0] and pos[1] > state[0][1] and state[1][1] < state[0][1]) or (pos[1] == state[0][1] and pos[0] < state[0][0] and state[1][0] > state[0][0]) or (pos[1] == state[0][1] and pos[0] > state[0][0] and state[1][0] < state[0][0]):
				git = False
			if (x, curr_pos[1]) != curr_pos and git:
				result.add((x, curr_pos[1]))

			git = True
			pos = (curr_pos[0], x)
			if (pos[0] == state[2][0] and pos[1] < state[2][1] and state[1][1] > state[2][1]) or (pos[0] == state[2][0] and pos[1] > state[2][1] and state[1][1] < state[2][1]) or (pos[1] == state[2][1] and pos[0] < state[2][0] and state[1][0] > state[2][0]) or (pos[1] == state[2][1] and pos[0] > state[2][0] and state[1][0] < state[2][0]):
				git = False
			if (pos[0] == state[0][0] and pos[1] < state[0][1] and state[1][1] > state[0][1]) or (pos[0] == state[0][0] and pos[1] > state[0][1] and state[1][1] < state[0][1]) or (pos[1] == state[0][1] and pos[0] < state[0][0] and state[1][0] > state[0][0]) or (pos[1] == state[0][1] and pos[0] > state[0][0] and state[1][0] < state[0][0]):
				git = False
			if (curr_pos[0], x) != curr_pos and git:
				result.add((curr_pos[0], x))
		return result
	if figure == 'bKing':
		pos = state[2]
		return [(pos[0]-1, pos[1]-1),(pos[0]-1, pos[1]),(pos[0]-1, pos[1]+1),(pos[0], pos[1]-1),(pos[0], pos[1]+1),(pos[0]+1, pos[1]-1),(pos[0]+1, pos[1]),(pos[0]+1, pos[1]+1)]

ruchy = dict()

def get_path(ID):
	while ID != 0:
		print(ruchy[ID])
		ID = ruchy[ID][1]

def bfs(state):
	#state, id, father, moves, rook moves
	q.put([state, 0, 0, 0, 0])
	visited_states = set()
	ID = 0
	debug = 0
	checkmate = 0

	while not q.empty():
		curr_state, curr_id, curr_father, curr_moves, curr_rook = q.get()
		#print(curr_state, curr_moves)
		#print(curr_state)

		if legal_state(curr_state) and curr_rook <4:
			visited_states.add(tuple(curr_state))

			if debug == 1:
				ruchy[curr_id]  = (curr_state, curr_father)

			if curr_state[3] == 'white':
				#wk moves:
				moves = possible_moves('wKing', curr_state)
				
				for move in moves:
					if (move, curr_state[1], curr_state[2], 'black') not in visited_states:
						ID += 1
						q.put([[move, curr_state[1], curr_state[2], 'black'], ID, curr_id, curr_moves+1, curr_rook])
						
				#wr moves:
				moves = possible_moves('wRook', curr_state)

				for move in moves:
					if (curr_state[0], move, curr_state[2], 'black') not in visited_states:
						ID += 1
						q.put([[curr_state[0], move, curr_state[2], 'black'], ID, curr_id, curr_moves+1, curr_rook+1])
			else:
				#bk moves
				moves = possible_moves('bKing', curr_state)
				
				ruch = False
				for move in moves:
					if legal_state((curr_state[0], curr_state[1], move, 'white')):
						ruch = True
					if (curr_state[0], curr_state[1], move, 'white') not in visited_states:
						ID += 1
						q.put([[curr_state[0], curr_state[1], move, 'white'], ID, curr_id, curr_moves+1, curr_rook])
				if check(curr_state) and not ruch:
					if debug == 1:
						#print(curr_state)
						get_path(curr_id)
					return curr_moves

	return -1

result = ''

for line in fhandle:
	start, white_king, white_rook, black_king = line.split()
	# 0 - wKing, 1 - wRook, 2 - bKing, 3 - turn
	state = [(pozycje[white_king[0]], int(white_king[1])), (pozycje[white_rook[0]], int(white_rook[1])), (pozycje[black_king[0]], int(black_king[1])), start]
	#print(state)
	result += str(bfs(state)) + '\n'
	#print(bfs(state))

print(result)
try:
	out = open('zad1_output.txt', 'w')
except:
	print('przypal')
	exit()


out.write(result)
out.close()