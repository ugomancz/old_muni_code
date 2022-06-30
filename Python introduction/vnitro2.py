"""
vnitro2
Ondřej Kostík
učo: 469007
"""
from random import randint


def diagonal_sum(matrix):
    result = 0
    for i in range(len(matrix)):        # určí počet prvků na diagonále
        result += matrix[i][i]      # sečte prvky na diagonále
    print(result)


def recursive_len(text):        # pro každý znak textu přičte 1
    if len(text) != 0:      # běží rekurzivně, dokud nedojde text
        return 1 + recursive_len(text[1:])
    else:
        return 0


def jan_ken_pon(count):
    result = listf(count)       # vytvoří list nul o délce "count"
    for i in range(count):      # cyklus jednotlivých her
        play = game()       # funkce game() nám vrací 1 (kámen) nebo 2 (papír)
        while play == 1:        # každá hra se opakuje dokud nevyjde papír
            result[i] += 1
            play = game()
        else:
            play = game()
    stats(result)       # funkce stats nám vypíše statistiky


def listf(x):       # vytvoří list nul o požadované délce
    alist = []
    for _ in range(x):
        alist.append(0)
    return alist


def game():     # určuje zda padne kámen nebo papír
    x = randint(1, 3)
    if x == 1:
        return 1
    if x == 2:
        return 2


def stats(final):       # vrátí statistiky číselného seznamu
    results = final
    average = 0
    for i in range(len(results)):
        average += results[i]
    average = average/len(results)
    print("Average:", average, "min:", min(results), "max:", max(results))

books = "Petr:Hobbit,Name of the Rose,1984,Robin Hood;Paul:;John:Mystery of the teaser,Hobbit;Martin:1984,Hobbit"


def book_frequency(books):
    people = books.split(";")
    almosttitles = []
    titles = []
    for i in range(len(people)):
        almosttitles.append(people[i].split(":"))
    for i in range(len(almosttitles)):
        titles.append(almosttitles[i][1])
    eachtitles = []
    for i in range(len(titles)):
        if len(titles[i]) != 0:
            eachtitles.append(titles[i].split(","))
    final = []
    for i in range(len(eachtitles)):
        for h in range(len(eachtitles[i])):
            final.append(eachtitles[i][h])
    therewego = set(final)
    for item in therewego:
        print(item, "appears", final.count(item), "times")


class Student:
    def __init__(self, name, uco):
        self.name = name
        self.uco = uco


class Course:
    def __init__(self, code, room):
        self.code = code
        self.students = []
        self.room = room

    def add_student(self, student):
        self.student.append(sstudent)


class Room:
    def __init__(self, code, capacity):
        self.code = code
        self.capacity = capacity

    def capacity_checker(courses):
        for i in range(len(courses)):
            if len(courses[i].students) < courses[i].room.capacity:
                print(courses[i], "ano")
            else:
                print(courses[i], "ne")


book_frequency(books)
