#!/usr/bin/env python3

# IB002 Domaci uloha 1.
#
# V teto uloze budete implementovat operace nad jednosmerne zretezenym
# seznamem. Jednosmerne zretezeny seznam ma pouze jeden atribut `first`,
# ktery ukazuje na zacatek seznamu. Kazdy uzel v seznamu pak ma dva atributy:
# `value`, ktery drzi hodnotu daneho uzlu, a `next`, ktery ukazuje na dalsi
# uzel v seznamu nebo None, pokud je aktualni uzel posledni.
#
# Korektni jednosmerne zretezeny seznam je takovy, ze bud je `first` None
# nebo se odkazuje na uzel takovy, ze prochazenim skrze odkazy `next` dojdeme
# k poslednimu uzlu. To znamena, ze korektni jednosmerne zretezeny seznam
# se nikde nesmi zacyklit.
#
# Smyslem teto ulohy je vyzkouset si praci s odkazy.
# V cele teto uloze je zakazano v implementaci pouzivat vestavene Pythonovske
# datove typy seznam (list), slovnik (dict), mnozina (set).
# Rovnez nejsou povoleny zadne Pythonovske knihovny.
# (Pokud chcete tyto veci pouzivat pro vlastni testovani, nezapomente je
#  pred odevzdanim vymazat nebo zakomentovat.)
#
# V prikladech a pri vystupu vyhodnocovaci sluzby znazornujeme jednosmerne
# zretezene seznamy nasledovne:
#
# -> 3 -> 4 -> 5 -> 7
# Toto reprezentuje seznam o ctyrech uzlech. Prvni uzel ma hodnotu 3, jeho
# naslednikem je uzel z hodnotou 4 atd. Posledni uzel ma hodnotu 7.
#
# Prazdny seznam (tj. seznam, jehoz `first` je None) znazornime takto:
# ->
#
# Jednoprvkovy seznam znazornime takto:
# -> 17
#
# Do definic trid LinkedList a Node nijak nezasahujte.
# (Pro zvidave: Deklarace __slots__ mimo jine zarucuje, ze se objektum danych
#  trid neda pridat zadny jiny atribut nez ty deklarovane.)
"""
vyhazoval nějaké errory ohledně syntaxe atd, ale testy prošly, OK
"""


class LinkedList:
    """Trida LinkedList reprezentuje jednosmerne zretezeny seznam.

    Atributy:
        first   odkaz na prvni prvek seznamu
    """

    __slots__ = ("first",)

    def __init__(self):
        self.first = None


class Node:
    """Trida Node reprezenujte prvek ve zretezenem seznamu.

    Atributy:
        value   hodnota uzlu
        next    odkaz na dalsi prvek seznamu
    """

    __slots__ = ("value", "next")

    def __init__(self):
        self.value = None
        self.next = None


def printlist(linked_list): # to be deleted
    curr_node = linked_list.first
    while curr_node is not None:
        print("-> " + str(curr_node.value) + " ", end="")
        curr_node = curr_node.next

# Ukol 1.
# Implementujte funkci remove_each(linked_list, k), ktera ze zadaneho
# jednosmerne zretezeneho seznamu odstrani kazdy k. prvek.

def remove_each(linked_list, k):
    """
    vstup: `linked_list` - korektni jednosmerne zretezeny seznam
           `k` - cele cislo >= 2
    vystup: zadny, ze vstupniho seznamu `linked_list` je odstranen kazdy
            `k`. prvek
            (samozrejme, seznam musi zustat korektni)
    casova slozitost: O(n), kde n je delka vstupniho seznamu
    extra prostorova slozitost: O(1)
        (zejmena tedy nesmite vytvaret novy seznam; smite jen modifikovat ten
         vstupni)

    priklad: pro vstup -> 1 -> 2 -> 3 -> 4 -> 5 a k=2 bude seznam modifikovan
             na -> 1 -> 3 -> 5
    """
    # print("first: ", end="")
    # printlist(linked_list)
    # print("")

    if linked_list.first is None or k < 2:
        return
    curr = linked_list.first
    before = None
    index = 1
    while curr is not None:
        if index % k == 0:
            before.next = curr.next
        before = curr
        curr = curr.next
        index += 1

    #print("then: ", end="")
    #printlist(linked_list)




# Ukol 2.
# Implementuje funkci double(linked_list), ktera jednosmerne zretezeny seznam
# zdvoji tak, aby obsahoval puvodni sekvenci hodnot dvakrat za sebou.

def double(linked_list):
    """
    vstup: `linked_list` - korektni jednosmerne zretezeny seznam
    vystup: zadny, vstupni seznam `linked_list` je zdvojeny (viz priklad)
            (samozrejme, seznam musi zustat korektni)
    casova slozitost: O(n), kde n je delka vstupniho seznamu

    priklad: pro vstup -> 17 -> 42 -> 0 -> -7 bude seznam modifikovan na
             -> 17 -> 42 -> 0 -> -7 -> 17 -> 42 -> 0 -> -7
    """
    #print("first: ", end="")
    #printlist(linked_list)
    #print("")
    if linked_list.first is None:
        return
    newfirst = Node()
    newcurr = newfirst
    curr = linked_list.first
    while True:
        if curr.next is None:
            newcurr.value = curr.value
            curr.next = newfirst
            break
        newcurr.value = curr.value
        newcurr.next = Node()
        newcurr = newcurr.next
        curr = curr.next
    #print("then: ", end="")
    #printlist(linked_list)


# emptylist = LinkedList()

# onelist = LinkedList()
# onelist.first = Node()
# onelist.first.value = 2

# linked = LinkedList()
# linked.first = Node()
# linked.first.value = 1
# linked.first.next = Node()
# linked.first.next.value = 2
# linked.first.next.next = Node()
# linked.first.next.next.value = 3
# linked.first.next.next.next = Node()
# linked.first.next.next.next.value = 4
# linked.first.next.next.next.next = Node()
# linked.first.next.next.next.next.value = 5
# linked.first.next.next.next.next.next = Node()
# linked.first.next.next.next.next.next.value = 6

# double(linked)
# double(emptylist)
# double(onelist)

# remove_each(linked, 2)
# remove_each(linked, 3)
# remove_each(linked, 4)
# remove_each(emptylist, 2)
# remove_each(onelist, 3)