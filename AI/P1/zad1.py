from queue import Queue

try:
	fhandle = open("test.txt", 'r')
except:
	print("No such file.")
	exit()

pozycje = {'a': 1, 'b': 2, 'c':3, 'd': 4, 'e': 5, 'f': 6, 'g':7, 'h': 8}

q = Queue(0)

def mate(state):
	#print(state)
	wKingPos = state['wKing']
	bKingPos = state['bKing']
	wRookPos = state['wRook']
	distK = (wKingPos[0] - bKingPos[0])**2 + (wKingPos[1] - bKingPos[1])**2
	#left wall
	if bKingPos[0] == 1 and distK == 4 and wRookPos[0] == 1:
		return True
	#right wall
	if bKingPos[0] == 8 and distK == 4 and wRookPos[0] == 8:
		return True 
	#ceiling
	if bKingPos[1] == 8 and distK == 4 and wRookPos[1] == 8:
		return True
	#floor 
	if bKingPos[1] == 1 and distK == 4 and wRookPos[1] == 1:
		return True
	return False

def is_empty(state, pos):
	figury = ['wKing', 'wRook', 'bKing']
	for figura in figury:
		if state[figura] == pos:
			return False 
	return True

def inbound(pos):
	if pos[0] >=1 and pos[0] <=8 and pos[1] >=1 and pos[1] <=8:
		return True
	return False

def legal(pos, state, figure):
	if not is_empty(state, pos):
		return False
	if figure == 'wRook':
		#trying to improve the speed by forcing rook to check every turn
		#if pos[0] != state['bKing'][0] and pos[1] != state['bKing'][1]:
		#	return False
		#checking collision
		if (pos[0] == state['bKing'][0] and pos[1] < state['bKing'][1] and state['wRook'][1] > state['bKing'][1]) or (pos[0] == state['bKing'][0] and pos[1] > state['bKing'][1] and state['wRook'][1] < state['bKing'][1]) or (pos[1] == state['bKing'][1] and pos[0] < state['bKing'][0] and state['wRook'][0] > state['bKing'][0]) or (pos[1] == state['bKing'][1] and pos[0] > state['bKing'][0] and state['wRook'][0] < state['bKing'][0]):
			return False
		if (pos[0] == state['wKing'][0] and pos[1] < state['wKing'][1] and state['wRook'][1] > state['wKing'][1]) or (pos[0] == state['wKing'][0] and pos[1] > state['wKing'][1] and state['wRook'][1] < state['wKing'][1]) or (pos[1] == state['wKing'][1] and pos[0] < state['wKing'][0] and state['wRook'][0] > state['wKing'][0]) or (pos[1] == state['wKing'][1] and pos[0] > state['wKing'][0] and state['wRook'][0] < state['wKing'][0]):
			return False
		#checking if at least one field away from bKing
		dist = (pos[0] - state['bKing'][0])**2 + (pos[1] - state['bKing'][1])**2
		if dist == 1:
			return False
		return True
	if figure == 'wKing':
		posB = state['bKing']
		dist = (pos[0] - posB[0])**2 + (pos[1] - posB[1])**2
		if dist >= 4:
			return True
		return False
	if figure == 'bKing':
		posW = state['wKing']
		dist = (pos[0] - posW[0])**2 + (pos[1] - posW[1])**2
		if dist >= 4 and pos[0] != state['wRook'][0] and pos[1] != state['wRook'][1]:
			return True
		return False
 
def kingSurroundings(pos):
	return [(pos[0]-1, pos[1]-1),(pos[0]-1, pos[1]),(pos[0]-1, pos[1]+1),(pos[0], pos[1]-1),(pos[0], pos[1]+1),(pos[0]+1, pos[1]-1),(pos[0]+1, pos[1]),(pos[0]+1, pos[1]+1)]

def rookSurroundings(pos):
	result = []
	for x in range(1,9):
			if (x, pos[1]) != pos:
				result.append((x,pos[1]))
			if (pos[0], x) != pos:
				result.append((pos[0], x))
	return result

def possible_moves(state, figure):
	if state['turn'] == 'white' and figure == 'bKing':
		return []
	if state['turn'] == 'black' and figure != 'bKing':
		return []
	#rozwazyc reszte przypadkow
	result = []
	if figure == 'wKing':
		curr_pos = state['wKing']
		candidates = kingSurroundings(curr_pos)
		for candidate in candidates:
			#need to check not only if inbound but also if legal
			if inbound(candidate) and legal(candidate, state, 'wKing'):
				result.append(candidate)
		return result
	if figure == 'wRook':
		curr_pos = state['wRook']
		candidates = rookSurroundings(curr_pos)
		for candidate in candidates:
			#need to check not only if inbound but also if legal
			if inbound(candidate) and legal(candidate, state, 'wRook'):
				result.append(candidate)
		return result
	if figure == 'bKing':
		curr_pos = state['bKing']
		candidates = kingSurroundings(curr_pos)
		for candidate in candidates:
			#need to check not only if inbound but also if legal
			if inbound(candidate) and legal(candidate, state, 'bKing'):
				result.append(candidate)
		return result


def switch_turn(turn):
	if turn == 'white':
		return 'black'
	return 'white'

def bfs(state):
	q.put(state)
	visited_states = set()

	while not q.empty():
		curr_state = q.get()
		visited_states.add(tuple(curr_state))
		
		if mate(curr_state):
			return curr_state['moves']

		#Adding possible moves of white King
		wKingMoves = possible_moves(curr_state, 'wKing')
		for move in wKingMoves:
			next_state = curr_state.copy()
			next_state['wKing'] = move
			next_state['moves'] = next_state.get('moves', 0) + 1
			next_state['turn'] = switch_turn(next_state.get('turn', None))
			tup = []
			for key in next_state.keys():
				tup.append(next_state[key])
			if not tuple(tup) in visited_states:
				q.put(next_state)

		#Adding possible moves of white Rook
		wRookMoves = possible_moves(curr_state, 'wRook')
		for move in wRookMoves:
			next_state = curr_state.copy()
			next_state['wRook'] = move
			next_state['moves'] = next_state.get('moves', 0) + 1
			next_state['turn'] = switch_turn(next_state.get('turn', None))
			tup = []
			for key in next_state.keys():
				tup.append(next_state[key])
			if not tuple(tup) in visited_states:
				q.put(next_state)

		#Adding possible moves of black King
		bKingMoves = possible_moves(curr_state, 'bKing')
		for move in bKingMoves:
			next_state = curr_state.copy()
			next_state['bKing'] = move
			next_state['moves'] = next_state.get('moves', 0) + 1
			next_state['turn'] = switch_turn(next_state.get('turn', None))
			tup = []
			for key in next_state.keys():
				tup.append(next_state[key])
			if not tuple(tup) in visited_states:
				q.put(next_state)

	return -1


for line in fhandle:
	start, white_king, white_rook, black_king = line.split()

	state = {'wKing': (pozycje[white_king[0]], int(white_king[1])), 'wRook': (pozycje[white_rook[0]], int(white_rook[1])), 'bKing': (pozycje[black_king[0]], int(black_king[1])), 'turn': start, 'moves': 0}



	print(bfs(state))
