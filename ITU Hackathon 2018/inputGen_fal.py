from random import randint
from random import shuffle
N = 10
Q = 10
K = 10**9
print Q,N,K
P = range(1,N+1)
shuffle(P)
print(" ".join(str(x) for x in P))
for i in range(Q):
	shuffle(P)
	print(" ".join(str(x) for x in P))
