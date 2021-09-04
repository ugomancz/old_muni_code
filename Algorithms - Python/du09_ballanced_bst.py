#!/usr/bin/env python3

from typing import Optional, List

# Povolene knihovny: typing, math

# IB002 Domaci uloha 9.
#
# V teto uloze se budeme zabyvat binarnimi vyhledavacimi stromy.
#
# V prvni casti bude Vasi ulohou sestavit skoro uplny binarni vyhledavaci strom
# obsahujici zadane klice. Vstupni pole klicu bude usporadano od nejmensich po
# nejvetsi. Vas algoritmus musi mit LINEARNI casovou slozitost vzhledem k poctu
# zadanych klicu. Tento pozadavek je splnitelny diky usporadanosti pole na
# vstupu.
#
# V druhe casti bude Vasi ulohou zjistit, jestli zadany binarni vyhledavaci
# strom je skoro uplny. Pozadovana casova slozitost je linearni vuci poctu uzlu
# ve strome.
#
# Ve treti casti bude Vasi ulohou zjistit, jestli zadany binarni vyhledavaci
# strom ma vsechny listy ve stejne hloubce. Pozadovana casova slozitost je opet
# linearni vuci poctu uzlu ve strome.
#
# Skoro uplny strom ma zaplnena vsechna patra, jen posledni nemusi byt uplne
# zaplneno (a rovnez nemusi byt doleva zarovnane).
#
# Pro ilustraci, pro vstup (1,2,3,4,5,6,7,8,9,10) je korektnim vystupem
# algoritmu z prvni casti napriklad jeden z nasledujicich stromu:
#
#             ( 5 )                           ( 7 )
#            /     \                         /     \
#          (2)     (8)                  ( 4 )       ( 9 )
#         /  \     /  \                /     \      /   \
#       (1)  (3) (6)  (9)            (2)     (6)  (8)   (10)
#              \   \    \            / \     /
#              (4) (7)  (10)       (1) (3) (5)
#
# Do nasledujicich definic trid nijak nezasahujte.
#
# Pro vykreslovani stromu muzete pouzit funkci make_graph z cv07.


class BSTree:
    """Trida BSTree pro reprezentaci binarniho vyhledavacicho stromu.

    Atributy:
        root   koren stromu typu Node, nebo None, pokud je strom prazdny
    """
    __slots__ = ("root",)

    def __init__(self) -> None:
        self.root: Optional[Node] = None


class Node:
    """Trida Node pro reprezentaci uzlu binarniho vyhledavaciho stromu.

    Atributy:
        key     klic daneho uzlu (zadany pri inicializaci)
        left    odkaz na leveho potomka typu Node, nebo None, pokud neexistuje
        right   odkaz na praveho potomka typu Node, nebo None, pokud neexistuje
    """
    __slots__ = ("left", "right", "key")

    def __init__(self, key: int) -> None:
        self.left: Optional[Node] = None
        self.right: Optional[Node] = None
        self.key: int = key


# Ukol 1.
# Implementuje funkci build_bst, ktera dostane vzestupne serazeny seznam hodnot
# a vytvori z nich skoro uplny binarni vyhledavaci strom (typu BSTree).
# Zadane pole hodnot nijak nemodifikujte.

def build_bst(array: List[int]) -> BSTree:
    """
    vstup: 'array' vzestupne serazene pole hodnot
    vystup: strom typu BSTree, ktery je skoro uplny (viz vyse) a obsahuje
            hodnoty z pole array
    casova slozitost: O(n), kde 'n' je delka array
    extrasekvencni prostorova slozitost:
         O(log n), nepocitame do ni vstupni pole ani vystupni strom,
         pocitame zasobnik rekurze
    """
    def foo(array: List[int], fst: int, last: int) -> node:
        if len(array) == 0:
            return None
        if len(array) == 1:
            node = Node()
            node.key = array[0]
            return node
        middle = last - fst // 2
        node = Node()
        node.key = array[middle]
        node.left = foo(array, fst, middle - 1)
        node.right = foo(array, middle + 1, last)
        return node
    if len(array) == 0:
        return None
    tree = BSTree()
    tree.root = foo(array, 0, len(array) - 1)
    return tree


# Ukol 2.
# Implementujte funkci check_almost_complete, ktera dostane binarni vyhledavaci
# strom a otestujte, zda je skoro uplny.
# Strom nijak nemodifikujte, ani nevytvarejte nove uzly nebo stromy.

def check_almost_complete(tree: BSTree) -> bool:
    """
    vstup: 'tree' binarni vyhledavaci strom typu BSTree
    vystup: True, pokud je 'tree' skoro uplny
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet uzlu stromu
    extrasekvencni prostorova slozitost: O(h), kde h je vyska stromu
        (nepocitame vstup, pocitame zasobnik rekurze)
    """
    pass # TODO


# Ukol 3.
# Implementujte funkci check_all_leaves_same_depth, ktera overi, zda jsou
# vsechny listy zadaneho binarniho vyhledavaciho stromu ve stejne hloubce.
# Strom nijak nemodifikujte, ani nevytvarejte nove uzly nebo stromy.

def check_all_leaves_same_depth(tree: BSTree) -> bool:
    """
    vstup: 'tree' binarni vyhledavaci strom typu BSTree
    vystup: True, pokud jsou vsechny listy 'tree' ve stejne hloubce
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet uzlu stromu
    extrasekvencni prostorova slozitost: O(h), kde h je vyska stromu
        (nepocitame vstup, pocitame zasobnik rekurze)
    """
    return True  # TODO
