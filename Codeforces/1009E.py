

if __name__=='__main__':
	n = int(input())
	string_input = input()
	P = string_input.split() #splits the input string on spaces
	diffs = [int(a) for a in P]
	print(diffs)