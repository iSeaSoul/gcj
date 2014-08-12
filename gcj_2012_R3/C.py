read = lambda: map(int, raw_input().split())

fs = open('..\C.out', 'w+')

def my_print(s):
	try:
		fs.write(s + '\n')
	except Exception as e:
		print e
		print s

def get_maxt_with_tm(TM, minp, M, F):
	M -= TM * F
	prev_t, ret = -1, 0
	for vt in sorted(minp.keys()):
		len_t = vt - prev_t
		pi = minp[vt]
		# day with pi <= pi * TM
		if pi * TM * len_t < M:
			M -= pi * TM * len_t
			ret += TM * len_t
		else:
			ret += (M // pi)
			break
		prev_t = vt
	return ret

for Case in xrange(input()):
	# indicator...
	print 'solving case %d...' % (Case + 1, )

	# input...
	m, f, n = read()
	minp = {}
	for idx in xrange(n):
		pi, ti = read()
		minp.setdefault(ti, 10**19)
		minp[ti] = min(minp[ti], pi)

	# purify
	max_t = max(minp.keys())
	maxp = minp[max_t]
	for vt in sorted(minp.keys(), reverse=True)[1:]:
		if minp[vt] >= maxp:
			minp.pop(vt)
		else:
			maxp = minp[vt]

	get_rcost_with_given_tm = lambda tm: get_maxt_with_tm(tm, minp, m, f)

	# ternary search
	l, r, ret = 0, m / f + 1, 0
	while l <= r:
		mid1, mid2 = (l * 2 + r) / 3, (l + r * 2) / 3
		cost1, cost2 = get_rcost_with_given_tm(mid1), get_rcost_with_given_tm(mid2)
		ret = max(max(cost1, cost2), ret)
		if cost1 > cost2:
			r = mid2 - 1
		else:
			l = mid1 + 1

	# solve...
	my_print('Case #%d: %d' % (Case + 1, ret))

try:
	fs.close()
except:
	pass