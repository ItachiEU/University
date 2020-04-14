#źle zinterpretowałem treść zadania

import random
import time

def correct(in_use, pos, queen, size):
	for i in range(size):
		good = True
		for used in in_use:
			#tu porownuje nowego hetmana z juz uzywanymi
			if i == pos[used][1] or (abs(pos[used][0]-queen) == abs(pos[used][1] - i)):
				good = False
				break
		if good:
			return (queen, i)
	return -1

def solve(queens, restart=True):
	size = len(queens)
	pos = dict()
	in_use = []
	while len(queens) > 0:
		#print(queens)
		queen = random.choice(queens)
		queens.remove(queen)
		new_pos = correct(in_use, pos, queen, size)
		if new_pos == -1:
			queens = [i for i in range(size)]
			if restart == True:
				solve(queens, restart=True)
			else:
				return 0
		else:
			pos[queen] = new_pos
			in_use.append(queen)
	return 1


#First task - 6 Queens no restart - probability
def first_task():
	queens = [index for index in range(6)]
	sample = 1000000
	solved = 0
	for i in range(sample):
		solved += solve(queens, restart=False)
		queens = [index for index in range(6)]
	print(solved)
	print(solved/sample) # przy sample == 1000000 szanse wynosza (kolejne odpalenia) -> 0.500451, 0.500092, 0.500494

#first_task()

#second task
def second_task(): #najwiecej ile udało mi się ułozyc ponizej 5 sekund to 623
	result = 0
	elapsed = 0.0
	for i in range(300,1000):
		test = [number for number in range(i)]
		start = time.time()
		solve(test, restart=True)
		end = time.time()	
		if (end - start) < 5.0:
			result = i
			elapsed = (end - start)
			print(result)
		else:
			print(end - start)
	print(result)
	print(elapsed)

first_task()