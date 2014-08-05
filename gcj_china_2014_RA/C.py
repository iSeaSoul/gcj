read = lambda: map(int, raw_input().split())

f = open('C.out', 'w')

for Case in xrange(input()):
	n = input()
	a = read()

	even, odd = [], []
	append_num = lambda arr, num: arr.append(num)
	for i in xrange(n):
		append_num(even if (a[i] & 1) == 0 else odd, a[i])
	even, odd = sorted(even, reverse = True), sorted(odd)
	pop_num = lambda arr: arr.pop(0)
	for i in xrange(n):
		a[i] = pop_num(even if (a[i] & 1) == 0 else odd)

	f.write('Case #%d: %s\n' % (Case + 1, ' '.join(str(a[i]) for i in xrange(n))))

f.close()