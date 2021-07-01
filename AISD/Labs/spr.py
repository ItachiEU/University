import os

name = "aisd21c1"

for znak in range(ord('a'), ord('k')):
    str = f"./zad3nomap < C_tests/{name}{chr(znak)}.inp > {chr(znak)}.out"
    os.system(str)
    if not os.system(f"diff -b {chr(znak)}.out C_tests/{name}{chr(znak)}.out"):
        print(f"ok {chr(znak)}")
