import copy
from fractions import gcd



def cycles(perm):
  remain = set(perm)
  result = []
  while len(remain) > 0:
    n = remain.pop()
    cycle = [n]
    while True:
      n = perm[n-1]
      if n not in remain:
        break
      remain.remove(n)
      cycle.append(n)
    result.append(len(cycle))
  return result
 
 
if __name__ == "__main__":
    N, Q, K = map(int, raw_input().split())
    string_input = raw_input()
    P = string_input.split() #splits the input string on spaces
    # process string elements in the list and make them integers
    P = [int(a) for a in P]
    disjoint_set_sizes = cycles(P)
    lcm = disjoint_set_sizes[0]
    for i in disjoint_set_sizes[1:]:
        lcm = lcm*i/gcd(lcm, i)

    for i in range(0,Q):
        S = [int(a) for a in raw_input().split()]
        tmp = copy.deepcopy(S)
        
        for j in xrange(0,K%lcm):
            for l in range(len(P)):
                tmp[P[l]-1] = S[l]
            S = copy.deepcopy(tmp)
        
        if S[N-2]<S[N-1]:
            print "NO"
        else:
            print "YES"
