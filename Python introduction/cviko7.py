def triangle(n):
    alist=[]
    inlist=[1]
    for i in range(n):
        alist.append((i+1)*inlist)
    return alist

triangle(0)
