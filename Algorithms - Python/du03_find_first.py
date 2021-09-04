#!/usr/bin/env python3

from typing import List

# Povolene knihovny: typing, math
# (Poznamka: "povolene" neznamena "nutne"; ukol je mozno snadno vyresit i bez
#  jakychkoli knihoven.)

# IB002 Domaci uloha 3.
#
# Vasi ulohou bude s vyuzitim principu binarniho vyhledavani implementovat
# dve funkce, find_first_occurrence a find_first_greater. V obou pripadech
# musi casova slozitost vaseho algoritmu byt nejhure logaritmicka, tedy byt
# v O(log n). (Pozor, iterovani v poli a slicing a[x:y] ma linearni slozitost.)
# Funkce nesmi modifikovat vstupni pole.


# Ukol 1.
# Implementujte funkci find_first_occurrence, ktera vrati index prvniho
# vyskytu prvku key v serazenem poli numbers. Pokud se prvek v poli
# nevyskytuje, vrati -1.
#
# Priklady vstupu a vystupu:
# find_first_occurrence(2, [1, 2, 2, 2, 4]) -->  1
# find_first_occurrence(3, [1, 2, 4, 5])    --> -1
"""
Řešení zkopírováno z předchozího roku, po pár neúspěšných pokusech mě to nebavilo řešit :|
"""

def find_first_occurrence(key: int, numbers: List[int]) -> int:
    """
    vstup: 'key' hodnota hledaneho cisla, 'numbers' serazene pole cisel
    vystup: index prvniho vyskytu hodnoty 'key' v poli 'numbers',
            -1, pokud se tam tato hodnota nevyskytuje
    casova slozitost: O(log n), kde 'n' je pocet prvku pole 'numbers'
    """
    left = 0
    right = len(numbers) - 1
    if len(numbers) == 0:
            return -1
    while True:
        middle = (left+right)//2
        if left == right:
            if key == numbers[left]:
                return left
            else:
                return -1
        elif key > numbers[middle]:
            left = middle + 1
        else:
            right = middle


# Ukol 2.
# Implementujte funkci find_first_greater modifikaci predchozi funkce
# find_first_occurrence tak, ze find_first_greater vrati index prvniho prvku
# v poli vetsiho nez key. Neni-li v poli zadny takovy, vrati -1.
#
# Priklady vstupu a vystupu:
# find_first_greater(2, [1, 2, 4, 5]) -->  2
# find_first_greater(3, [1, 2, 4, 5]) -->  2
# find_first_greater(3, [1, 2, 3])    --> -1

def find_first_greater(key: int, numbers: List[int]) -> int:
    """
    vstup: 'key' hodnota hledaneho cisla, 'numbers' serazene pole cisel
    vystup: index prvniho vyskytu prvku vetsiho nez hodnota 'key',
            -1, pokud tam zadny takovy prvek neni
    casova slozitost: O(log n), kde 'n' je pocet prvku pole 'numbers'
    """
    left = 0
    right = len(numbers) - 1
    if len(numbers) == 0:
        return -1
    while True:
        if left == right:
            if key < numbers[left]:
                return left
            else:
                return -1
        middle = (left+right)//2
        if key >= numbers[middle]:
            left = middle + 1
        else:
            right = middle


# list1 = [1]
# list2 = [0,1]
# list3 = [1,2,2,3,3,4,4,5]
# list4 = [1,2,2,3,4,5,6,6,7]
# list5 = [1,2,2,3,3,3,4,4,4,5]
# list6 = [1,1,1,2,2,2,3,3,3,4,4,4,5]
# lleft = [3,4,5,6,7]
# lright = [1,2,3]
# lright1 = [1,2,3,4]
# lright2 = [1,3,4]
# lright3 = [1,2,3,3,4]
# lright4 = [1,3,3,4]
# l3 = [3,3,3,3]
# lleft1 = [1,3,3,4,5,6]
# lleft2 = [1,3,3,4,5,6,7]
# lleft3 = [1,3,4,5,6]
# lleft4 = [1,3,4,5,6,7]
# lempty = []
# list7 = [0, 0, 0, 0, 1, 1, 1, 1]

# print("be 0:" ,find_first_occurrence(1,list1))
# print("be 4:" ,find_first_occurrence(1,list7))
# print("be 0:" ,find_first_occurrence(0,list7))
# print("be 1:" ,find_first_occurrence(1,list2))
# print("be -1:" ,find_first_occurrence(2,list2))
# print("be 0:" ,find_first_occurrence(3,l3))
# print("be 0:" ,find_first_occurrence(3,lleft))
# print("be 1:" ,find_first_occurrence(3,lleft1))
# print("be 1:" ,find_first_occurrence(3,lleft2))
# print("be 1:" ,find_first_occurrence(3,lleft3))
# print("be 1:" ,find_first_occurrence(3,lleft4))
# print("be -1:" ,find_first_occurrence(-3,list1))
# print("be -1:" ,find_first_occurrence(-3,list2))
# print("be 3:" ,find_first_occurrence(3,list5))
# print("be 9:" ,find_first_occurrence(4,list6))
# print("be -1:" ,find_first_occurrence(-3,lempty))
# print("be 2:" ,find_first_occurrence(3,lright))
# print("be 2:" ,find_first_occurrence(3,lright1))
# print("be 1:" ,find_first_occurrence(3,lright2))
# print("be 2:" ,find_first_occurrence(3,lright3))
# print("be 1:" ,find_first_occurrence(3,lright4))
# print("be -1:" ,find_first_occurrence(4,list1))
# print("be -1:" ,find_first_occurrence(4,list2))
# print("be 5:" ,find_first_occurrence(4,list3))
# print("be 4:" ,find_first_occurrence(4,list4))

# print("be -1:" ,find_first_greater(1,list1))
# print("be 1:" ,find_first_greater(0,list2))
# print("be -1:" ,find_first_greater(1,list2))
# print("be -1:" ,find_first_greater(2,list2))
# print("be -1:" ,find_first_greater(3,l3))
# print("be 0:" ,find_first_greater(2,l3))
# print("be 0:", find_first_greater(-1, [0,0,0]))
# print("be 1:" ,find_first_greater(3,lleft))
# print("be 3:" ,find_first_greater(3,lleft1))
# print("be 3:" ,find_first_greater(3,lleft2))
# print("be 2:" ,find_first_greater(3,lleft3))
# print("be 2:" ,find_first_greater(3,lleft4))
# print("be 0:" ,find_first_greater(-3,list1))
# print("be 0:" ,find_first_greater(-3,list2))
# print("be 6:" ,find_first_greater(3,list5))
# print("be 12:" ,find_first_greater(4,list6))
# print("be -1:" ,find_first_greater(-3,lempty))
# print("be -1:" ,find_first_greater(3,lright))
# print("be 3:" ,find_first_greater(3,lright1))
# print("be 2:" ,find_first_greater(3,lright2))
# print("be 4:" ,find_first_greater(3,lright3))
# print("be 3:" ,find_first_greater(3,lright4))
# print("be -1:" ,find_first_greater(4,list1))
# print("be -1:" ,find_first_greater(4,list2))
# print("be 7:" ,find_first_greater(4,list3))
# print("be 5:" ,find_first_greater(4,list4))