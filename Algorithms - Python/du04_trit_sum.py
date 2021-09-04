#!/usr/bin/env python3

import time

from typing import List

# Povolene knihovny: typing, copy, math
# (Poznamka: "povolene" neznamena "nutne"; ukol je mozno vyresit i bez
#  jakychkoli knihoven.)

# IB002 Domaci uloha 4.
#
# V tomto ukolu uvazujeme pole, ktera obsahuji pouze cisla -1, 0, 1.
# Vasim ukolem bude implementovat funkci trit_sum, ktera pro zadana cisla
# `length` a `total` vrati seznam vsech takovych poli delky `length`, jejichz
# soucet je presne `total`.
#
# Priklady:
# Pro vstup length=2 a total=0 bude vystupem:
#   [[-1, 1], [0, 0], [1, -1]]
# Pro vstup length=4 a total=-3 bude vystupem:
#   [[-1, -1, -1, 0], [-1, -1, 0, -1], [-1, 0, -1, -1], [0, -1, -1, -1]]
#
# Pocty poli pro dane hodnoty `length` a `total` se daji zapsat nasledovne:
#
#                             total
# length|  -5  -4  -3  -2  -1   0   1   2   3   4   5
# ------+----------------------------------------------
#    0  |   0   0   0   0   0   1   0   0   0   0   0
#    1  |   0   0   0   0   1   1   1   0   0   0   0
#    2  |   0   0   0   1   2   3   2   1   0   0   0
#    3  |   0   0   1   3   6   7   6   3   1   0   0
#    4  |   0   1   4  10  16  19  16  10   4   1   0
#   ...
#
# Vsimnete si, ze kazda hodnota v tabulce je souctem tri hodnot: te
# bezprostredne nad ni a dvou sousedicich. (Tomuto se rika trinomialni
# trojuhelnik, viz https://en.wikipedia.org/wiki/Trinomial_triangle.)
#
# Toto pozorovani muzete jednak pouzit pro kontrolu toho, ze vase reseni
# pocita spravne, jednak bude hodnota v tabulce hrat roli v casove slozitosti
# reseni.
#
# Pozadovanou funkci je vhodne resit rekurzivne. Pro dodrzeni spravne casove
# slozitosti je treba si dobre rozmyslet, ve kterych chvilich je vhodne
# rekurzi ukoncit.

def trit_sum(length: int, total: int) -> List[List[int]]:
    # start = time.time()
    """
    vstup: `length` - nezaporne cele cislo
           `total` - cele cislo
    vystup: seznam vsech poli delky presne `length`,
            jejichz soucet je presne `total`
    casova slozitost: O(T(length, total) * length^2),
        kde T(length, total) je hodnota z tabulky naznacene vyse
    """
    assert length >= 0
    finallist = []
    def helper(length: int, curr_length: int, total: int, curr_total: int, mylist: List) -> None:
        if (curr_total - (length - curr_length) > total) or (curr_total + (length - curr_length) < total):
            return
        if curr_length == length:
            if total == curr_total:
                finallist.append(mylist)
            return
        helper(length, curr_length + 1, total, curr_total, mylist + [0])
        helper(length, curr_length + 1, total, curr_total + 1, mylist + [1])
        helper(length, curr_length + 1, total, curr_total - 1, mylist + [-1])
    helper(length, 0, total, 0, [])
    # print("seconds: " + str((time.time() - start)))
    return finallist

# trit_sum(14,0)