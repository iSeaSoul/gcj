import sys
sys.path.append('../')

from utils.GCJTemplate import *

def solve():
    A, B, C = read_int()
    N = input()
    foods = [read_int() for i in xrange(N)]

    for state in xrange(1 << N):
        Asum, Bsum, Csum = 0, 0, 0
        for i in xrange(N):
            if ((state >> i) & 1) == 1:
                Asum, Bsum, Csum = Asum + foods[i][0], Bsum + foods[i][1], Csum + foods[i][2]
        if Asum == A and Bsum == B and Csum == C:
            return 'yes'

    return 'no'

GCJJob('B', solve).run(True)
