def evennumbers(x):
    for i in range(0,x*2,2):
        print(i+2,end=" ")
def unevennumbers(x):
    for i in range(0,x*2,2):
        print(i+1,end=" ")
def powers(base, x):
    for i in range(x):
        print(base**i, end=" ")
def fibonacci(n):
    x=0
    y=1
    print("0 1", end=" ")
    for i in range(n-2):
        z=x+y
        x=y
        y=z
        print(z, end=" ")
        
def square(n):
    for i in range(n):
        for x in range(n):
            print("#", end=" ")
        print("")

def pyramid(n):
    if n<16:
        for i in range(n-1):
            w=n-i*2+n//(n//4)
            c=(n + 5 //2) //5
            b=(w + 2 //2) //2
            o=10//n*2
            for h in range(b+c+o):
                print(" ", end=" ")
            for x in range(i*2+2):
                print("#", end=" ")
            print("")
    else:
        print("nelze")

def table(n):
    for g in range(n+1):
        print(g, end=" ")
    print()
    for i in range(n):
        print(i+1, end=" ")
        for x in range(n):
            print((i+1)*(x+1), end=" ")
        print("")
