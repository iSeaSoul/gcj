import sys
sys.path.append('../')

from utils.GCJTemplate import *

MOD = 10**9 + 7
MAXN = 2015
P = make_array(1, (MAXN, MAXN))
P2 = make_array(1, (MAXN, MAXN))

def solve():
    A, B = map(int, raw_input().strip().split('-'))
    return "%d %d" % (P2[A][B], P[B][B])

def cal_P():
    for i in xrange(2, MAXN):
        for j in xrange(1, i + 1):
            if i == j:
                P[i][j] = P[i][j - 1]
            else:
                P[i][j] = (P[i - 1][j] + P[i][j - 1]) % MOD

    for i in xrange(2, MAXN):
        for j in xrange(1, i):
            if i == j + 1:
                P2[i][j] = P2[i][j - 1]
            else:
                P2[i][j] = (P2[i - 1][j] + P2[i][j - 1]) % MOD

cal_P()
GCJJob('C', solve).run(True)
