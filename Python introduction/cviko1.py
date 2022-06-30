from turtle import Turtle, done
julie = Turtle()
def square(side):
    for i in range(4):
        julie.forward(side)
        julie.right(90)

def triangle(side):
    for i in range(3):
        julie.forward(side)
        julie.left(120)

def pentagon(side):
    for i in range(5):
        julie.forward(side)
        julie.right(72)
        
def nevim(side):
    for i in range(2):
        julie.forward(side)
        julie.right(45)
        julie.forward(side)
        julie.right(45)
        julie.forward(side)
        julie.right(90)
        
def nuhelnik(n,side):
    angle=360//n
    for i in range(n):
        julie.forward(side)
        julie.left(angle)

def bludiste(n,side,c):
    angle=360//n
    for i in range(c):
        julie.forward(side)
        julie.left(angle)
        julie.forward(side+i*5)    
    
