import random

fhandle = open('zad5_input.txt', 'r')
count = 0

rows, columns = 0, 0
rows_description = []
columns_description = []

for line in fhandle:
	if count == 0:
		rows, columns = line.split(' ')
		rows = int(rows)
		columns = int(columns)
	elif count <= rows:
		rows_description.append(int(line))
	else:
		columns_description.append(int(line))
	count += 1

#mapa
obrazek_rows = []
obrazek_columns = []

#pomocnicze tablice mowiace, ktore wiersze/kolumny wymagaja jeszcze zmian
change_rows = set()
change_columns = set()
for i in range(columns):
	obrazek_rows.append(['.']*columns)
	if rows_description[i] != 0:
		change_rows.add(i)
for i in range(rows):
	obrazek_columns.append(['.']*rows)
	if columns_description[i] != 0:
		change_columns.add(i)

count = 0

def flip(a):
	if a == '.':
		return '#'
	return '.'

def opt_dist(a, b):
	b = int(b)
	suma = a.count('#')
	if b == 0:
		return suma
	result = b + 1
	for i in range(len(a) - b+1):
		result = min(result, b - a[i:i+b].count('#') + a[i+b:].count('#') + a[:i].count('#'))
	return result

#main
def solve():
	count = 0
	while (len(change_rows)+len(change_columns)) > 0 and count < 100:
		if len(change_rows) > 0:
			zmiana = random.choice(tuple(change_rows))
			max_improvement = -10000
			index = -1
			for i in range(columns):
				row_curr = opt_dist(obrazek_rows[zmiana], rows_description[zmiana])
				column_curr = opt_dist(obrazek_columns[i], columns_description[i])
				row_change = opt_dist(obrazek_rows[zmiana][:i]+[flip(obrazek_rows[zmiana][i])]+obrazek_rows[zmiana][i+1:], rows_description[zmiana])
				column_change = opt_dist(obrazek_columns[i][:zmiana]+[flip(obrazek_columns[i][zmiana])]+obrazek_columns[i][zmiana+1:], columns_description[i])
				if row_curr + column_curr - row_change - column_change > max_improvement:
					max_improvement = row_curr + column_curr - row_change - column_change
					index = i
			obrazek_rows[zmiana][index] = flip(obrazek_rows[zmiana][index])
			obrazek_columns[index][zmiana] = flip(obrazek_columns[index][zmiana])

			dist_row = opt_dist(obrazek_rows[zmiana], rows_description[zmiana])
			if  dist_row == 0:
				if zmiana in change_rows:
					change_rows.remove(zmiana)
			if dist_row != 0 and (zmiana not in change_rows):
				change_rows.add(zmiana)

			dist_column = opt_dist(obrazek_columns[index], columns_description[index])
			if dist_column == 0:
				if index in change_columns:
					change_columns.remove(index)
			if dist_column != 0 and (index not in change_columns):
				change_columns.add(index)

		elif len(change_columns) > 0:
			i = random.choice(tuple(change_columns))
			max_improvement = -10000
			index = -1
			for zmiana in range(rows):
				row_curr = opt_dist(obrazek_rows[zmiana], rows_description[zmiana])
				column_curr = opt_dist(obrazek_columns[i], columns_description[i])
				row_change = opt_dist(obrazek_rows[zmiana][:i]+[flip(obrazek_rows[zmiana][i])]+obrazek_rows[zmiana][i+1:], rows_description[zmiana])
				column_change = opt_dist(obrazek_columns[i][:zmiana]+[flip(obrazek_columns[i][zmiana])]+obrazek_columns[i][zmiana+1:], columns_description[i])
				if row_curr + column_curr - row_change - column_change > max_improvement:
					max_improvement = row_curr + column_curr - row_change - column_change
					index = zmiana
			obrazek_rows[index][i] = flip(obrazek_rows[index][i])
			obrazek_columns[i][index] = flip(obrazek_columns[i][index])

			dist_row = opt_dist(obrazek_rows[index], rows_description[index])
			if dist_row == 0:
				if index in change_rows:
					change_rows.remove(index)
			if dist_row != 0 and (index not in change_rows):
				change_rows.add(index)

			dist_column = opt_dist(obrazek_columns[i], columns_description[i])
			if dist_column == 0:
				if i in change_columns:
					change_columns.remove(i)
			if dist_column != 0 and (i not in change_columns):
				change_columns.add(i)

		count += 1

	if count == 100:
		return False
	return True

while not solve():
	#change map here
	#mapa
	obrazek_rows = []
	obrazek_columns = []

	#pomocnicze tablice mowiace, ktore wiersze/kolumny wymagaja jeszcze zmian
	rand = ['.', '#']
	change_rows = set()
	change_columns = set()
	for i in range(columns):
		temp = []
		for v in range(columns):
			temp.append(random.choice(rand))
		obrazek_rows.append(temp)
		if opt_dist(obrazek_rows[i], rows_description[i]) != 0:
			change_rows.add(i)
	for i in range(rows):
		temp = []
		for v in range(rows):
			temp.append(obrazek_rows[v][i])
		obrazek_columns.append(temp)
		if opt_dist(obrazek_columns[i], columns_description[i]) != 0:
			change_columns.add(i)

result = ''
for row in obrazek_rows:
	for char in row:
		result += char
	result += '\n'

#print(result)


fhandle2 = open("zad5_output.txt", 'w')
fhandle2.write(result)
fhandle2.close()
