import copy
import time

if __name__ == "__main__":
    start = time.time()
    N = int(raw_input())
    string_input = raw_input()
    P = string_input.split() #splits the input string on spaces
    # process string elements in the list and make them integers
    P = [int(a) for a in P]
    Q = int(raw_input())
    for i in xrange(0,Q):
         A = [int(a) for a in raw_input().split()]
         if A[0] == 1: #print comm
             print(sum(P[A[1]-1:A[2]]))
         elif A[0] == 2:
             for j in xrange(A[1]-1,A[2]):
                 P[j] |= (1<<(A[3]-1))
                 
         else:
             for j in xrange(A[1]-1,A[2]):
                 P[j] &= ~(1<<(A[3]-1))
    end = time.time()
    print "time: ",(end - start)
