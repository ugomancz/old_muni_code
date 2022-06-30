"""
FIFO
from collections import deque
queue = deque(list)
"""
from random import randint
from collections import deque

def flower(n):
    alist=[]
    for i in range(n):
        alist.append(randint(1,4))
    blist=deque(alist)
    return blist

def game(n):
    flist=[]
    for _ in range(n):
        flist.append(flower(4))
    final=deque(flist)
    print("seznam kytek", final)
    """
    for _ in range(n*n):
        templist=final.pop
        print("templist", templist)
        templist2=templist.popleft
        final.append(templist2)
    print(final)

    IDK
"""

"""
slovník - množina klíč:hodnota
points = {"jack":66, "Peter":50, "Dennis":78}

print(points[Jack]) vypise 66
points["Peter"]+=10 prida petrovi 10 bodu

test přislušnosti
if "sam" in points:
    print("sam has record")
else:
    print("No record for sam")
"""

morseAlphabet ={
        "A" : ".-",
        "B" : "-...",
        "C" : "-.-.",
        "D" : "-..",
        "E" : ".",
        "F" : "..-.",
        "G" : "--.",
        "H" : "....",
        "I" : "..",
        "J" : ".---",
        "K" : "-.-",
        "L" : ".-..",
        "M" : "--",
        "N" : "-.",
        "O" : "---",
        "P" : ".--.",
        "Q" : "--.-",
        "R" : ".-.",
        "S" : "...",
        "T" : "-",
        "U" : "..-",
        "V" : "...-",
        "W" : ".--",
        "X" : "-..-",
        "Y" : "-.--",
        "Z" : "--..",
        " " : "/"
        }

def encode(n):
    for i in range(len(n)):
        letter=n[i]
        print(morseAlphabet[letter], end=" ")

def decode(n):
    backward = {value:key for key, value in morseAlphabet.items()}
    for i in range(len(n)):
        pass
    #IDK

def sudokucheck(n):
    aset=(n)
    bset=(1,2,3,4,5,6,7,8,9)
    testset=aset-bset
    if len(testset)== 0:
        return True
    else:
        return False
