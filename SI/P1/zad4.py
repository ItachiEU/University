#!/usr/bin/env python3

try:
	fhandle = open('zad4_input.txt', 'r')
except:
	print('No such file.')
	exit()


def opt_dist(a, b):
	b = int(b)
	suma = a.count('1')
	if b == 0:
		return suma
	result = b + 1
	for i in range(len(a) - b+1):
		result = min(result, b - a[i:i+b].count('1') + a[i+b:].count('1') + a[:i].count('1'))
	return result

wynik = ''

for line in fhandle:
	a, b = line.split()
	wynik += str(opt_dist(a, b)) + '\n'

fhandle.close()

try:
	fhandle2 = open('zad4_output.txt', 'w')
except:
	print("Failed to open file")
	exit()

fhandle2.write(wynik)

fhandle2.close()