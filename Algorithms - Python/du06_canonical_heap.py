#!/usr/bin/env python3

from typing import List

# Povolene knihovny: typing, math

# IB002 Domaci uloha 6.
#
# V nasledujicim textu pouzivame pojem "halda" ve vyznamu "binarni halda".
#
# Minimova halda je v kanonickem tvaru, pokud pro kazdy jeji prvek se dvema
# potomky plati, ze jeho levy potomek je mensi nez ten pravy nebo se oba
# rovnaji.
#
# Je v kanonickem tvaru | Neni v kanonickem tvaru
#                       |
#       (1)             |           (1)
#      /   \            |          /   \
#    (2)   (3)          |        (3)   (2)


# Trida representujici minimovou haldu. Pro praci s ni muzete s vyhodou pouzit
# funkce, ktere jste implementovali v zakladnim domacim ukolu.
# V teto implementaci indexujte od 0, tj. koren je na pozici heap.array[0].

class MinHeap:
    __slots__ = ("size", "array")

    def __init__(self) -> None:
        self.size: int = 0
        self.array: List[int] = []


# Ukol 1.
# Vasim prvnim ukolem je implementovat funkci is_canonical_min_heap(heap),
# ktera overi, zda je zadana halda 'heap' korektni minimovou haldou
# v kanonickem tvaru. Pokud ano, vrati True, v opacnem pripade vrati False.
#
# Prazdna nebo jednoprvkova halda je v kanonickem tvaru implicitne. Mejte na
# pameti, ze halda v kanonickem tvaru musi splnovat take pozadavky kladene na
# minimovou haldu.
def left(heap: MinHeap, parentIndex: int) -> int:
    return heap.array[2*parentIndex + 1]

def right(heap: MinHeap, parentIndex: int) -> int:
    return heap.array[2*parentIndex + 2]

def swap(heap: MinHeap, left: int, right: int) -> None:
    heap.array[left], heap.array[right] = heap.array[right], heap.array[left]

def is_canonical_min_heap(heap: MinHeap) -> bool:
    """
    vstup: 'heap' typu MinHeap
           (je zaruceno, ze heap.size je velikost pole heap.array;
            neni zaruceno, ze prvky heap.array splnuji haldovou podminku
            nebo podminku kanonickeho tvaru)
    vystup: True, pokud je 'heap' minimova halda v kanonickem tvaru
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet prvku 'heap'
    """
    if heap.size < 2:
            return True
    if heap.size == 2:
            return heap.array[0] <= heap.array[1]
    for i in range(heap.size//2):
            if heap.size <= 2*i + 2: # there's no right child
                    if heap.array[i] > left(heap, i): # parent is bigger than the child
                        return False
                        break
            elif heap.array[i] > left(heap, i) or left(heap, i) > right(heap, i): # parent is bigger than children, left child is same or smaller than right one
                    return False
    return True


# Ukol 2.
# Druhym ukolem je implementovat funkci canonise_min_heap(heap), ktera zadanou
# minimovou haldu 'heap' prevede na kanonicky tvar. Funkce bude menit primo
# haldu zadanou v argumentu, proto nebude vracet zadnou navratovou hodnotu.
#
# Napoveda:
# Pro algoritmus s linearni casovou slozitosti je potreba postupovat takto:
# - Rekurzivne resime od korene k listum haldy;
# - pro kazdy uzel haldy:
#   + zkontrolujeme, jestli potomci splnuji vlastnost kanonickeho tvaru;
#     pokud ne:
#     * prohodime hodnoty leveho a praveho potomka;
#     * tim se muze pokazit vlastnost haldy v pravem podstrome, proto
#       probublame problematickou hodnotu z korene praveho podstromu
#       tak hluboko, aby uz neporusovala vlastnost haldy (pri tomto bublani
#       opravujeme pouze vlastnost haldy, kanonicky tvar neresime)
#   + mame tedy korektni minimovou haldu, ktera navic splnuje kanonicky
#     tvar od tohoto uzlu smerem nahoru;
#   + pokracujeme v rekurzi vlevo a vpravo.

def canonise_min_heap(heap: MinHeap) -> None:
    """
    vstup: 'heap' korektni minimova halda typu MinHeap
    vystup: funkce nic nevraci, vstupni halda 'heap' je prevedena
            do kanonickeho tvaru (pritom obsahuje stejne prvky jako na zacatku)
    casova slozitost: O(n), kde 'n' je pocet prvku 'heap'
    """
    def bubble(heap: MinHeap, index: int) -> None:
        # print("bubble is called on index ", str(index))
        smallest = index
        if 2*index+1 < heap.size and heap.array[2*index+1] < heap.array[index]:
            smallest = 2*index+1
        if 2*index+2 < heap.size and heap.array[2*index+2] < heap.array[index] and heap.array[2*index+2] < heap.array[smallest]:
            smallest = 2*index+2
        if smallest != index:
                # print("bubble -> swapped: ", str(index), "[", str(heap.array[index]),"]", " and ", str(smallest),"[", str(heap.array[smallest]),"]")
                swap(heap, index, smallest)
                bubble(heap, smallest)
    def canonise(heap: MinHeap, index: int) -> None:
            if 2 * index + 2 >= heap.size:
                    return
            if left(heap, index) > right(heap, index):
                    swap(heap, 2 * index + 1, 2 * index + 2)
                    # print("canonise -> swapped: ", str(2 * index + 1), "[", str(heap.array[2*index+1]),"]", " and ", str(2*index+2),"[", str(heap.array[2*index+2]),"]")
                    bubble(heap, 2 * index + 2)
            canonise(heap, 2*index + 1)
            canonise(heap, 2*index + 2)
    canonise(heap, 0)
    pass  # TODO

heap0 = MinHeap()
heap0.array = []
heap0.size = 0

heap1 = MinHeap()
heap1.size = 1
heap1.array = [3]

heap2n = MinHeap()
heap2n.size = 2
heap2n.array = [1,0]

heap2y = MinHeap()
heap2y.size = 2
heap2y.array = [0,0]

heap3n = MinHeap()
heap3n.size = 3
heap3n.array = [3,2,1]

heap3y = MinHeap()
heap3y.size = 3
heap3y.array = [1,2,3]

heap4y = MinHeap()
heap4y.size = 4
heap4y.array = [1,2,3,3]

heap4n = MinHeap()
heap4n.size = 4
heap4n.array = [1,2,4,1]

heap5y = MinHeap()
heap5y.size = 5
heap5y.array = [1,2,3,3,5]

heap5n = MinHeap()
heap5n.size = 5
heap5n.array = [4,3,2,0,1]

heap3s = MinHeap()
heap3s.size = 3
heap3s.array = [1,1,1]

###########################

aheap5 = MinHeap()
aheap5.size = 5
aheap5.array = [1,3,2,5,3]

aheap4 = MinHeap()
aheap4.size = 4
aheap4.array = [1,3,2,3]

aheap3 = MinHeap()
aheap3.size = 3
aheap3.array = [1,3,2]

aheap2 = MinHeap()
aheap2.size = 2
aheap2.array = [1,2]

aheap0 = MinHeap()
aheap0.array = []
aheap0.size = 0

aheap1 = MinHeap()
aheap1.size = 1
aheap1.array = [3]

# print("be 0  true:  ", is_canonical_min_heap(heap0))
# print("be 1  true:  ", is_canonical_min_heap(heap1))
# print("be 2y true:  ", is_canonical_min_heap(heap2y))
# print("be 2n false: ", is_canonical_min_heap(heap2n))
# print("be 3y true:  ", is_canonical_min_heap(heap3y))
# print("be 3n false: ", is_canonical_min_heap(heap3n))
# print("be 4y true:  ", is_canonical_min_heap(heap4y))
# print("be 4n false: ", is_canonical_min_heap(heap4n))
# print("be 5y true:  ", is_canonical_min_heap(heap5y))
# print("be 5n false: ", is_canonical_min_heap(heap5n))
# print("be 3s true:  ", is_canonical_min_heap(heap3s))

# print(canonise_min_heap(aheap0))
# print(canonise_min_heap(aheap1))
# print(canonise_min_heap(aheap2))
# print(canonise_min_heap(aheap3))
# print(canonise_min_heap(aheap4))
# print(canonise_min_heap(aheap5))