from queue import Queue
from collections import namedtuple

ruchy = []
situation = namedtuple('situation', ['turn', 'wk0', 'wk1', 'wr0', 'wr1', 'bk0', 'bk1'])
checkmate = False

def legalstate(state):
	#wk and wr
	if (state.wk0 == state.wr0) and (state.wk1 == state.wr1):
		return False
	#wk & bk
	if (abs(state.wk0 - state.bk0) <= 1) and (abs(state.wk1 - state.bk1) <= 1):
		return False
	for coord in state[1:]:
		if coord < 1 or coord > 8:
				return False
	return True

def check(state):
	#bk same row/columna as wr
	return bool((state.bk0 == state.wr0) ^ (state.bk1 == state.wr1))

def doublecheck(state):
	return bool(check(state) or not legalstate(state))

def allmoves(state, distance):
	moves = []
	if state[0] == 'white':
		#wk
		moves.append([state._replace(turn = 'black', wk0 = state.wk0 + 1), distance + 1])
		moves.append([state._replace(turn = 'black', wk0 = state.wk0 - 1), distance + 1])
		moves.append([state._replace(turn = 'black', wk1 = state.wk1 + 1), distance + 1])
		moves.append([state._replace(turn = 'black', wk1 = state.wk1 - 1), distance + 1])
		moves.append([state._replace(turn = 'black', wk0 = state.wk0 + 1, wk1 = state.wk1 + 1), distance + 1])
		moves.append([state._replace(turn = 'black', wk0 = state.wk0 - 1, wk1 = state.wk1 + 1), distance + 1])
		moves.append([state._replace(turn = 'black', wk0 = state.wk0 + 1, wk1 = state.wk1 - 1), distance + 1])
		moves.append([state._replace(turn = 'black', wk0 = state.wk0 - 1, wk1 = state.wk1 - 1), distance + 1])
		#wr
		for cord in range(state.wr1, 9):
			#check for collision
			if (((state.wr0 == state.bk0) and (state.bk1 == cord)) or (state.wr0 == state.wk0) and (state.wk1 == cord)):
				break
			moves.append([state._replace(turn = 'black', wr1 = cord), distance + 1])
		for cord in range(state.wr1,0,-1):
			if (((state.wr0 == state.bk0) and (state.bk1 == cord)) or (state.wr0 == state.wk0) and (state.wk1 == cord)):
				break
			moves.append([state._replace(turn = 'black', wr1 = cord), distance + 1])
		for cord in range(state.wr0, 9):
			if (((state.wr1 == state.bk1) and (state.bk0 == cord)) or (state.wr1 == state.wk1) and (state.wk0 == cord)):
				break
			moves.append([state._replace(turn = 'black', wr0 = cord), distance + 1])
		for cord in range(state.wr0,0,-1):
			if (((state.wr1 == state.bk1) and (state.bk0 == cord)) or (state.wr1 == state.wk1) and (state.wk0 == cord)):
				break
			moves.append([state._replace(turn = 'black', wr0 = cord), distance + 1])
	else:
		#bk
		marker = True
		if not doublecheck(state._replace(turn = 'white', bk0 = state.bk0 + 1)):
			moves.append([state._replace(turn = 'white', bk0 = state.bk0 + 1), distance + 1])
			marker = False
		if not doublecheck(state._replace(turn = 'white', bk0 = state.bk0 - 1)):
			moves.append([state._replace(turn = 'white', bk0 = state.bk0 - 1), distance + 1])
			marker = False
		if not doublecheck(state._replace(turn = 'white', bk1 = state.bk1 + 1)):
			moves.append([state._replace(turn = 'white', bk1 = state.bk1 + 1), distance + 1])
			marker = False
		if not doublecheck(state._replace(turn = 'white', bk1 = state.bk1 - 1)):
			moves.append([state._replace(turn = 'white', bk1 = state.bk1 - 1), distance + 1])
			marker = False
		if not doublecheck(state._replace(turn = 'white', bk0 = state.bk0 + 1, bk1 = state.bk1 + 1)):
			moves.append([state._replace(turn = 'white', bk0 = state.bk0 + 1, bk1 = state.bk1 + 1), distance + 1])
			marker = False
		if not doublecheck(state._replace(turn = 'white', bk0 = state.bk0 - 1, bk1 = state.bk1 + 1)):
			moves.append([state._replace(turn = 'white', bk0 = state.bk0 - 1, bk1 = state.bk1 + 1), distance + 1])
			marker = False
		if not doublecheck(state._replace(turn = 'white', bk0 = state.bk0 + 1, bk1 = state.bk1 - 1)):
			moves.append([state._replace(turn = 'white', bk0 = state.bk0 + 1, bk1 = state.bk1 - 1), distance + 1])
			marker = False
		if not doublecheck(state._replace(turn = 'white', bk0 = state.bk0 - 1, bk1 = state.bk1 - 1)):
			moves.append([state._replace(turn = 'white', bk0 = state.bk0 - 1, bk1 = state.bk1 - 1), distance + 1])
			marker = False
		if marker and check(state) and legalstate(state):
			#print('Tu ustawiam\n', state)
			global checkmate
			checkmate = True
	return moves

debug = False

def bfs(state):
	ID = 0
	q = Queue(0)
	visitedStates = set()
	#state,distance, id
	q.put([state, 0, 0]) 
	ruchy.append([state, -1])
	while not q.empty():
		curr_state = q.get()
		if (not curr_state[0] in visitedStates) and legalstate(curr_state[0]):
			visitedStates.add(curr_state[0])
			moves = allmoves(curr_state[0], curr_state[1])
			for move in moves:
				if (not move[0] in visitedStates) and legalstate(move[0]):
					ruchy.append([move[0], curr_state[2]])
					ID += 1
					q.put([move[0], move[1], ID])
			if checkmate:
				#tutaj wersja debug
				if debug:
					ind = curr_state[2]
					while ind != -1:
						print(ruchy[ind])
						ind = ruchy[ind][1]
				return curr_state[1]


fhandle = open('zad1_input.txt', 'r')

result = ''

for line in fhandle:
	start, white_king, white_rook, black_king = line.split()

	state = situation(start, ord(white_king[0]) - 96,int(white_king[1]), ord(white_rook[0]) - 96,int(white_rook[1]) , ord(black_king[0]) - 96,int(black_king[1]))

	result += str(bfs(state)) + '\n'

fhandle.close()

fhandle2 = open('zad1_output.txt', 'w')

fhandle2.write(result)