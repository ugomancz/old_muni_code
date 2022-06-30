"""
vnitro 1
kostík, 469007
1.11.2017
"""
import math
from turtle import Turtle
paja=Turtle()

def numbers(n):
    a=1
    for i in range(n):
        print(a)
        a=3*a-1

def table(size):
    list=[]
    for g in range(size):
        for l in range(size):
            list.append(l+1)
    for i in range(size):
        for x in range(size):
            print(list[x+i], end=" ")
        print()

def eleven(n):
    list=[int(d) for d in str(n)]
    x=0
    y=1
    sigh=len(list)/2
    for i in range(sigh):
        result+=list[x]
        x+=2
    for b in range(sigh):
        result-=list[y]
        y+=2
    if result%11==0:
        return True
    else:
        return False
"""
nestihl jsem zprovoznit
"""

def mill(size,width):
    if width>size:
        print("can´t be done")
    else:
        angle=math.degrees(math.tan((width/2)/size))*16/8
        print(angle)
        side=math.sqrt(size**2+(width/2)**2)
        print(side)
        for i in range(4):
            paja.left(angle/2)
            paja.forward(side)
            paja.right(angle/2+90)
            paja.forward(width)
            paja.right(angle/2+90)
            paja.forward(side)
            paja.left(90+angle/2)
"""
kreslí to trošku něco jiného, někde ve výpočtech mám chybu a jakmile width>size,
tak to taky vykreslilo nějakou hloupost
"""
