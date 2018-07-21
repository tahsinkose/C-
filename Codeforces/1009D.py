import math

if __name__=='__main__':
	string_input = input()
	P = string_input.split() #splits the input string on spaces
	n,m = [int(a) for a in P]
	if m < n-1 or m > (n*(n-1))/2:
		print("Impossible")
	else:
		records = []
		for i in range(1,n+1):
			for j in range(i+1,n+1):
				if math.gcd(i,j)==1:
					records.append((i,j))
					if len(records) == m:
						print("Possible")
						for pair in records:
							print(pair[0],pair[1])
						exit(0)
		print("Impossible")
