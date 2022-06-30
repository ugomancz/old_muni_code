"""
uco: 469007
jmeno: Ondřej Kostík
hw: 1
"""
"""
import turtle mám na začátku jednotlivých funkcí (okno se neotevře na popředí),
pokud se však okno se želví grafikou na konci funkce zavře, musí se následující použítá
funkce zavolat 2x, poprvé to totiž napíše error a otevře prázdné okno se želví grafikou
"""
def alternating_multiples(n):
    i=1
    print(n, end="; ")
    for c in range(5):
        b=i*2
        print("-",n*b, end="; ")
        x=b+1
        print(n*x, end="; ")
        i=i+1
"""
nejspíš je na ty násobky nějaká sofistikovanější metoda,
ale na nic lepšího jsem nepřišel
"""

def crossing(n, length):
    f=length+2
    for i in range(n):
        for z in range(f):          #plný řádek
            print("#", end=" ")
        print("")
        print("#", end=" ")
        for x in range(length):     #prázdný řádek
            print(" ", end=" ")
        print("#", end=" ")
        print("")
    for y in range(f):              #poslední řádek
        print("#", end=" ")

def mocniny(m, exponent):
    for i in range(2):              #odsazení
        print(" ", end=" ")
    for i in range(1, m+1):         #"názvy" sloupců
        print(i, end=" ")
    print()
    for i in range(2):              #odsazení
        print(" ", end=" ")
    for g in range(m):              #ohraničení tabulky
        print("-", end=" ")
    print()
    for lines in range(1, exponent+1):
        print(lines, end=" | ")     #ohraničení tabulky
        for sloupec in range(1, m+1):
            c=m-sloupec
            x=m-c
            print(x**lines, end=" ")
        print()

def castle(towers, side, space):
    from turtle import Turtle, done
    paja = Turtle()
    paja.speed(150)
    for i in range(towers-1):
        for x in range(4):          #věže
            paja.forward(side)
            paja.left(90)
        paja.left(90)
        paja.forward(side)
        paja.right(30)
        paja.forward(side)
        paja.right(120)
        paja.forward(side)
        paja.right(30)
        paja.forward(side)
        paja.left(90)
        for y in range(space):      #mezery mezi věžemi
            for w in range(4):
                paja.forward(side)
                paja.left(90)
            paja.forward(side)
    for x in range(4):
        paja.forward(side)
        paja.left(90)
    paja.left(90)                   #poslední věž
    paja.forward(side)
    paja.right(30)
    paja.forward(side)
    paja.right(120)
    paja.forward(side)
    paja.right(30)
    paja.forward(side)
    paja.left(90)

def python(side):
    from turtle import Turtle, done
    paja = Turtle()
    paja.speed(200)
    b=side**2 + (side/2)**2
    c=b**0.5-0.5
    paja.left(90)
    for i in range(3):                  #ocas
        paja.forward(side)
        paja.left(120)
    paja.right(90)
    for i in range(7):                  #části těla
        paja.forward(2*side)
        paja.left(90)
        paja.forward(side)
        paja.left(90)
        paja.forward(2*side)
        paja.left(90)
        paja.forward(side)
        paja.left(90)
        paja.forward(side)
        paja.left(150)
        paja.forward(c-1.5)
        paja.right(120)
        paja.forward(c-1.5)
        paja.right(60)
        paja.forward(c-1.5)
        paja.right(120)
        paja.forward(c-1.5)
        paja.left(150)
        paja.forward(side)
    paja.right(30)                      #hlava
    paja.forward(side/3)
    paja.left(40)
    paja.forward(side*1.5)
    paja.left(80)
    paja.forward(side*0.8)
    paja.left(80)
    paja.forward(side*1.5)
    paja.left(40)
    paja.forward(side/3)
    paja.penup()
    paja.left(60)
    paja.forward(0.3*side)
    paja.left(90)
    paja.forward(side/2)
    paja.pendown()
    for i in range(4):
        paja.left(90)
        paja.forward(0.1*side)
    paja.penup()
    paja.right(90)
    paja.forward(0.4*side)
    paja.pendown()
    for i in range(4):
        paja.left(90)
        paja.forward(0.1*side)
    paja.penup()
    paja.left(90)
    paja.forward(1.25*side)
    paja.left(90)
    paja.forward(side/5)
    paja.right(90)
    paja.pendown()
    for i in range(8):                  #jazyk
        paja.left(6)
        paja.forward(side/8)
    paja.left(30)
    paja.forward(side/3)
    paja.left(180)
    paja.forward(side/3)
    paja.right(150)
    paja.forward(side/3)
    paja.penup()
    paja.left(150)
    paja.forward(side*10)
