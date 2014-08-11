read = lambda: map(int, raw_input().split())

def check(nums):
	prev = 0
	for num in sorted(nums):
		if num != prev + 1:
			return False
		prev = num
	return True

f = open('A.out', 'w')

def my_print(s):
	try:
		f.write(s + '\n')
	except:
		print s

def solve(mat, n):
	for idx in xrange(n * n):
		if not check(mat[idx]):
			return False
		if not check([mat[i][idx] for i in xrange(n * n)]):
			return False

	for sx in xrange(0, n * n, n):
		for sy in xrange(0, n * n, n):
			nums = []
			for idx in xrange(n):
				nums.extend([mat[sx + idx][sy + idy] for idy in xrange(n)])
			if not check(nums):
				return False

	return True

for Case in xrange(input()):
	n = input()
	mat = [read() for idx in xrange(n * n)]
	my_print('Case #%d: %s' % (Case + 1, 'Yes' if solve(mat, n) else 'No'))

f.close()