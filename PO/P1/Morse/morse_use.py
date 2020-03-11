from morse import code, decode

mode = input('Choose-> Code: 0, Decode: 1\n')

if mode == '0':
	text = input('Podaj text: ')
	print(code(text))
elif mode == '1':
	print('Oddziel znaki spacja, a słowa tabem.\n')
	text = input('Podaj text: ')
	print(decode(text))
else:
	print('Try again.')