read = lambda: map(int, raw_input().split())

MAXX = 37

def can_sup(B, X, bpt, G):
	return B >= sum([G - X[xid] for xid in xrange(bpt)]) + \
		sum([max(0, G + 1 - X[xid]) for xid in xrange(bpt, MAXX)])

def get_profit(B, X, bpt, G):
	minc, big = sum([G - X[xid] for xid in xrange(bpt)]), \
		sum([max(0, G + 1 - X[xid]) for xid in xrange(bpt, MAXX)])
	if minc + big <= B:
		return minc * 36.0 / bpt - minc - big
	return -1

def solve(B, X):
	ans = 0
	for bpt in xrange(1, MAXX):
		# slot < bpt: all with min
		sum_less = sum(X[:bpt])
		# less than X[bpt]
		maxt = min((B + sum_less) // bpt, X[bpt] - 1)
		ans = max(ans, (bpt * maxt - sum_less) * (36.0 - bpt) / bpt)
		# no less than X[bpt]
		if can_sup(B, X, bpt, X[bpt]):
			l, r = X[bpt], 10**12
			while l <= r:
				mid = (l + r) >> 1
				if can_sup(B, X, bpt, mid):
					l = mid + 1
				else:
					r = mid - 1
			ans = max(ans, get_profit(B, X, bpt, l - 1))
	return ans

f = open('..\A.out', 'w+')

def my_print(s):
	try:
		f.write(s + '\n')
	except:
		print s

for Case in xrange(input()):
	b, n = read()
	x = read()
	for xid in xrange(len(x), MAXX):
		x.append(0)

	my_print('Case #%d: %.10lf' % (Case + 1, solve(b, sorted(x))))

f.close()
