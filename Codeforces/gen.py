N = 100
import random
arr = [0] * N
print N
for i in range(N):
	arr[i] = random.randint(2,5)
	print arr[i],