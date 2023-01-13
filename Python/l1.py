
# ZADANIE 1

from collections import defaultdict
from decimal import *


def vat_faktura(lista: list, is_decimal: bool = False):
    if is_decimal:
        return sum(lista) * Decimal('0.23')
    return sum(lista) * 0.23


def vat_paragon(lista: list, is_decimal: bool = False):
    if is_decimal:
        return sum([Decimal('0.23') * x for x in lista])
    return sum([0.23 * x for x in lista])


zakupy = [0.2, 0.5, 4.59, 6]
print(vat_faktura(zakupy), vat_paragon(zakupy))

zakupy_dec = [Decimal('0.2'), Decimal('0.5'), Decimal('4.59'), Decimal('6')]
print(vat_faktura(zakupy_dec, True), vat_paragon(zakupy_dec, True))

# ZADANIE 2


def is_palindrom(text: str):
    clean_txt = ''.join([c.lower() for c in text if c.isalpha()])
    return clean_txt == clean_txt[::-1]


print(is_palindrom('rotor'))
print(is_palindrom('oko'))
print(is_palindrom('Kobyła ma mały bok.'))
print(is_palindrom('Eine güldne, gute Tugend: Lüge nie!'))
print(is_palindrom('Míč omočím.'))
print(is_palindrom('Test'))


# ZADANIE 5


def find_longest_word(wordlist: list):
    return max([len(w) for w in wordlist])


def common_prefix(wordlist: list):
    l = find_longest_word(wordlist)
    wordlist = [w.lower() for w in wordlist]
    best_prefix = ''
    for i in range(l):
        prefix_count = defaultdict(int)
        for w in wordlist:
            if i > len(w):
                continue
            prefix_count[w[:i+1]] += 1
            if prefix_count[w[:i+1]] > 2:
                best_prefix = w[:i+1]
    return best_prefix


print(common_prefix(["Cyprian", "cyberotoman", "cynik", "ceniąc", "czule"]))
print(common_prefix(["Cyprian", "cyberotoman", "cynik",
                     "ceniąc", "czule", "cybi", "cybcybcyb"]))
