#!/usr/bin/env python3

from typing import Optional

# IB002 Domaci uloha 2.
#
# Jednosmerne spojovany seznam uz znate - jde o zretezeny seznam uzlu (Node),
# kde kazdy uzel ukazuje na sveho naslednika. V tomto prikladu nemame first
# (ani last), seznam je zadany "prvnim" ze svych uzlu.
# Seznamy v teto uloze nikdy nebudou prazdne, tj. vzdy muzete predpokladat,
# ze na vstupu je objekt typu Node.
#
# Tato uloha pracuje se dvema typy jednosmerne spojovanych seznamu:
# Linearni seznam - kde posledni prvek seznamu ukazuje na None.
# Kruhovy seznam - kde posledni prvek seznamu ukazuje zpet na prvni prvek.
#
# Pro vsechny funkce muzete predpokladat, ze seznam na vstupu je linearni,
# nebo kruhovy, tj. nemusite napriklad osetrovat situaci, kdy naslednikem
# "posledniho" v seznamu je "druhy".
#
# Podobne jako u minule ulohy, smyslem je vyzkouset si praci s odkazy.
# I v teto uloze je tedy zakazano pouzivat seznamy (list), slovniky (dict)
# a mnoziny (set).
# Rovnez nejsou povoleny zadne Pythonovske knihovny.
# (Pokud chcete tyto veci pouzivat pro vlastni testovani, nezapomente je
#  pred odevzdanim vymazat nebo zakomentovat.)
#
# Ve vystupu vyhodnocovaci sluzby znazornujeme jednosmerne spojovane seznamy
# podobne jako u minuleho ukolu:
#
# Toto je linearni seznam o trech prvcich:
# linearni seznam: -> 7 -> 42 -> 17
# Toto je kruhovy seznam o trech prvcich:
# kruhovy seznam: -> 7 -> 42 -> 17 -> zpet na zacatek
#
# Do definice tridy Node nijak nezasahujte.


class Node:
    """Trida Node reprezentujici prvek ve spojovanem seznamu

    Atributy:
        key        klic daneho uzlu (cele cislo)
        next       odkaz na dalsi prvek seznamu
        opposite   odkaz na protejsi prvek seznamu, viz ukol 3.
    """

    __slots__ = ('key', 'next', 'opposite')

    def __init__(self) -> None:
        self.key: int = 0
        self.next: Optional[Node] = None
        self.opposite: Optional[Node] = None

# def mynodeprint(node: Node) -> str:
#     if node is None:
#         return "none"
#     return str(node.key)
# def myprint(node: Node) -> None:
#     fst = node
#     curr = fst
#     while curr is not None and curr.next != fst:
#         print("(" + mynodeprint(curr) + ", " + mynodeprint(curr.opposite) + ") -> ")
#         curr = curr.next


# Ukol 1.
# Implementujte funkci is_circular, ktera dostane prvni uzel seznamu
# a otestuje, zda je zadany zretezeny seznam kruhovy.

def is_circular(node: Node) -> bool:
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: True, pokud je seznam z uzlu 'node' kruhovy
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    """
    fst = node
    while node is not None:
        node = node.next
        if node == fst:
            return True
    return False


# Ukol 2.
# Implementujte funkci get_length, ktera vrati delku (tj. pocet uzlu)
# linearniho nebo kruhoveho zretezeneho seznamu zacinajiciho v zadanem uzlu.

def get_length(node: Node) -> int:
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: pocet prvku v zadanem seznamu
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    """
    fst = node
    counter = 1
    while node.next is not None and node.next != fst:
        counter += 1
        node = node.next
    return counter


# Ukol 3.
# Implementujte funkci calculate_opposites, ktera korektne naplni atributy
# "opposite" v uzlech kruhoveho seznamu sude delky. Tj. pro kruhove seznamy
# delky 2n naplni u kazdeho uzlu atribut opposite uzlem, ktery je o n kroku
# dale (tedy v kruhu je to uzel "naproti").
#
# Napriklad v kruhovem seznamu 1 -> 2 -> 3 -> 4 (-> 1) je opposite
# uzlu 1 uzel 3, uzlu 2 uzel 4, uzlu 3 uzel 1 a uzlu 4 uzel 2.
#
# Pokud vstupni seznam neni kruhovy nebo ma lichou delku, tak funkce
# calculate_opposites seznam neupravuje.
#
# Pozor na casovou a prostorovou slozitost vaseho algoritmu!

def calculate_opposites(node: Node) -> None:
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: nic, kokretne doplni atribut opposite pro kruhovy seznam sude delky
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    prostorova slozitost: 1 (konstantni)
    """
    length = get_length(node)
    if length % 2 == 1:
    	print("licha delka")
    	return
    if not is_circular(node):
    	print("neni kruhovy")
    	return
    # myprint(node)
    oppo = node
    for _ in range(length//2):
    	oppo = oppo.next
    for _ in range(length):
    	node.opposite = oppo
    	node = node.next
    	oppo = oppo.next
    # myprint(node)

# node6 = Node()
# node6.key = 1
# node6.next = Node()
# node6.next.key = 2
# node6.next.next = Node()
# node6.next.next.key = 3
# node6.next.next.next = Node()
# node6.next.next.next.key = 4
# node6.next.next.next.next = Node()
# node6.next.next.next.next.key = 5
# node6.next.next.next.next.next = Node()
# node6.next.next.next.next.next.key = 6

# node6c = Node()
# node6c.key = 1
# node6c.next = Node()
# node6c.next.key = 2
# node6c.next.next = Node()
# node6c.next.next.key = 3
# node6c.next.next.next = Node()
# node6c.next.next.next.key = 4
# node6c.next.next.next.next = Node()
# node6c.next.next.next.next.key = 5
# node6c.next.next.next.next.next = Node()
# node6c.next.next.next.next.next.key = 6
# node6c.next.next.next.next.next.next = node6c

# node3 = Node()
# node3.key = 1
# node3.next = Node()
# node3.next.key = 2
# node3.next.next = Node()
# node3.next.next.key = 3

# node3c = Node()
# node3c.key = 1
# node3c.next = Node()
# node3c.next.key = 2
# node3c.next.next = Node()
# node3c.next.next.key = 3
# node3c.next.next.next = node3c

# node2 = Node()
# node2.key = 1
# node2.next = Node()
# node2.next.key = 2

# node2c = Node()
# node2c.key = 1
# node2c.next = Node()
# node2c.next.key = 2
# node2c.next.next = node2c

# node1 = Node()
# node1.key = 1

# node1c = Node()
# node1c.key = 1
# node1c.next = node1c

# print(is_circular(node1))
# print(is_circular(node1c))
# print(is_circular(node2))
# print(is_circular(node2c))
# print(is_circular(node3))
# print(is_circular(node3c))
# print(is_circular(node6))
# print(is_circular(node6c))

# print(get_length(node1))
# print(get_length(node1c))
# print(get_length(node2))
# print(get_length(node2c))
# print(get_length(node3))
# print(get_length(node3c))
# print(get_length(node6))
# print(get_length(node6c))

# calculate_opposites(node1)
# calculate_opposites(node1c)
# calculate_opposites(node2)
# calculate_opposites(node2c)
# calculate_opposites(node3)
# calculate_opposites(node3c)
# calculate_opposites(node6)
# calculate_opposites(node6c)