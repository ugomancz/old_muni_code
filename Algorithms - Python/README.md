Done in the spring semester of 2020.

## du01_linkedlist
tests OK
```
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
```
```
def double(linked_list):
    """
    vstup: `linked_list` - korektni jednosmerne zretezeny seznam
    vystup: zadny, vstupni seznam `linked_list` je zdvojeny (viz priklad)
            (samozrejme, seznam musi zustat korektni)
    casova slozitost: O(n), kde n je delka vstupniho seznamu

    priklad: pro vstup -> 17 -> 42 -> 0 -> -7 bude seznam modifikovan na
             -> 17 -> 42 -> 0 -> -7 -> 17 -> 42 -> 0 -> -7
    """
```
## du02_circularlist
tests OK
```
def is_circular(node: Node) -> bool:
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: True, pokud je seznam z uzlu 'node' kruhovy
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    """
```
```
def get_length(node: Node) -> int:
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: pocet prvku v zadanem seznamu
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    """
```
```
def calculate_opposites(node: Node) -> None:
    """
    vstup: 'node' prvni uzel seznamu, ktery je linearni, nebo kruhovy
    vystup: nic, kokretne doplni atribut opposite pro kruhovy seznam sude delky
    casova slozitost: O(n), kde 'n' je pocet prvku seznamu
    prostorova slozitost: 1 (konstantni)
    """
```
## du03\_find\_first
tests OK, used solution from the spring semester of 2019
```
def find_first_occurrence(key: int, numbers: List[int]) -> int:
    """
    vstup: 'key' hodnota hledaneho cisla, 'numbers' serazene pole cisel
    vystup: index prvniho vyskytu hodnoty 'key' v poli 'numbers',
            -1, pokud se tam tato hodnota nevyskytuje
    casova slozitost: O(log n), kde 'n' je pocet prvku pole 'numbers'
    """
```
```
def find_first_greater(key: int, numbers: List[int]) -> int:
    """
    vstup: 'key' hodnota hledaneho cisla, 'numbers' serazene pole cisel
    vystup: index prvniho vyskytu prvku vetsiho nez hodnota 'key',
            -1, pokud tam zadny takovy prvek neni
    casova slozitost: O(log n), kde 'n' je pocet prvku pole 'numbers'
    """
```
## du04\_trit\_sum
tests OK
```
def trit_sum(length: int, total: int) -> List[List[int]]:
    """
    vstup: `length` - nezaporne cele cislo
           `total` - cele cislo
    vystup: seznam vsech poli delky presne `length`,
            jejichz soucet je presne `total`
    casova slozitost: O(T(length, total) * length^2),
        kde T(length, total) je hodnota z tabulky naznacene vyse
    """
```
## du06\_canonical\_heap
tests OK
```
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
```
```
def canonise_min_heap(heap: MinHeap) -> None:
    """
    vstup: 'heap' korektni minimova halda typu MinHeap
    vystup: funkce nic nevraci, vstupni halda 'heap' je prevedena
            do kanonickeho tvaru (pritom obsahuje stejne prvky jako na zacatku)
    casova slozitost: O(n), kde 'n' je pocet prvku 'heap'
    """
```
## du07\_binary\_trees
tests OK, used solution from the spring semester of 2019
```
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
```
```
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
```
```
def remove_zero_leaves(tree: SumTree) -> None:
    """
    vstup: 'tree' korektni souctovy strom typu SumTree
    vystup: zadny, ze stromu 'tree' jsou vymazany vsechny listy s hodnotou 0
            (vcetne vsech listu s hodnotou 0, ktere vzniknou timto mazanim)
    casova slozitost: O(n), kde 'n' je pocet prvku puvodniho 'tree'
    """
```
## duspec
2/3 tests + advanced tests OK. Working with d-ary max heap
```
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
```
```
def repair_heap(heap: DMaxHeap, i: int) -> None:
    """
    vstup: 'heap' d-arni halda typu DMaxHeap
           'i'    index prvku, ktery jediny muze porusovat vlastnost haldy
    vystup: zadny, presklada prvky v 'heap' tak, aby byla korektni d-arni
            maximovou haldou
    casova slozitost: O(d * log(n)), kde n je pocet prvku v halde
    extrasekv. prostorova slozitost: O(log(n)), kde n je pocet prvku v halde
    """
```
```
def all_subtree_mins(heap: DMaxHeap) -> Optional[Node]:
    """
    vstup: 'heap' korektni d-arni halda typu DMaxHeap
    vystup: koren (typu Node) stromove reprezentace haldy
               (vcetne minimalnich hodnot)
            None pro prazdnou haldu
    casova slozitost: O(n), kde n je pocet hodnot v halde
    """
```

## du09\_ballanced\_bst
tests NOK, didn't do
```
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
```
```
def check_almost_complete(tree: BSTree) -> bool:
    """
    vstup: 'tree' binarni vyhledavaci strom typu BSTree
    vystup: True, pokud je 'tree' skoro uplny
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet uzlu stromu
    extrasekvencni prostorova slozitost: O(h), kde h je vyska stromu
        (nepocitame vstup, pocitame zasobnik rekurze)
    """
```
```
def check_all_leaves_same_depth(tree: BSTree) -> bool:
    """
    vstup: 'tree' binarni vyhledavaci strom typu BSTree
    vystup: True, pokud jsou vsechny listy 'tree' ve stejne hloubce
            False, jinak
    casova slozitost: O(n), kde 'n' je pocet uzlu stromu
    extrasekvencni prostorova slozitost: O(h), kde h je vyska stromu
        (nepocitame vstup, pocitame zasobnik rekurze)
    """
```

## du10\_filesystem
tests OK
```
def cd(current: Directory, path: str) -> Optional[Directory]:
    """Vrati adresar, do nejz se dostaneme z adresare current po pruchodu
       cestou path.

    Vstup:
       current typu Directory -- aktualni adresar
       path -- neprazdny retezec s cestou
               nezacina ani nekonci znakem '/', neobsahuje dve '/' za sebou

    Casova slozitost: linearni vuci delce (poctu segmentu) zadane cesty
        (ale viz poznamku nahore o ignorovani slozitosti nekterych operaci)
    """
```
```
def mkdirp(current: Directory, path: str) -> None:
    """Vytvori vsechny adresare po zadane ceste ze zadaneho aktualniho
       adresare. Existujici adresare nechava v puvodnim stavu.

    Vstup:
       current typu Directory -- aktualni adresar
       path -- neprazdny retezec s cestou
               nezacina ani nekonci znakem '/', neobsahuje dve '/' za sebou

    Casova slozitost: linearni vuci delce (poctu segmentu) zadane cesty
        (ale viz poznamku nahore o ignorovani slozitosti nekterych operaci)
    """
```
```
def find(current: Directory, pattern: str) -> List[Directory]:
    """Najde vsechny adresare v podstrome danem aktualnim adresarem,
       jejichz jmena obsahuji zadany retezec.

    Vstup:
       current typu Directory -- aktualni adresar
       pattern -- vyhledavany podretezec, neobsahuje znak '/', ale muze byt
                  i prazdny (pak zadani splnuji vsechny podadresare ve strome)

    Casova slozitost: linearni vuci velikosti podstromu aktualniho adresare
        (ale viz poznamku nahore o ignorovani slozitosti nekterych operaci)
    """
```

## du11\_graph\_algorithms
tests NOK, didn't figure it out
```
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
```
```
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
```

## du12\_graph\_relation
\# TODO
```
def is_reflexive(graph: Graph) -> bool:
    """Zjisti, zda je relace zadana grafem reflexivni.
    Vstup: graph - orientovany graf typu Graph
    Vystup: True/False
    casova slozitost: O(n), kde n je pocet vrcholu grafu
    extrasekvencni prostorova slozitost: O(1)
    """
```
```
def is_symmetric(graph: Graph) -> bool:
    """Zjisti, zda je relace zadana grafem symetricka.
    Vstup: graph - orientovany graf typu Graph
    Vystup: True/False
    casova slozitost: O(n^2), kde n je pocet vrcholu grafu
    extrasekvencni prostorova slozitost: O(1)
    """
```
```
def is_antisymmetric(graph: Graph) -> bool:
    """Zjisti, zda je relace zadana grafem antisymetricka.
    Vstup: graph - orientovany graf typu Graph
    Vystup: True/False
    casova slozitost: O(n^2), kde n je pocet vrcholu grafu
    extrasekvencni prostorova slozitost: O(1)
    """
```
```
def is_transitive(graph: Graph) -> bool:
    """Zjisti, zda je relace zadana grafem tranzitivni.
    Vstup: graph - orientovany graf typu Graph
    Vystup: True/False
    casova slozitost: O(n^3), kde n je pocet vrcholu grafu
    extrasekvencni prostorova slozitost: O(1)
    """
```
```
def transitive_closure(graph: Graph) -> Graph:
    """Vypocita tranzitivni uzaver zadaneho grafu.
    Vstup: graph - orientovany graf typu Graph
    Vystup: tranzitivni uzaver grafu (objekt typu Graph)
    casova slozitost: O(n^3), kde n je pocet vrcholu grafu
    """
```