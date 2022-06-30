"""
hw3
Kostík, 469007
"""

from random import randint


def newplan(n, m):      # vytvori plan podle uvodnich pozadavku
    plan = []
    for i in range(n):
        plan.append([])
        for _ in range(m):
            plan[i].append(0)
    return plan


def printplan(rows, columns):   # vytiskne plan do "lidske" podoby
    for i in range(rows):
        for h in range(columns):
            if plan[i][h] == 1:
                print("X", end=" ")
            elif plan[i][h] == 2:
                print("O", end=" ")
            else:
                print(" ", end=" ")
        print()
    for _ in range(columns):
        print("-", end=" ")
    print()
    for i in range(columns):
        print(i + 1, end=" ")
    print()


def wincheck(m, n):     # funkce pro kontrolu výhry
    for x in range(1, 3):
        for i in range(m - 3):
            for h in range(n - 3):
                if plan[i][h] == x and plan[i + 1][h + 1] == x and \
                        plan[i + 2][h + 2] == x and plan[i + 3][h + 3] == x:
                    return x

        for i in range(m - 3):
            for h in range(n - 3):
                if plan[i][-h - 1] == x and plan[i + 1][-h - 2] == x and \
                        plan[i + 2][-h - 3] == x and plan[i + 3][-h - 4] == x:
                    return x

        for i in range(m - 3):
            for h in range(n):
                if plan[i][h] == x and plan[i + 1][h] == x and \
                        plan[i + 2][h] == x and plan[i + 3][h] == x:
                    return x

        for i in range(m):
            for h in range(n - 3):
                if plan[i][h] == x and plan[i][h + 1] == x and \
                        plan[i][h + 2] == x and plan[i][h + 3] == x:
                    return x
    return 0


def pcturn(m, n):       # tah počítače
    found_space = False
    while not found_space:
        x = randint(0, m - 1)
        found_space = plan[1][x] == 0

    for i in range(1, len(plan)):
        if plan[-i][x] == 0:
            plan[-i][x] = 2
            break


def play(rows, columns, human_starts):      # samotná hra
    global plan
    plan = newplan(rows, columns)
    print("Hra začíná:")
    if not human_starts:
        pcturn(columns, rows)
    win = 0
    while win == 0:
        printplan(rows, columns)
        columnraw = input("Vyberte sloupec: ")
        column = int(columnraw) - 1
        for i in range(1, len(plan)):
            if plan[-i][column] == 0:
                plan[-i][column] = 1
                break
        printplan(rows, columns)
        pcturn(columns, rows)
        win = wincheck(rows, columns)
    if win == 1:
        print("Vyhráli jste!")
    elif win == 2:
        print("Vyhrál počítač!")


def tictactoe(rows, cols, human_starts):        # spuštění hry
    play(rows + 1, cols, human_starts)


tictactoe(5, 5, True)
