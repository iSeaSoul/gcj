import sys
sys.path.append('../')

from utils.GCJTemplate import *

def solve():
    l, n = raw_input().split()
    n = int(n)

    l = sorted(l)
    base = len(l)

    base_pow = [base ** i for i in xrange(55)]
    ans_len = 0
    while base_pow[ans_len] <= n:
        n -= base_pow[ans_len]
        ans_len += 1

    ans_str = ''
    for pos in xrange(ans_len - 1, -1, -1):
        ans_str += l[n / base_pow[pos]]
        n %= base_pow[pos]

    return ans_str

GCJJob('HackCup_1401A', solve).run(True)
