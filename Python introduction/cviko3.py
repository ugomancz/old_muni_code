def series_sum(n):
    sum=0
    for i in range(n+1):
        sum+=i
    return sum

def factorial(n):
    number=1
    for i in range(n):
        number*=i+1
    return number

def divisors(n):
    for i in range(1,n+1):
        if n%i == 0:
            print(i, end="; ")
    print()

def approximation(n):
    result=0
    for i in range(0,n):
        result+=1/factorial(i)
    return result
