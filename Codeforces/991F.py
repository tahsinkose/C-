num = int(raw_input())

k = len(num)
zeroes = [False]*k
for i in range(k-1,-1,-1):
    if num[i]=='0':
        zeroes[i] = True