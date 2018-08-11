import math

t = int(raw_input())
for j in range(t):
    inp = raw_input()
    P = inp.split()
    x,n = [int(a) for a in P]
    if x<n:
        tmp = 0
        for i in range(x):
            print 1,
            tmp+=1
        for i in range(tmp,n):
            print 0,
        continue
    k = int(math.ceil(float(x-n)/(n-1)))
    k+=1
    full = k*n -(k-1)
    rest = full - x
    if k%2==0:
        if rest>0:
            print k/2,
        else:
            print k/2 + 1,
        rest-=1
        for i in range(1,n-1):
            if rest>0:
                print k-1,
            else:
                print k,
            rest-=1
        if rest>0:
            print k/2 -1,
        else:
            print k/2,
    else:
        taken = [k]*n
        taken[0] = int(math.ceil(float(k)/2))
        taken[n-1] =  int(math.ceil(float(k)/2))
        for i in range(n-1,-1,-1):
            if rest>0:
                taken[i] -=1
            rest-=1
        for i in range(0,n):
            print taken[i],

