#!/usr/bin/env python3

from typing import List, Optional

# Povolene knihovny: typing, math

# IB002 Domaci uloha 7.
#
# Souctovy strom je binarni strom, kde kazdy uzel ma nasledujici vlastnost:
# Pokud ma uzel alespon jednoho syna, potom je klic uzlu roven souctu klicu
# vsech jeho synu. Listy stromu tedy mohou obsahovat libovolne hodnoty.
# Za souctovy je povazovan i strom, ktery neobsahuje zadne uzly, a strom,
# ktery obsahuje prave jeden uzel.
#
# Muzete si samozrejme pridat vlastni pomocne funkce.
#
# Priklad:
# souctove stromy      nesouctove stromy
#   53       47            53       47
#  /  \        \          /  \     /
# 21  32       47        21  21   46
#             /  \                  \
#            1    46                 1

# Do nasledujicich definic trid nijak nezasahujte.
#
# Trida pro reprezentaci souctoveho stromu.
# root je koren stromu a je typu Node, nebo None, pokud je strom prazdny.
#
# Pro vykreslovani stromu muzete pouzit funkci make_graph z cv07.


class SumTree:
    __slots__ = ("root",)

    def __init__(self) -> None:
        self.root: Optional[Node] = None


# Trida pro reprezentaci uzlu v souctovem strome.
# key je hodnota uzlu, ktera ma byt rovna souctu hodnot vsech synu.

class Node:
    __slots__ = ("key", "left", "right")

    def __init__(self) -> None:
        self.key: int = 0
        self.left: Optional[Node] = None
        self.right: Optional[Node] = None


# Ukol 1.
# Vasim prvnim ukolem je napsat funkci, ktera vybuduje uplny souctovy strom ze
# zadaneho pole. Listy stromu budou prave prvky pole v poradi zleva doprava.
# Delka pole bude vzdy mocninou dvojky. Vstupni pole nijak nemodifikujte.
#
# Napriklad:
# Z pole [1,2,3,4] vznikne strom:
#      10
#    /    \
#   3      7
#  / \    / \
# 1   2  3   4

def build_sum_tree(array: List[int]) -> SumTree:
    """
    vstup: pole (Pythonovsky seznam) 'array' cisel delky 'n',
           kde 'n' je nejaka mocnina dvojky
    vystup: korektni strom typu SumTree, ktery ma v listech (v poradi zleva
            doprava) hodnoty ze zadaneho pole 'array'
            strom musi byt uplny, tj. vsechna jeho patra musi byt zcela
            zaplnena
    casova slozitost: O(n)
    extrasekvencni prostorova slozitost: O(log n)
        (Nepocita se prostor vstupniho pole a vybudovaneho vystupniho stromu,
         pocita se zasobnik rekurze.)
    """
    counter = 0
    newarr = []
    def foo() -> None:
        x = 1
        temp = 0
        if counter % 2 != 0:
            return
        temp = counter//2
        while temp % 2 == 0:
            x += 1
            temp = temp//2
        for _ in range(x):
            node = Node()
            node.key = newarr[-1].key + newarr[-2].key
            node.left = newarr[-2]
            node.right = newarr[-1]
            newarr.pop()
            newarr.pop()
            newarr.append(node)
    for i in range(len(array)):
        newarr.append(Node())
        newarr[-1].key = array[i]
        counter += 1
        foo()
    final = SumTree()
    if len(newarr) > 0:
            final.root = newarr[0]
    return final


# Ukol 2.
# Vasim druhym ukolem je napsat funkci is_sum_tree, ktera overi, zda je strom
# souctovy. Pokud ano, vraci True, jinak False.
# Vstupni strom nemodifikujte ani v prubehu vypoctu nevytvarejte nove stromy
# nebo uzly.

def is_sum_tree(tree: SumTree) -> bool:
    """
    vstup: 'tree' typu SumTree
           (je zaruceno, ze uzly ve strome jsou typu Node;
            neni zaruceno, ze splnuji souctovou podminku)
    vystup: True, pokud je 'tree' korektni SumTree, tj. vsechny jeho uzly
                  splnuji souctovou podminku
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet prvku 'tree'
    """
    if tree.root is None:
        return True
    def foo(node) -> bool:
        if node.left is None and node.right is None:
            return True
        if node.left is None:
            if node.key != node.right.key:
                return False
            else:
                return foo(node.right)
        elif node.right is None:
            if node.key != node.left.key:
                return False
            else:
                return foo(node.left)
        else:
            if node.key != (node.left.key + node.right.key):
                return False
        return foo(node.left) and foo(node.right)
    return foo(tree.root)


# Ukol 3.
# Vasim tretim ukolem je ze zadaneho souctoveho stromu smazat vsechny listy
# s hodnotou 0. Pokud timto mazanim vzniknou nove listy s hodnotou 0,
# je treba rekurzivne smazat i ty. Modifikujte primo zadany strom, nevytvarejte
# zadne nove stromy ani uzly.

def remove_zero_leaves(tree: SumTree) -> None:
    """
    vstup: 'tree' korektni souctovy strom typu SumTree
    vystup: zadny, ze stromu 'tree' jsou vymazany vsechny listy s hodnotou 0
            (vcetne vsech listu s hodnotou 0, ktere vzniknou timto mazanim)
    casova slozitost: O(n), kde 'n' je pocet prvku puvodniho 'tree'
    """
    if tree.root is None:
        return
    def foo(node) -> int:
        if node.key != 0:
            if node.left is not None:
                if foo(node.left) == -1:
                    node.left = None
            if node.right is not None:
                if foo(node.right) == -1:
                    node.right = None
        elif node.key == 0:
            if node.left is not None:
                if foo(node.left) == -1:
                    node.left = None
            if node.right is not None:
                if foo(node.right) == -1:
                    node.right = None
            if node.left is None and node.right is None:
                return -1
    if foo(tree.root) == -1:
        tree.root = None
