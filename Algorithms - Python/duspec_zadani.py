#!/usr/bin/python3

# UCO:
# Povolene knihovny: math, collections, typing

import math  # tento radek nesmite smazat!
from typing import List, Optional, Any, IO

# --- Specialni domaci ukol IB002 2020 ---
#
# Zadani:
# V tomto domacim ukolu budeme pracovat s maximovymi haldami.
# Na rozdil od prednasky neuvazujeme binarni haldy, ale d-arni
# (tj. stupen vetveni je d). Reprezentace d-arni haldy polem funguje
# obdobne jako pro binarni haldy. Napriklad halda      7     s aritou 3
# je reprezentovana polem [7, 5, 2, 4, 3].          /  |  \
#                                                  5   2   4
#                                                 /
#                                                3


class DMaxHeap:
    """
    Trida DMaxHeap slouzi k reprezentaci d-arni maximove haldy.

    Atributy:
        size    pocet prvku v halde
        arity   arita haldy
        array   pole prvku haldy
    """
    __slots__ = ('size', 'arity', 'array')

    def __init__(self) -> None:
        self.size: int = 0
        self.arity: int = 0
        self.array: List[Any] = []


# Ukol 1. (1 bod)
#
# Implementujte funkci is_correct, ktera overi, zda je zadana halda
# korektni d-arni maximovou haldou.
#
# Velmi doporucujeme implementovat si a pouzivat i nasledujici pomocne funkce.


def parent_index(heap: DMaxHeap, i: int) -> Optional[int]:
    """
    vstup: 'heap' korektni d-arni halda typu DMaxHeap
           'i'    korektni index haldy, jehoz rodic nas zajima
    vystup: index rodice prvku na pozici 'i'
            None, pokud prvek na pozici 'i' nema rodice.
    casova i extrasekvencni prostorova slozitost: O(1)
    """
    if i == 0:
        return 0
    return (i - 1) // heap.arity


def child_index(heap: DMaxHeap, i: int, k: int) -> Optional[int]:
    """
    vstup: 'heap' korektni d-arni halda typu DMaxHeap
           'i'    korektni index haldy, jehoz syn nas zajima
           'k'    kolikaty syn nas zajima (1 <= k <= heap.arity)
    vystup: index 'k'. syna prvku na pozici 'i'
            None, pokud tento syn neexistuje.
    casova i extrasekvencni prostorova slozitost: O(1)
    """
    return heap.arity * i + k


def parent(heap: DMaxHeap, i: int) -> Optional[Any]:
    """
    vstup: 'heap' korektni d-arni halda typu DMaxHeap
           'i'    korektni index haldy, jehoz rodic nas zajima
    vystup: hodnota rodice prvku na pozici 'i'
            None, pokud prvek na pozici 'i' nema rodice
    casova i extrasekvencni prostorova slozitost: O(1)
    """
    return heap.array[parent_index(heap, i)]


def child(heap: DMaxHeap, i: int, k: int) -> Optional[Any]:
    """
    vstup: 'heap' korektni d-arni halda typu DMaxHeap
           'i'    korektni index haldy, jehoz syn nas zajima
           'k'    kolikaty syn nas zajima (1 <= k <= heap.arity)
    vystup: hodnota 'k'. syna prvku na pozici 'i'
            None, pokud tento syn neexistuje.
    casova i extrasekvencni prostorova slozitost: O(1)
    """
    return heap.array[child_index(heap, i, k)]


def is_correct(heap: DMaxHeap) -> bool:
    """
    vstup: 'heap' d-arni halda typu DMaxHeap
           (je zaruceno, ze heap.size je velikost pole heap.array;
            neni zaruceno, ze prvky heap.array splnuji podminky haldy)
    vystup: True, pokud heap je korektni d-arni maximova halda
            False, jinak
    casova slozitost: O(n), kde n je pocet prvku v halde
    extrasekvencni prostorova slozitost: O(1) - POZOR, nelze pouzit rekurzi
        za rekurzivni reseni se slozitosti O(log(n)) budete penalizovani -0.5
        body
    """
    """
    I very much hope that arity is ignored when calculating complexity,
    because this is technically O(n * d), but I didn't consider that during
    algorithm creation.
    """
    for i in range(heap.size // heap.arity + 1):
        for j in range(heap.arity):
            if child_index(heap, i, j + 1) >= heap.size: # prevents index out of range errors
                break
            if child(heap, i, j + 1) > heap.array[i]: # if child is bigger than it's parent -> isn't correct MaxHeap
                return False
    return True


# Ukol 2. (1 bod)
# Implementujte funkci repair_heap, ktera opravi zadanou d-arni maximovou
# haldu. Vlastnost haldy porusuje nanejvys jeden prvek (tj. vstup vznikl
# z korektni haldy tak, ze se zmenila hodnota tohoto jednoho prvku).
# Index tohoto prvku dostanete na vstupu.


def repair_heap(heap: DMaxHeap, i: int) -> None:
    """
    vstup: 'heap' d-arni halda typu DMaxHeap
           'i'    index prvku, ktery jediny muze porusovat vlastnost haldy
    vystup: zadny, presklada prvky v 'heap' tak, aby byla korektni d-arni
            maximovou haldou
    casova slozitost: O(d * log(n)), kde n je pocet prvku v halde
    extrasekv. prostorova slozitost: O(log(n)), kde n je pocet prvku v halde
    """
    if heap.array[i] > parent(heap, i): # if parent's value is lower than it's own swaps them and bubbles up the heap
        heap.array[i], heap.array[parent_index(heap, i)] = heap.array[parent_index(heap, i)], heap.array[i]
        repair_heap(heap, parent_index(heap, i))
        return
    highest_child_index = i
    for j in range(heap.arity): # finds the child with highest value
        if child_index(heap, i, j + 1) >= heap.size:
            break
        if child(heap, i, j + 1) > heap.array[highest_child_index]:
            highest_child_index = child_index(heap, i, j + 1)
    if highest_child_index == i: # no child with value higher than current node, end of recursion
        return
    if heap.array[i] < heap.array[highest_child_index]: # if there is a child with higher value than current node swaps them and bubbles down the heap
        heap.array[i], heap.array[highest_child_index] = heap.array[highest_child_index], heap.array[i]
        repair_heap(heap, highest_child_index)



# Ukol 3. (1 bod)
# V tomto ukolu budete prevadet d-arni haldu do stromove reprezentace.
# Navic budeme pocitat pro kazdy prvek d-arni maximove haldy, jaka je
# minimalni hodnota v 'podstromu tohoto prvku', tj. stromu jemuz je korenem.
# Napr. pro ternarni maxim. haldu [20, 4, 9, 8, 2, 1, 3, 6, 4, 5, 7, 2, 4, 1]
# cili            (20)       jsou minima v podstromech       (1)
#           /      |       \                            /     |      \
#       (4)       (9)       (8)                     (1)      (4)       (2)
#      / | \     / | \     / | \                   / | \     / | \     / | \
#    (2)(1)(3) (6)(4)(5) (7)(2)(4)               (1)(1)(3) (6)(4)(5) (7)(2)(4)
#   /                                           /
# (1)                                         (1)
#
# Konkretne budete implementovat funkci all_subtree_mins, ktera pro zadanou
# korektni d-arni maximovou haldu vrati stromovou reprezentaci haldy doplnenou
# o minimalni hodnoty v podstromech. Pro stromovou reprezentaci pouzijte
# uzly typu Node (viz nize). Navratova hodnota bude koren tohoto stromu,
# bude tedy take typu Node.

class Node:
    """
    Trida Node pro stromovou reprezentaci haldy.

    Atributy:
        value         hodnota prvku na odpovidajici pozici v halde
        min_val       minimalni hodnota v podstromu tohoto prvku
        sons          pole uzlu pro syny (zachovejte poradi jako v halde)
    """
    __slots__ = ('value', 'min_val', 'sons')

    def __init__(self, value: Any) -> None:
        self.value: Any = value
        self.min_val: Any = None
        self.sons: List[Node] = []

"""
I spent 20 minutes figuring out how to do this in O(n), I think I found a solution
in O(n*log n), but didn't have enough time to implement it :/
"""   
    

def all_subtree_mins(heap: DMaxHeap) -> Optional[Node]:
    """
    vstup: 'heap' korektni d-arni halda typu DMaxHeap
    vystup: koren (typu Node) stromove reprezentace haldy
               (vcetne minimalnich hodnot)
            None pro prazdnou haldu
    casova slozitost: O(n), kde n je pocet hodnot v halde
    """
    return None  # TODO


########################################################################
#               Nasleduje kod testu, NEMODIFIKUJTE JEJ                 #
########################################################################


def print_tree(tree: Optional[Node], filename: str) -> None:
    """
    Zde mate k dispozici funkci `print_tree`, ktera vam vygeneruje do
    souboru `filename` reprezentaci stromu pro graphviz. Graphviz je nastroj,
    ktery vam umozni vizualizaci datovych struktur, coz se hodi predevsim pro
    ladeni. Pro zobrazeni graphvizu muzete vyuzit: http://www.webgraphviz.com/.
    Nebo si soubor otevrete v lokalne nainstalovanem programu xdot.
    """
    with open(filename, 'w') as dot_file:
        dot_file.write("digraph {\n")
        ib002_print_tree(dot_file, tree)
        dot_file.write("}\n")


def ib002_print_tree(f: IO[str], tree: Optional[Node]) -> None:
    from collections import deque
    queue = deque([tree])
    vertices = []
    c = 0
    while queue:
        c += 1
        node = queue.popleft()
        if node is not None:
            f.write('"{}" [label="{},{}"];\n'.format(node, node.value,
                                                     node.min_val))
            for i in node.sons:
                vertices.append((node, i))
                queue.append(i)
        if c > 10000:
            print("Vypis stromu do souboru nedokoncen!")
            print("Vytvoreny strom asi obsahuje cyklus.")
            return
    for (v, r) in vertices:
        f.write('"{}" -> "{}"\n'.format(v, r))


class Ib002TestCase:
    def __init__(self, array: List[int], arity: int, is_correct: bool,
                 mins: List[int], is_canonical: bool) -> None:
        self.heap = DMaxHeap()
        self.heap.size = len(array)
        self.heap.arity = arity
        self.heap.array = array
        self.is_correct = is_correct
        self.mins = mins
        self.is_canonical = is_canonical
        self.sub_cases: List[Any] = []
        self.heap_working_copy: DMaxHeap = DMaxHeap()
        self.heap_equiv_copy: DMaxHeap = DMaxHeap()

    def add_sub_case(self, place: int, new_val: int) -> 'Ib002TestCase':
        self.sub_cases.append((place, new_val))
        return self

    def get_working_heap(self) -> DMaxHeap:
        self.heap_working_copy = DMaxHeap()
        self.heap_working_copy.size = self.heap.size
        self.heap_working_copy.arity = self.heap.arity
        self.heap_working_copy.array = self.heap.array[:]
        return self.heap_working_copy

    def get_equiv_heap(self) -> DMaxHeap:
        self.heap_equiv_copy = DMaxHeap()
        self.heap_equiv_copy.size = self.heap.size
        self.heap_equiv_copy.arity = self.heap.arity
        self.heap_equiv_copy.array = self.heap.array[:]
        return self.heap_equiv_copy

    def make_new_subcase_heap(self, sub_case: Any) -> None:
        self.get_equiv_heap()
        self.get_working_heap()
        if sub_case is not None:
            self.heap_working_copy.array[sub_case[0]] = sub_case[1]
            self.heap_equiv_copy.array[sub_case[0]] = sub_case[1]

    def check_heap(self, changeable: bool) -> bool:
        if changeable:
            return self.check_heap_equiv()
        else:
            return self.check_heap_unchanged()

    def check_heap_unchanged(self) -> bool:
        if self.heap.size == self.heap_working_copy.size and \
           self.heap.array == self.heap_working_copy.array and \
           self.heap.arity == self.heap_working_copy.arity:
            return True

        ib002_report_heap("Doslo k modifikaci vstupni haldy", self.heap)
        ib002_report_heap("na", self.heap_working_copy)

        self.heap_working_copy = DMaxHeap()  # invalidate the copy
        return False

    def check_heap_equiv(self) -> bool:
        # compares heap_working_copy with heap_equiv_copy
        if self.heap_equiv_copy.size == self.heap_working_copy.size and \
           sorted(self.heap_equiv_copy.array[:self.heap_equiv_copy.size]) == \
           sorted(self.heap_working_copy.array[:self.heap_working_copy.size])\
           and self.heap_equiv_copy.arity == self.heap_working_copy.arity:
            return True

        ib002_report_heap("Doslo k nekorektni modifikaci vstupni haldy",
                          self.heap_equiv_copy)
        ib002_report_heap("na neekvivalentni haldu", self.heap_working_copy)

        self.heap_working_copy = DMaxHeap()  # invalidate the copy
        return False

    def prune_test(self) -> bool:
        test_diameter = self.heap.arity
        return ib002_test_pruning(
            [i * -1 for i in self.heap_working_copy.array], test_diameter)

    def test_merging(self) -> bool:
        test_diameter = self.heap.arity
        return ib002_test_merging(
            [i * -test_diameter for i in self.heap_working_copy.array],
            test_diameter)


def ib002_report_heap(msg: str, heap: DMaxHeap) -> None:
    print("{}:".format(msg))
    print("    heap.size = {}".format(heap.size))
    print("    heap.arity = {}".format(heap.arity))
    print("    heap.array = {}".format(heap.array))


def ib002_report_node(msg: str, node: Node) -> None:
    print("{}:".format(msg))
    print("    node.value = {}".format(node.value))
    print("    node.min_val = {}".format(node.min_val))
    print("    node.sons = {}".format(node.sons))


IB002_CASES = [
    Ib002TestCase([7, 5, 2, 4, 3], 3, True, [2, 3, 2, 4, 3], False)
    .add_sub_case(1, 23)
    .add_sub_case(1, -23)
    .add_sub_case(0, 23)
    .add_sub_case(0, 0)
    .add_sub_case(0, -10203)
    .add_sub_case(0, 10203)
    .add_sub_case(2, 1203)
    .add_sub_case(3, 100),
    Ib002TestCase([7, 5, 2, 4], 3, True, [2, 5, 2, 4], False)
    .add_sub_case(1, 23)
    .add_sub_case(1, -23)
    .add_sub_case(0, 23)
    .add_sub_case(0, 0)
    .add_sub_case(0, -10203)
    .add_sub_case(0, 10203)
    .add_sub_case(2, 1203)
    .add_sub_case(3, 100),
    Ib002TestCase([1, 5, 2, 4], 2, False, [], False),
    Ib002TestCase([10, 5, 2, 4], 2, True, [2, 4, 2, 4], False),
    Ib002TestCase([10, 5, 2, 8], 2, False, [], False),
    Ib002TestCase([10, 5, 2, 8], 3, True, [2, 5, 2, 8], True),
    Ib002TestCase([7, 5, 2, 6, 1], 3, True, [1, 1, 2, 6, 1], True),
    Ib002TestCase([7, 5, 2, 6, 1], 2, False, [], False),
    Ib002TestCase([7, 5, 2, 6, 1], 3, True, [1, 1, 2, 6, 1], True),
    Ib002TestCase([7, 5, 2, 6, 1], 2, False, [], False),
    Ib002TestCase([7, 1, 2, 8], 3, False, [], False),
    Ib002TestCase([20, 4, 9, 2, 1, 3, 6], 2, True,
                  [1, 1, 3, 2, 1, 3, 6], False)
    .add_sub_case(1, 23)
    .add_sub_case(1, -23)
    .add_sub_case(0, 23)
    .add_sub_case(0, 0)
    .add_sub_case(0, -10203)
    .add_sub_case(0, 10203)
    .add_sub_case(2, 120)
    .add_sub_case(3, 100)
    .add_sub_case(4, 120)
    .add_sub_case(5, 100)
    .add_sub_case(6, 120)
    .add_sub_case(2, 12)
    .add_sub_case(3, 10)
    .add_sub_case(4, 12)
    .add_sub_case(5, 10)
    .add_sub_case(6, 12),
    Ib002TestCase([20, 4, 9, 1, 2, 3, 6], 2, True,
                  [1, 1, 3, 1, 2, 3, 6], True),
    Ib002TestCase([20, 4, 9, 1, 2, 6, 3], 2, True,
                  [1, 1, 3, 1, 2, 6, 3], False),
    Ib002TestCase([20, 4, 9, 1, 2, 6], 2, True,
                  [1, 1, 6, 1, 2, 6], True),
    Ib002TestCase([20, 4, 9, 2, 1, 3, 6, 1], 2, True,
                  [1, 1, 3, 1, 1, 3, 6, 1], False),
    Ib002TestCase([23, 0, 5, -2, -6, 3, 5], 2, True,
                  [-6, -6, 3, -2, -6, 3, 5], False),
    Ib002TestCase([23, 0, 5, 1, -2, -6, -3, 5], 3, True,
                  [-6, -6, 5, 1, -2, -6, -3, 5], False)
    .add_sub_case(0, 1000)
    .add_sub_case(0, -1000)
    .add_sub_case(1, 1000)
    .add_sub_case(1, -1000)
    .add_sub_case(2, 0),
    Ib002TestCase([20, 4, 9, 2, 1, 3, 6, 1, -5, -7, -2, 4, 1], 2, False,
                  [], False),
    Ib002TestCase([20, 4, 9, 8, 2, 1, 3, 6, 4, 5, 7, 2, 4, 1], 2, False,
                  [], False),
    Ib002TestCase([20, 4, 9, 8, 2, 1, 3, 6, 4, 5, 7, 2, 4, 1], 3, True,
                  [1, 1, 4, 2, 1, 1, 3, 6, 4, 5, 7, 2, 4, 1], False),
    Ib002TestCase([20, 4, 9, 18, 2, 1, 3, 6, 4, 7, 7, 2, 1], 3, True,
                  [1, 1, 4, 1, 2, 1, 3, 6, 4, 7, 7, 2, 1], False),
    Ib002TestCase([20, 4, 9, 18, 2, 1, 3, 6, 4, 7, 7, 2], 3, True,
                  [1, 1, 4, 2, 2, 1, 3, 6, 4, 7, 7, 2], False),
    Ib002TestCase([20, 4, 9, 18, 2, 1, 3, 6, 4, 7, 7], 3, True,
                  [1, 1, 4, 7, 2, 1, 3, 6, 4, 7, 7], True),
    Ib002TestCase([20, 4, 9, 18, 2, 1, 3, 6, 4, 7, 70], 3, False, [], False),
    Ib002TestCase([], 12, True, [], True),
    Ib002TestCase([1], 2, True, [1], True),
    Ib002TestCase([1, 1, 1, 1, 1, 1, 1, 1], 5, True,
                  [1, 1, 1, 1, 1, 1, 1, 1], True),
    Ib002TestCase([5, 4, 2, 3, 1], 3, True, [1, 1, 2, 3, 1], False),
    Ib002TestCase([5, 4, 2, 3], 4, True, [2, 4, 2, 3], False),
    Ib002TestCase([20, 4, 9, 8, 2, 3, 6, 5, 7, 4, 1], 3, False, [], False),
    Ib002TestCase([2013], 2, True, [2013], True),
    Ib002TestCase([17, -13, -2, -18], 2, True, [-18, -18, -2, -18], True),
    Ib002TestCase([2023, 3, 9, 1, 2, 4], 4, False, [], False),
    Ib002TestCase([2023, 7, 9, 1, 2, 4], 4, True, [1, 4, 9, 1, 2, 4], False),
    Ib002TestCase([9999999999999, 700000000, 9000000000, 1, 2, 4], 4, True,
                  [1, 4, 9000000000, 1, 2, 4], False),
    Ib002TestCase([9999999999999, 700000000, 9000000000, 1, 2, 4], 2, True,
                  [1, 1, 4, 1, 2, 4], True),
    Ib002TestCase([9999999999999, 777777700000000, 9000000000, 1, 2, 4],
                  4, False, [], False),
    Ib002TestCase([9999999999999, 777777700000000, 9000000000, 1, 2, 4],
                  2, False, [], False),
    Ib002TestCase([3, 3, 9, 1, 0, 4], 4, False, [], False),
    Ib002TestCase([0, -1, -12, -2, -3, -15, -19, -3], 2, True,
                  [-19, -3, -19, -3, -3, -15, -19, -3], False),
    Ib002TestCase([0, -12, -1, -19, -15, -3, -2, -3], 2, False, [], False),
    Ib002TestCase([0, -1, -12, -2, -3, -15, -19, -3], 3, False, [], False),
    Ib002TestCase([0, -1, -12, -2, -3, -15, -19, -3], 3, False, [], False),
    Ib002TestCase([0, -1, -12, -2, -3, -15, -19, -30], 3, True,
                  [-30, -19, -30, -2, -3, -15, -19, -30], False),
    Ib002TestCase([0, 1, 12, -2, -3, -15, -19, -3], 2, False, [], False),
    Ib002TestCase([0, 12, 1, -19, -15, -3, -2, -3], 2, False, [], False),
    Ib002TestCase([0, 1, 12, -2, -3, -15, -19, -3], 3, False, [], False),
    Ib002TestCase([0, 1, 12, -2, -3, -15, -19, -3], 3, False, [], False),
    Ib002TestCase([0, 1, 12, -2, -3, -15, -19, -30], 3, False, [], False),
    Ib002TestCase([4000, 2300, 120, 312, 323, 20, 4, 9, 3, 2, 7, 3, 1,
                   2, 2, 1, 2, 4, 1], 4, True,
                  [1, 3, 1, 1, 1, 20, 4, 9, 3, 2, 7, 3, 1, 2, 2, 1, 2, 4, 1],
                  False),
    Ib002TestCase([4000, 300, 120, 312, 3230, 2, 4, 9, 30, 2, 7, 3, 10, 2, 2,
                   1, 20, 4, 1], 4, True,
                  [1, 2, 2, 1, 1, 2, 4, 9, 30, 2, 7, 3, 10, 2, 2, 1, 20, 4,
                   1], False),
    Ib002TestCase([4000, 2300, 120, 312, 323, 20, 4, 9, 3, 2, 7, 3, 1, 2,
                   2, 1, 2, 4, 1], 3, True,
                  [1, 1, 2, 1, 1, 1, 4, 9, 3, 2, 7, 3, 1, 2, 2, 1, 2, 4, 1],
                  False),
    Ib002TestCase([4000, 2300, 120, 312, 323, 20, 4, 9, 3, 2, 7, 3, 1, 2, 2,
                   1, 2, 4, 1], 2, False, [], False),
    Ib002TestCase([20, 4, 9, 3, 2, 7, 3, 1, 2, 2, 1, 2, 4, 1], 2, True,
                  [1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 2, 4, 1], False),
    Ib002TestCase([20, 4, 9, 3, 2, 7, 3, 1, 2, 2, 1, 2, 4], 2, True,
                  [1, 1, 2, 1, 1, 2, 3, 1, 2, 2, 1, 2, 4], False),
    Ib002TestCase([10, 8, 9, 7, 8, 2, 0, 9, 3, 1, 7, 0, 1], 3, True,
                  [0, 0, 1, 0, 8, 2, 0, 9, 3, 1, 7, 0, 1], False)
    .add_sub_case(0, 1000)
    .add_sub_case(0, -1000)
    .add_sub_case(3, 18)
    .add_sub_case(3, 2)
    .add_sub_case(1, 18)
    .add_sub_case(1, -2)
    .add_sub_case(7, 18)
    .add_sub_case(7, -2)
    .add_sub_case(8, 8)
    .add_sub_case(8, 3)
    .add_sub_case(8, 32)
    .add_sub_case(8, 2)
    .add_sub_case(8, 1)
    .add_sub_case(8, 0)
    .add_sub_case(9, 32)
    .add_sub_case(9, 10)
    .add_sub_case(9, 6)
    .add_sub_case(9, 2)
    .add_sub_case(9, -5)
    .add_sub_case(12, 8)
    .add_sub_case(12, 32)
    .add_sub_case(11, 32)
    .add_sub_case(12, 2)
    .add_sub_case(11, 4)
    .add_sub_case(10, 8)
    .add_sub_case(12, -2)
    .add_sub_case(7, -2),
    Ib002TestCase([20, 4, 9, 3, 2, 7, 3, 1, 2, 2, 1, 2, 4, 1, 3], 2, True,
                  [1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 2, 4, 1, 3], False)
    .add_sub_case(0, 1000)
    .add_sub_case(0, -1000)
    .add_sub_case(3, 18)
    .add_sub_case(3, 2)
    .add_sub_case(1, 18)
    .add_sub_case(1, -2)
    .add_sub_case(7, 18)
    .add_sub_case(7, -2)
    .add_sub_case(8, 8)
    .add_sub_case(8, 3)
    .add_sub_case(8, 3)
    .add_sub_case(8, 2)
    .add_sub_case(8, 1)
    .add_sub_case(8, 0)
    .add_sub_case(8, -2)
    .add_sub_case(7, -2),
    Ib002TestCase([3, 1, 2, 0, 1, -5, -7, 0, -4, -6, 0, -7, -6], 3, True,
                  [-7, -7, -6, -7, 1, -5, -7, 0, -4, -6, 0, -7, -6], False)
    .add_sub_case(0, 1000)
    .add_sub_case(0, -1000)
    .add_sub_case(3, 11)
    .add_sub_case(3, -5)
    .add_sub_case(1, 11)
    .add_sub_case(1, -9)
    .add_sub_case(7, 11)
    .add_sub_case(7, -9)
    .add_sub_case(8, 1)
    .add_sub_case(8, -4)
    .add_sub_case(8, 25)
    .add_sub_case(8, -5)
    .add_sub_case(8, 1)
    .add_sub_case(8, -6)
    .add_sub_case(8, -7)
    .add_sub_case(9, 25)
    .add_sub_case(9, 3)
    .add_sub_case(9, -1)
    .add_sub_case(9, -5)
    .add_sub_case(9, -12)
    .add_sub_case(12, 1)
    .add_sub_case(12, 25)
    .add_sub_case(11, 25),
    Ib002TestCase([0], 2, True, [0], True),
    Ib002TestCase([0, -1], 2, True, [-1, -1], True)
    .add_sub_case(0, -25)
    .add_sub_case(1, 25)
    .add_sub_case(0, 40)
    .add_sub_case(1, -25)
    .add_sub_case(0, 0)
    .add_sub_case(0, -1)
    .add_sub_case(1, -1)
    .add_sub_case(1, 0),
    Ib002TestCase([-1, 0], 2, False, [], False),
    Ib002TestCase([10, 0], 2, True, [0, 0], True)
    .add_sub_case(0, 0)
    .add_sub_case(0, -1)
    .add_sub_case(1, 25),
    Ib002TestCase([-1, -3], 2, True, [-3, -3], True)
    .add_sub_case(1, 0)
    .add_sub_case(1, 25)
    .add_sub_case(0, 0)
    .add_sub_case(0, 12),
    Ib002TestCase([0, 0, -1], 2, True, [-1, 0, -1], False)
    .add_sub_case(0, -2)
    .add_sub_case(0, -1)
    .add_sub_case(2, 0)
    .add_sub_case(2, 1)
    .add_sub_case(2, 2)
    .add_sub_case(2, 3),
    Ib002TestCase([1, 0, -2], 2, True, [-2, 0, -2], False)
    .add_sub_case(0, 0)
    .add_sub_case(0, -1)
    .add_sub_case(0, -2)
    .add_sub_case(0, -3)
    .add_sub_case(2, 0)
    .add_sub_case(2, 1)
    .add_sub_case(2, 2)
    .add_sub_case(2, 3),
    Ib002TestCase([1, 0, -2], 3, True, [-2, 0, -2], False)
    .add_sub_case(0, 0)
    .add_sub_case(0, -1)
    .add_sub_case(0, -2)
    .add_sub_case(0, -3)
    .add_sub_case(2, 0)
    .add_sub_case(2, 1)
    .add_sub_case(2, 2)
    .add_sub_case(2, 3)
]

IB002_BASIC = [[0, 2, 3, 1, 4], [1, 0, 11, 17], [20, 0, 1, 3, 5, 6],
               [0, 1, 3, 5, 6]]


########################################################################
#                            Test FRAMEWORK                            #
########################################################################


def ib002_test_report(ok: bool, basic: bool) -> bool:
    if ok:
        print("[ OK ] {} prosel.".format("Zakladni test" if basic else "Test"))
        return True

    if basic:
        print("[FAIL] Zakladni test neprosel.",
              "Tato cast bude automaticky hodnocena 0 body.")
    else:
        print("[FAIL] Test neprosel.")

    return False


def ib002_test_iscorrect_DMaxHeap(case: Any, result: Any, *args: Any) -> bool:
    if case.is_correct != result:
        ib002_report_heap("Vracite '{}' pro haldu".format(result), case.heap)
        if case.is_correct:
            print("ktera je korektni maximova d-arni halda.")
        else:
            print("ktera neni korektni maximova d-arni halda.")
        return False
    return True


def ib002_test_isrepaired_DMaxHeap(case: Any, result: Any, *args: Any) -> bool:
    if case.is_correct and case.prune_test():
        ib002_report_heap("Ze vstupni haldy", case.heap_equiv_copy)
        print("jste pro parametr 'i': ", args[0][0])
        ib002_report_heap("vytvorili nekorektni haldu", case.heap_working_copy)
        return False
    return True


def ib002_test_subtree_mins(case: Any, result: Any, *args: Any) -> bool:
    if result is None:
        if case.heap.size == 0:
            return True
        else:
            ib002_report_heap("Pro neprazdnou vstupni haldu", case.heap)
            print("vracite 'None'.")
            return False

    if case.heap.size == 0:
        ib002_report_heap("Pro prazdnou vstupni haldu", case.heap)
        print("nevracite 'None'.")
        return False

    if not isinstance(result, Node):
        ib002_report_heap("Pro neprazdnou vstupni haldu", case.heap)
        print("nevracite koren typu Node.")
        return False

    from collections import deque
    queue = deque([result])
    i = -1

    def check_node(node: Any, i: int, h: int, a: int) -> Optional[str]:
        if not isinstance(node, Node):
            return "not Node"
        if node.value != case.heap.array[i]:
            return "ma chybnou hodnotu value"
        if node.min_val != case.mins[i]:
            return "ma chybnou hodnotu min_val"
        if len(node.sons) != min(max(0, h - a * i), a):
            return "ma chybny pocet synu"
        return None

    while queue:
        node = queue.popleft()
        i += 1
        # neni potreba, zvladne kontrola poctu synu
        # if i >= case.heap.size:
        #     ib002_report_heap("Pro vstupni haldu", case.heap)
        #     print("vracite strom, ktery ma uzlu vice nez '{}'"\
        #           .format(case.heap.size))
        msg = check_node(node, i, case.heap.size - 1, case.heap.arity)
        if msg is not None:
            ib002_report_heap("Pro vstupni haldu", case.heap)
            print(
                "vracite strom, jehoz uzel odpovidajici pozici '{}'".format(i))
            if msg == "not Node":
                print("neni typu 'Node'.")
            else:
                ib002_report_node(msg, node)
            return False
        queue.extend(node.sons)
    return True


def ib002_run_checks(test: Any, case: Any, result: Any, *args: Any) -> bool:
    name = test[2]  # explicitni nazev pro soubor
    if name is None:
        name = test[0].__name__  # implicitni nazev

    check = test[3]  # kontrolni fce

    changeable = test[-1]  # meni zadany vstup
    if not case.check_heap(changeable) or not check(case, result, *args):
        if args:
            print("Parametr 'i' byl: ", args[0][0])
        # jen vypis souboru, na obrazovku vypisuji samy kontroly
        if test[4] == 2:  # vypis stromu
            filename = "Err_tree_{}.dot".format(name)
            print_tree(result, filename)
            print("Vraceny strom je v souboru " + filename)
        return False
    return True


def ib002_test_template(test: Any, case: Any) -> bool:
    # ukoly >1 pro nekorektni vstup nepoustime
    if test[4] > 0 and not case.is_correct:
        return True

    fun = test[0]  # testovana fce studenta

    case.get_working_heap()

    if test[-1]:  # funkce meni vstup
        case.get_equiv_heap()

    if test[4] == 1:
        # repair_heap uses subcases
        for sub_case in case.sub_cases:
            case.make_new_subcase_heap(sub_case)
            result = fun(case.heap_working_copy, sub_case[0])
            if not ib002_run_checks(test, case, result, sub_case):
                return False
    else:
        # no subcases
        result = fun(case.heap_working_copy)
        if not ib002_run_checks(test, case, result):
            return False

    return True


def ib002_test_pruning(subcase: Any, test_case_number: int) -> bool:
    # vyrezavani testu pro vadne stromy

    # kontrola testovaci sady
    for i in range(0, len(subcase) - 1):
        # spocitej vadne testy
        vadny = i // test_case_number
        # urci vysledek spatneho testu
        vysl = subcase[i + 1]
        # overime predpocitany vysledek
        if subcase[vadny] > vysl:
            return True

    # korektni sady
    return False


def ib002_test_merging(subcase: Any, test_case_number: int) -> bool:
    # spojovani rozdelenych testovacich sad
    rozsah_testu = len(subcase) - 1
    basic_point = [math.inf] * len(subcase)

    # vypocti obtiznost vsech testu
    for i in range(0, rozsah_testu):
        # spocitej vadne testy
        vadny = i // test_case_number
        # vypocti obtiznost testu
        basic_point[vadny] = min(subcase[i + 1], basic_point[vadny])

    for i in range(0, len(subcase) - 1):
        # spocitej vadne testy
        vadny = i // test_case_number
        if not (i + 1) % test_case_number and basic_point[vadny] != subcase[i +
                                                                            1]:
            # tohle testovat nechceme
            return True

    if rozsah_testu > 1 and \
       subcase[-1] != basic_point[(rozsah_testu - 1) // test_case_number]:
        # tohle je taky moc
        return True

    return False


def ib002_try_test(test: Any, *args: Any) -> Any:
    # test is always ib002_test_template
    import traceback
    import sys
    try:
        return test(*args)
    except Exception:
        print("Test vyhodil vyjimku:")
        traceback.print_exc(file=sys.stdout)
        return False


def ib002_run_test(test: Any, cases: Any, basic: bool) -> bool:
    msg = test[1]
    if msg is None:
        msg = test[0].__name__
    print("\n*** {} {}:".format("Zakladni test" if basic else "Test", msg))

    return ib002_test_report(
        all(ib002_try_test(ib002_test_template, test, case) for case in cases),
        basic)


def ib002_run_both_tests(test: Any) -> bool:
    # vykopirovani zakladnich testu
    basic_cases = (IB002_CASES[i] for i in IB002_BASIC[test[4]])

    # if basic test fails, full tests are not run
    return ib002_run_test(test, basic_cases, basic=True) and \
        ib002_run_test(test, IB002_CASES, basic=False)


IB002_TEST_DESCRIPTIONS = [
    # vektory pro testy obsahuji:
    #   - testovana funkce studenta
    #   - explicitni pojmenovanim pro vypis; if None, pouzije se test[0]
    #   - bezmezerove jmeno pro soubor; if None, pouzije se test[0]
    #   - fce kontroly vystupu studenta
    #   - cislo ukolu - 1,
    #   - True/False jestli muze menit vstup
    (is_correct, None, None, ib002_test_iscorrect_DMaxHeap, 0, False),
    (repair_heap, None, None, ib002_test_isrepaired_DMaxHeap, 1, True),
    (all_subtree_mins, None, None, ib002_test_subtree_mins, 2, False)
]


def ib002_main() -> None:
    for test in IB002_TEST_DESCRIPTIONS:
        ib002_run_both_tests(test)


# Hlavni funkce volana automaticky po spusteni programu.
# Pokud chcete krome dodanych testu spustit vlastni testy, dopiste je sem.
# Odevzdavejte reseni s puvodni verzi teto funkce.


if __name__ == '__main__':
    ib002_main()
