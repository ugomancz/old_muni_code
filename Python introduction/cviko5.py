values = [52, 3, -5, -800, 23, 25, 185 , 12, 85, 154, 2, 5, 7]

def my_sum(values):
    final=0
    for i in values:
        final+=i
    return final

def my_max(values):
    max_value=0
    for i in values:
        if max_value<i:
            max_value=i
    return max_value

def my_in(n, values):
    a=False
    for i in values:
        if n==i:
            a=True
    return a

def my_min(values):
    min_value=my_max(values)
    for i in values:
        if min_value>i:
            min_value=i
    return min_value

def double_all(values):
    for i in range (len(values)):
        values[i]=values[i]*2
    return values

def dummy(text,x):
    text="text"
    
