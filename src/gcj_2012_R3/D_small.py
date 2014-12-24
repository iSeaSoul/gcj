read = lambda: map(int, raw_input().split())

f = open('..\D.out', 'w+')

def my_print(s):
	try:
		f.write(s + '\n')
	except:
		print s

mis_map = {"o": "0", "i": "1", "e": "3", "a": "4", "s": "5", "t": "7", "b": "8", "g": "9"}

def get_idx(x):
	global mp, mpcnt
	if not mp.has_key(x):
		mp[x] = mpcnt
		mpcnt += 1
	return mp[x]

def add_edge_imp(a, b, g):
	g[a][b] = True

def add_edge(a, b, g):
	global mis_map
	add_edge_imp(get_idx(a), get_idx(b), g)
	if mis_map.has_key(b):
		add_edge_imp(get_idx(a), get_idx(mis_map[b]), g)
	if mis_map.has_key(a):
		add_edge_imp(get_idx(mis_map[a]), get_idx(b), g)
		if mis_map.has_key(b):
			add_edge_imp(get_idx(mis_map[a]), get_idx(mis_map[b]), g)

for Case in xrange(input()):
	# indicator...
	print 'solving case %d...' % (Case + 1, )

	# input...
	n = int(raw_input())
	s = raw_input().strip()

	mp = {}
	mpcnt = 0
	g = [[False for xid in xrange(34)] for xid in xrange(34)]

	for idx in xrange(len(s) - 1):
		add_edge(s[idx], s[idx + 1], g)

	ans = 0
	ind, outd = [0 for idx in xrange(mpcnt)], [0 for idx in xrange(mpcnt)]
	for idx in xrange(mpcnt):
		for jdx in xrange(mpcnt):
			if not g[idx][jdx]: continue
			ind[jdx] += 1
			outd[idx] += 1
			ans += 1

	while True:
		lowest, biggest = mpcnt, -mpcnt
		dif_num = 0
		for i in xrange(mpcnt):
			if ind[i] != outd[i]:
				dif_num += 1
			if ind[i] - outd[i] < lowest:
				lowest = ind[i] - outd[i]
				lowest_id = i
			if ind[i] - outd[i] > biggest:
				biggest = ind[i] - outd[i]
				biggest_id = i
		if dif_num <= 2 and lowest >= -1 and biggest <= 1:
			break
		ans += 1
		ind[lowest_id] += 1
		outd[biggest_id] += 1

	# solve...
	my_print('Case #%d: %d' % (Case + 1, ans + 1))

try:
	f.close()
except:
	pass