from random import randint

def guess_human_number(upper_bound):
    number=randint(1,upper_bound)
    while True:
        guess=int(input("Guess a number: "))
        if guess == number:
            print("You win")
            break;
        elif guess < number:
            print("Higher one")
        else:
            print("lower one")


def guess_Pc_number(upper_bound):
    print("Think of a number from 1 to ", upper_bound)
    number=randint(1,upper_bound)
    while True:
        print("Is ", number, " higher(h), lower(l) or the same(s)?")
        answer=(input())
        if answer=="s":
            print("your number is ",number)
            break;
        elif answer=="h":
            temp=number
            number=randint(1,temp)
        else:
            temp=number
            number=randint(temp,upper_bound)

#guess_Pc_number(10)

def guesspcpc(upper_bound):
    print("Think of a number from 1 to ", upper_bound)
    number=randint(1,upper_bound)
    tru=randint(1, upper_bound)
    tries=1
    while True:
        print("A: Is ", number, " higher(h), lower(l) or the same(s)?")
        if tru==number:
            print("B: yep, thats the one")
            print("A: your number is ",number)
            print("it took: ",tries,"tries")
            break;
        elif tru<number:
            print("B: nope, its higher")
            temp=number
            number=randint(1,temp)
            tries+=1
        else:
            print("B: nope its lower")
            temp=number
            number=randint(temp,upper_bound)
            tries+=1
