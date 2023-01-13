from curses.ascii import isalnum, isalpha
import random
import re

# Zadanie 2


def pierwiastek(n: int) -> int:
    res, sum = 0, 0
    while (sum + (2*res + 1)) <= n:
        res += 1
        sum += (2*res - 1)
    return res


assert pierwiastek(16) == 4
assert pierwiastek(18) == 4
assert pierwiastek(25) == 5
assert pierwiastek(30) == 5
assert pierwiastek(81) == 9
assert pierwiastek(99) == 9
assert pierwiastek(100) == 10

# Zadanie 4


def uprosc_zdanie(tekst: str, dl_slowa: int, liczba_slow: int) -> str:
    words = tekst.split(' ')
    words_filtered = [w for w in words if len(w) <= dl_slowa]
    while len(words_filtered) > liczba_slow:
        words_filtered.pop(random.randrange(len(words_filtered)))

    return ' '.join(words_filtered)


tekst = "Podział peryklinalny inicjałów wrzecionowatych \
kambium charakteryzuje się ścianą podziałową inicjowaną \
w płaszczyźnie maksymalnej."

print(uprosc_zdanie(tekst, 10, 5))
print(uprosc_zdanie(tekst, 10, 5))
print(uprosc_zdanie(tekst, 10, 5))
print(uprosc_zdanie(tekst, 10, 5))

# Zadanie 5


def kompresja(tekst: str) -> str:
    res = tekst[0]
    count = 1
    for i in range(len(tekst)-1):
        if(tekst[i] == tekst[i+1]):
            count += 1
        else:
            if count > 1:
                res += f'{count}'
            res += tekst[i+1]
            count = 1
    if count > 1:
        res += f'{count}'
    return res


test = kompresja('aaa"aaa')


def dekompresja(tekst: str) -> str:
    res = ''
    for (char, num, single_nondigit) in re.findall(r'([a-zA-Z])([0-9]+)|(\D)', tekst):
        if num:
            res += char * int(num)
        else:
            res += single_nondigit
    return res


print(test)
print(dekompresja(test))
print('a4bxc3')
print(dekompresja('a4bxc3'))

with open('test.txt', 'r') as f:
    compressed = kompresja(f.read())
    print('Compressed: \n', compressed)
    decompressed = dekompresja(compressed)
    print('Decompressed: \n', decompressed)
