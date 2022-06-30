"""
hw: 2
jmeno: Kostík
učo: 469007
"""

from random import randint

def my_max(values):
    max_value=0
    for i in values:
        if max_value<i:
            max_value=i
    return max_value

def game(n):
    if n==1:
        print("Velikost hracího pole musí být větší než 1")
    else:
        finals=[0,0,0,0,0]
        while my_max(finals)<n:
            for i in range(5):
                dice=randint(1,6)+randint(1,6)+randint(1,6)
                x=n-finals[i]
                if dice==18:
                    finals[i]+=0
                elif dice>x:
                    finals[i]+=0
                elif dice<n:
                    finals[i]+=dice
        for p in range(5):
            for v in range(finals[p]-1):
                print("( )", end=" ")
            print("(X)", end=" ")
            for b in range(n-finals[p]):
                print("( )", end=" ")
            print()
        print(finals)

"""
dál jsem se nestihl dostat, protože jsem se zasekl u tohohle
občas to nevypíše nic, když n<10, ale jenom někdy, nevím proč
"""
