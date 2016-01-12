import sys
sys.path.append('../../')

from utils import GCJTemplate as gt

SQUARE_CHAR = '#'

def solve():
    n = input()
    g = [raw_input() for i in xrange(n)]

    minx, miny = n, n
    maxx, maxy = -1, -1
    for i in xrange(n):
        for j in xrange(n):
            if g[i][j] == SQUARE_CHAR:
                maxx = max(maxx, i)
                maxy = max(maxy, j)
                minx = min(minx, i)
                miny = min(miny, j)

    if minx == n:
        print 'ERROR:: no black cell detected'
        return 'NO'
    if minx - maxx != miny - maxy:
        return 'NO'

    for i in xrange(minx, maxx + 1):
        for j in xrange(miny, maxy + 1):
            if g[i][j] != SQUARE_CHAR:
                return 'NO'
    return 'YES'

gt.GCJJob('HackCup_1400A', solve).run(True)
