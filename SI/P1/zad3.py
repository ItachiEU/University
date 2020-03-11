import random

figury = ['Ace', 'King', 'Queen', 'Jack']
bloty = ['2', '3', '4', '5', '6', '7', '8', '9', '10']
kolory = ['Hearts', 'Diamonds', 'Spades', 'Clubs']

deckF = [(f, k) for f in figury for k in kolory]
random.shuffle(deckF)

winDeckB = [('6', 'Spades'), ('7', 'Spades'), ('8', 'Spades'), ('9', 'Spades'), ('10', 'Spades')]

deckB = [(b, k) for b in bloty for k in kolory] #basic deck, wygrywa ~0.085
random.shuffle(deckB)

deckB1 = [(b, k) for b in bloty[:5] for k in kolory] #czesciej wygrywa (wywalilem 5 figur) ~0.28

deckB2 = [(b, k) for b in bloty for k in kolory[0:3]] # ~0.7 bez jednego koloru

deckB3 = deckB.copy()

for i in range(10):
	deckB3.remove(random.choice(deckB3)) # przy usuwaniu losowych kart nie widac zadnej zaleznosci
 

def restore_cards(hand, deck):
	for card in hand:
		deck.append(card)

def generate_hand(deck):
	hand = [None]*5
	for i in range(5):
		hand[i] = random.choice(deck)
		deck.remove(hand[i])
	restore_cards(hand, deck)
	return hand


def pair(hand):
	count = 0
	t = dict()
	for card in hand:
		t[card[0]] = t.get(card[0], 0) + 1
	for key in t.keys():
		if t.get(key,0) == 2:
			count +=1
	if count == 1:
		return 'pair'
	if count == 2:
		return 'two pairs'
	return False

def three_four(hand):
	t = dict()
	for card in hand:
		t[card[0]] = t.get(card[0], 0) + 1
	for key in t.keys():
		if t.get(key, 0) == 3:
			return 'three'
		if t.get(key, 0) == 4:
			return 'four'
	return False

def flush(hand):
	t = dict()
	for card in hand:
		t[card[1]] = t.get(card[1], 0) + 1
	for key in t.keys():
		if t.get(key) == 5:
			return 'flush'
	return False

def straight(hand):
	if hand[0][0].isdecimal():
		hand.sort(key = lambda tup: int(tup[0]))
		for i in range(len(hand)-1):
			if int(hand[i][0])+1 != int(hand[i+1][0]):
				return False
		if flush(hand) == 'flush':
			return 'straight flush'
		return 'straight'
	else:
		return False
	print(hand)

def full(hand):
	if pair(hand) == 'pair' and three_four(hand) == 'three':
		return 'full'
	return False

strength = {False: 0, 'pair': 1, 'two pairs': 2, 'three': 3, 'straight': 4, 'flush': 5, 'full': 6, 'four':7, 'straight flush': 8}


def find_strength(hand):
	power = strength[False]
	if strength[straight(hand)] > power:
		power = strength[straight(hand)]
	if strength[three_four(hand)] > power:
		power = strength[three_four(hand)]
	if strength[full(hand)] > power:
		power = strength[full(hand)]
	if strength[flush(hand)] > power:
		power = strength[flush(hand)]
	if strength[pair(hand)] > power:
		power = strength[pair(hand)]
	return power

bWins = 0
games = 10000

for i in range(games):

	hand1 = generate_hand(deckF)
	hand2 = generate_hand(deckB)

	power1 = find_strength(hand1)
	power2 = find_strength(hand2)

	if power2 > power1:
		bWins += 1

print(bWins/games)