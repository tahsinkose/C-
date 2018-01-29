from random import randint
from random import shuffle
N = 10
print N
P = range(1,N+1)
for i in range(0,N):
    num = randint(0,1048576)
    P[i] = num

print(" ".join(str(x) for x in P))
Q = 10
print Q
for i in range(0,Q):
    comm = randint(1,3)
    if comm == 1:
        l = randint(1,N)
        r = randint(l,N)
        print comm,l,r
    else:
        l = randint(1,N)
        r = randint(l,N)
        x = randint(1,7)
        print comm,l,r,x
        
	
