read = lambda: map(int, raw_input().split())

f = open('..\B.out', 'w+')

def my_print(s):
	try:
		f.write(s + '\n')
	except:
		print s

def can_min_g(C, n, m):
	more = C
	worst_rank = 1
	rank_base = 2 ** (n - 1)
	while more != 0:
		more = (more - 1) >> 1
		worst_rank += rank_base
		rank_base >>= 1
	return worst_rank <= m

def can_max_g(C, n, m):
	less = (2 ** n) - 1 - C
	best_rank = (2 ** n)
	while less != 0:
		less = (less - 1) >> 1
		best_rank >>= 1
	return best_rank <= m

def bsearch(n, m, verify_func):
	l, r = 0, (2 ** n) - 1
	while l <= r:
		mid = (l + r) >> 1
		if verify_func(mid, n, m):
			l = mid + 1
		else:
			r = mid - 1
	return l - 1

for Case in xrange(input()):
	# indicator...
	print 'solving case %d...' % (Case + 1, )

	# input...
	n, m = read()

	# solve...
	my_print('Case #%d: %d %d' % (Case + 1, bsearch(n, m, can_min_g), bsearch(n, m, can_max_g)))

try:
	f.close()
except:
	pass