read = lambda: map(int, raw_input().split())

f = open('..\A.out', 'w+')

def my_print(s):
	try:
		f.write(s + '\n')
	except:
		print s

def get_cost(e, o, n):
	num = o - e + 1
	return (n + n - num + 1) * num / 2

for Case in xrange(input()):
	# indicator...
	print 'solving case %d...' % (Case + 1, )

	# input...
	n, m = read()
	e, l = {}, {}

	ori_sum = 0
	for idx in xrange(m):
		oi, ei, pi = read()
		ori_sum += get_cost(oi, ei, n) * pi
		e.setdefault(oi, 0)
		l.setdefault(ei, 0)
		e[oi] += pi
		l[ei] += pi

	best_sum = 0
	for ei in sorted(l.keys()):
		pi = l[ei]
		for oi in sorted(e.keys(), reverse=True):
			if oi <= ei and e[oi] > 0:
				d_pi = min(e[oi], pi)
				best_sum += get_cost(oi, ei, n) * d_pi
				e[oi] -= d_pi
				pi -= d_pi
				if e[oi] == 0: e.pop(oi)
				if pi == 0: break

	# solve...
	my_print('Case #%d: %d' % (Case + 1, (ori_sum - best_sum) % 1000002013))

try:
	f.close()
except:
	pass