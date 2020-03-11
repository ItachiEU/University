morse = ['.-',	'-...',	'-.-.',	'-..','.','..-.','--.','....','..','.---','-.-','.-..','--','-.','---','.--.','--.-','.-.',	
	'...','-','..-','...-','.--','-..-','-.--','--..',	'-----','.----','..---','...--','....-','.....','-....','--...',
	'---..','----.']	

alf = list(map(chr, range(97, 123)))

liczby = [str(i) for i in range(0, 10)]
alf = alf + liczby

morsetoenglish = {kod:litera for kod, litera in zip(morse, alf)}

englishtomorse = {litera:kod for kod, litera in zip(morse, alf)}

def code(string):
	result = ''
	for char in string:
		if char == ' ':
			result+= '   '
			continue
		result += englishtomorse.get(char, 0) + ' '
	return result

def decode(string):
	znaki = string.split(' ')
	result = ''
	for znak in znaki:
			result += morsetoenglish.get(znak, 0)
	return result

