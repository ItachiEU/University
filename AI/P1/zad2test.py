#zmienic na linijka po linijce 
try:
	fhandle = open("words_for_ai1.txt", 'r')
except:
	print("no such file")
	exit()

slownik = dict()

for line in fhandle:
	slownik[line.strip()] = slownik.get(line, 0) + 1

fhandle.close()

try:
	fhandle2 = open("pan_tadeusz_bez_spacji.txt", 'r')
except:
	print("no such file 2")
	exit()

text = ""
result = ''
for line in fhandle2:
	spaces = 0
	result_line = ''
	start = 0
	#przechodzimy przes spacje
	for char in line:
		if char == ' ' or char == '\t':
			start += 1
			spaces += 1
			result_line += ' '
			continue
		else:
			break

	text = line[start:len(line)]
	text = text.rstrip()

	dp = [0]*(len(text)+3)
	words = [0]*(len(text)+3)

	for i in range(len(text)+1):
		if i < 40:
			#print("sprawdzam:",text[0:i+1], i)
			if slownik.get(text[0:i+1], 0) == 1:
				#print("weszlo")
				dp[i] = (i+1)**2
				words[i] = i+1
		for j in range(i, max(-1, i-40), -1):
			#print(text[j:i+1], j, i+1)
			if slownik.get(text[j:i+1], 0) == 1 and dp[j-1] != 0:
				if dp[j-1] + (i-j+1)**2 > dp[i]:
					words[i] = i-j+1
				dp[i] = max(dp[i], dp[j-1]+(i-j+1)**2)

	i = len(text)-1

	res_temp = []

	while i >= 0:
		#print(text[i-words[i]+1:i+1])
		res_temp.append(text[i-words[i]+1:i+1])
		i -= words[i]

	res_temp.reverse()

	for word in res_temp:
		result_line += word + ' '
	result_line = result_line.rstrip()

	result += result_line + '\n'

print(result)

fhandle3 = open("zad2_output.txt", 'w')

fhandle3.write(result)

fhandle3.close()

