#!/usr/bin/env python3

# Povolene knihovny: typing, math, collections
# Z knihovny collections je povolena pouze datova struktura deque
# reprezentujici frontu. Pro jeji import pouzijte presne nasledujici radek:
from collections import deque

from typing import List, Optional

# IB002 Domaci uloha 11.
#
# Tento tyden bude vasim ukolem implementovat dva grafove algoritmy.
# Ukoly jsou zamereny na aplikace pruchodu grafem.
#
# Reprezentace grafu je stejna jako v ukolu cv11, tedy matici sousednosti.
# Matice je indexovana od [0][0], vrcholum odpovidaji cisla 0 .. graph.size-1.
# V matici je na indexu [u][v] hodnota True, pokud graf obsahuje hranu u -> v,
# jinak je tam hodnota False.
#
# Grafy (i neorientovane!) mohou obsahovat smycky (tj. situace, kdy v matici
# na indexu [u][u] je True) a mohou byt i nesouvisle.
#
# Pripomenuti prace s frontou typu deque:
# inicializace fronty: queue = deque() nebo queue = deque([seznam prvku])
# vlozeni prvku do fronty: queue.append(prvek)
# vybrani prvku z fronty: queue.popleft(prvek)
#
# Definici tridy Graph nijak nemodifikujte, ani nepridavejte zadne atributy.
# Zamerne se v teto uloze budete muset obejit bez pomocnych poli ve tride
# Graph; budete muset pouzit lokalni promenne a pripadne parametry v rekurzi.
#
# V teto uloze je zakazano pouzivat datove struktury set (mnoziny) a dict
# (slovniky). Uvedomte si, ze vrcholy grafu jsou vzdy cisla od 0 do size - 1.


class Graph:
    """Trida Graph drzi graf reprezentovany matici sousednosti.
    Atributy:
        size: velikost (pocet vrcholu) grafu
        matrix: matice sousednosti
                [u][v] reprezentuje hranu u -> v
    """
    __slots__ = ("size", "matrix")

    def __init__(self, size: int) -> None:
        self.size: int = size
        self.matrix: List[List[bool]] = [[False] * size for _ in range(size)]


# Ukol 1.
# Implementujte funkci colourable, ktera zjisti, zda je dany neorientovany graf
# obarvitelny dvema barvami tak, aby kazde dva sousedni vrcholy mely ruznou
# barvu.
#
# Neorientovany graf v nasi reprezentaci znamena, ze
#    graph.matrix[u][v] == graph.matrix[v][u] pro vsechny vrcholy u, v.

def colourable(graph: Graph) -> bool:
    """Zjisti, zda je zadany neorientovany graf obarvitelny dvema barvami.
    Vstup:
        graph - neorientovany graf typu Graph
    Vystup:
        True, pokud je graf obarvitelny dvema barvami
        False, jinak
    casova slozitost: O(n^2), kde n je pocet vrcholu grafu
    extrasekvencni prostorova slozitost: O(n), kde n je pocet vrcholu grafu
    """
    def opc(color):
        if color == "blue":
            return "red"
        return "blue"
    colors = ["none"] * graph.size
    q = deque()
    q.append(0)
    colors[0] = "red"
    while len(q) != 0:
        curr = q.popleft()
        for i in range(graph.size):
            if graph.matrix[curr][i]:
                if colors[i] == "none":
                    colors[i] = opc(colors[curr])
                    q.append(i)
                elif colors[i] == colors[curr]:
                    return False
    return True



# Ukol 2.
# Implementujte funkci compute_dependencies, ktera pro zadany orientovany graf
# spocita topologicke usporadani vrcholu, tj. ocislovani vrcholu takove, ze
# kazda hrana vede z vrcholu s nizsim cislem do vrcholu s vyssim cislem.
#
# Vystupem je pole zadavajici topologicke usporadani (ocislovani vrcholu),
# kde na prvni pozici (tedy s indexem 0) je vrchol nejmensi
# v tomto usporadani, tj. nevede do nej zadna hrana,
# a na posledni pozici vrchol nejvetsi, tj. nevede z nej zadna hrana.
# Pokud topologicke usporadani neexistuje, algoritmus vraci None.
#
# Priklad:
#    mejme graf s vrcholy 0, 1, 2 a hranami 0 -> 1, 2 -> 1, 2 -> 0;
#    vystupem bude pole (Pythonovsky seznam] [2, 0, 1]

def compute_dependencies(graph: Graph) -> Optional[List[int]]:
    """Spocita topologicke usporadani vrcholu v grafu.
    Vstup:
        graph - orientovany graf typu Graph
    Vystup:
        pole cisel reprezentujici topologicke usporadani vrcholu
        None, pokud zadne topologicke usporadani neexistuje
    casova slozitost: O(n^2), kde n je pocet vrcholu grafu
    extrasekvencni prostorova slozitost: O(n), kde n je pocet vrcholu grafu
    """
    return []  # TODO

###############################################################################

def is_root(g, n):
    for i in range(g.size):
        if (g.matrix[i][n]):
            return False
    return True


def vert_neighbours(g, n):
    for i in range(g.size):
        if g.matrix[n][i]:
            yield i

            
def str_dot_graph(g):
    s = "\ndigraph g {\n"

    for i in range(g.size):
        s += str(i) + "\n"

    for i in range(g.size):
        for j in range(g.size):
            if (g.matrix[i][j]):
                s += ("%i -> %i\n" %(i, j))

    s += "}\n"
    return s


def is_top(g, n):
    # are no other nodes pointing at me?
    for i in range(g.size):
        if (g.matrix[i][n]):
            return False
    return True


def is_cyclic_rec(g, n, visited):
    if visited[n] == 1:
        return True
   
    if visited[n] == 2:
        return False
 
    visited[n] = 1
 
    neighbours = vert_neighbours(g, n)
 
    for ne in neighbours:
        if is_cyclic_rec(g, ne, visited):
            return True
 
    visited[n] = 2
    return False
 

def is_cyclic(g):
    visited = [0] * g.size
    for i in range(g.size):
        if not visited[i]:
            if is_cyclic_rec(g, i, visited):
                return True
    return False


def is_correct_topo(g, topo):
    for i in range(len(topo)):
        if is_top(g, topo[i]):
            continue
        bad = True
        for j in range(i):
            if topo[i] in vert_neighbours(g, topo[j]):
                bad = False
                break
        if bad:
            return False
    return True
   
 
import unittest, random
 
class Testing(unittest.TestCase):
    def test_simple_dependencies(self):
        g = Graph(3)
        g.matrix[0] = [0, 1, 0]
        g.matrix[1] = [0, 0, 0]
        g.matrix[2] = [0, 1, 0]
 
        dep = compute_dependencies(g)
        self.assertTrue((dep == [2, 0, 1] or dep == [0, 2, 1]))
       
   
    def test_depe_cyclic_random_graph(self):
        for _ in range(10000): # * 100
            g = Graph(7)
 
            for i in range(g.size):
                g.matrix[i] = [random.choice([True, False, False]) for _ in range(g.size)]
 
            dep = compute_dependencies(g)
 
            if dep is None:
                self.assertTrue(is_cyclic(g), str_dot_graph(g)
                                + "\nReturned None but this graph is not cyclic!")
            else:
                self.assertFalse(is_cyclic(g), str_dot_graph(g)
                                 + "\nReturned topologicaly sorted vertices on graph that is cyclic!")
                self.assertTrue(is_correct_topo(g, dep), str_dot_graph(g)
                                 + "\nReturned vertices are not topologicaly sorted.\n"
                                 + str(dep) + "\nWebgraphviz might help you. ")
 
 
    def test_random_cyclic_colorable(self):
        for i in range(3, 30):
            g = Graph(i)
 
            for j in range(i):
                g.matrix[j][(j+1)%i] = True
                g.matrix[(j+1)%i][j] = True
 
            if (i % 2 == 1):
                self.assertFalse(colourable(g), str_dot_graph(g)
                                 + "\nUndirected graph with odd cycle isn't colorable!")
            else:
                self.assertTrue(colourable(g), str_dot_graph(g)
                                + "\nUndirected graph with even cycle should be colorable!")
 
    def test_random_double_cyclic_colorable(self):
        for _ in range(100000):
            g = Graph(50)
            c1 = random.randint(3, 20)
            c2 = random.randint(3, 20)
       
            for j in range(c1):
                g.matrix[j][(j+1)%c1] = True
                g.matrix[(j+1)%c1][j] = True
 
            for j in range(c2):
                g.matrix[25+j][25+(j+1)%(c2)] = True
                g.matrix[25+(j+1)%(c2)][25+j] = True
 
            if (c1 % 2 == 0 and c2 % 2 == 0):
                self.assertTrue(colourable(g), str_dot_graph(g)
                                + "\nUndirected graph with two even cycles should be colorable!")
            else:
                self.assertFalse(colourable(g), str_dot_graph(g)
                                + "\nUndirected graph with one or more odd cycles isn't be colorable!")
 
       
    def test_random_adv_cyclic_colorable(self):
        # three joined cycles, all are even.
        for _ in range(1000):
            g = Graph(50)
            c1 = random.randint(2, 10) * 2
            c2 = random.randint(2, 10) * 2
 
            for j in range(c1):
                g.matrix[j][(j+1)%c1] = True
                g.matrix[(j+1)%c1][j] = True
 
            g.matrix[c1-1][25] = True
            g.matrix[25][c1-1] = True
            g.matrix[25+c2][c1-3] = True
            g.matrix[c1-3][25+c2] = True
 
            for j in range(c2):
                g.matrix[25+j][25+j+1] = True
                g.matrix[25+j+1][25+j] = True
 
            self.assertTrue(colourable(g), str_dot_graph(g))
           
           
def perf(func):
    def wrapper_perf(*args, **kwargs):
        start = time.process_time()
        func(*args, **kwargs)
        stop = time.process_time()
        #print("CPU process time: %.1f [sec]" % (stop-start))
        return stop - start
 
    return wrapper_perf
 
 
@perf
def perf_colourable(g):
    colourable(g)
 
 
@perf
def perf_dependencies(g):
    compute_dependencies(g)
 
 
def colourable_complexity():
 
    odd_sizes = []
    even_sizes = []
    odd_times = []
    even_times = []
   
    TRIES = 20
   
    for g_size in range(3, 500):
        g = Graph(g_size)
 
        for j in range(g_size):
            g.matrix[j][(j+1)%g_size] = True
            g.matrix[(j+1)%g_size][j] = True
 
        if (g_size % 2 == 0):
            even_sizes.append(g_size ** 2)
            even_times.append(sum([perf_colourable(g) for _ in range(TRIES)]) * 1000 / TRIES)
            print("Colourable for graph with %i vertices took %.1f [msec] (even) " % (g_size, even_times[-1]))
        else:
            odd_sizes.append(g_size ** 2)
            odd_times.append(sum([perf_colourable(g) for _ in range(TRIES)]) * 1000 / TRIES)
            print("Colourable for graph with %i vertices took %.1f [msec] (odd)" % (g_size, odd_times[-1]))
 
    plt.plot(odd_sizes, odd_times, "-", label="Odd graph size")
    plt.plot(even_sizes, even_times, "-", label="Even graph size")
   
    plt.title("colourable() time complexity")
    plt.xlabel("Squared graph size (n^2)")
    plt.ylabel("CPU time [msec]")
    plt.legend()
    #plt.savefig("g.png", dpi=400)
    plt.show()
 
def dependencies_complexity():
    times = []
    sizes = []
   
    TRIES = 20
   
    for g_size in range(3, 300):
        # upper triangle graph:
        # [0 1 1 ...  1]
        # [0 0 1 ...  1]
        # ...
        # [0 0 0 ...  0]
        g = Graph(g_size)
 
        for i in range(g_size):
            for j in range(i + 1, g_size):
                g.matrix[i][j] = True
       
        sizes.append(g_size ** 2)
        times.append(sum([perf_dependencies(g) for _ in range(TRIES)]) * 1000 / TRIES)
        print("Dependencies for graph with %i vertices took %.1f [msec]" % (g_size, times[-1]))
   
    plt.plot(sizes, times, "-")
                 
    plt.title("compute_dependencies() time complexity")
    plt.xlabel("Squared graph size (n^2)")
    plt.ylabel("CPU time [msec]")
    #plt.legend()
    #plt.savefig("g.png", dpi=400)
    plt.show()
   
 
if __name__ == '__main__':
     unittest.main()
 
     import matplotlib.pyplot as plt
     import random
     import string
     import time

     print('uncomment colourable_complexity() and dependencies_complexity() for benchmark')
     #colourable_complexity()
     #dependencies_complexity()