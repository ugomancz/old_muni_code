"""
cviko9
rekurze - volani funkce sebe sama
"""

from turtle import Turtle
paja=Turtle()


def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)


def nsd(a,b):       # nejvetsi spolecny delitel
    if b % a == 0:
        return a
    else:
        return nsd(b % a, a)


def screwing(n):        # sroubujeme zarovku, 1 otoceni -> print "twist"; n = pocet zavitu
    if n != 0:
        print("twist")
        return screwing(n-1)


def seriessum(n):
    if n == 0:
        return 0
    else:
        return n + seriessum(n-1)


def binarysearch(value,numbers):        # idk
    if numbers[len(numbers)//2] < value:
        pass


def tree(length):
    
