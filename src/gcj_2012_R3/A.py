read = lambda: map(int, raw_input().split())

f = open('..\A.out', 'w+')

def my_print(s):
	try:
		f.write(s + '\n')
	except:
		print s

def comp(x, y, L, P):
	cx = L[y] * P[x] 
	cy = L[x] * P[y]
	if cx - cy == 0:
		return x < y
	return -1 if cx > cy else 1

for Case in xrange(input()):
	# indicator...
	print 'solving case %d...' % (Case + 1, )

	# input...
	n = input()
	l = read()
	p = read()
	alter = sorted([i for i in xrange(n)], cmp = lambda x, y: comp(x, y, l, p))

	# solve...
	my_print('Case #%d: %s' % (Case + 1, ' '.join([str(alter[i]) for i in xrange(n)])))

try:
	f.close()
except:
	pass