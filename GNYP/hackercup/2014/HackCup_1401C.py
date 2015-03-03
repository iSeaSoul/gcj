import sys
sys.path.append('../')

from utils.GCJTemplate import *

def can_reach(x, y, gmap, n, m):
    return x >= 0 and x < n and y >= 0 and y < m and gmap[x][y] == '.'

def solve():
    n, m = read_int()
    gmap = []
    for row in xrange(n):
        rowstr = raw_input()
        gmap.append(rowstr)

    dpup = make_array(-1, (n, m, 2))
    dpdn = make_array(-1, (n, m, 2))

    dpdn[0][0][0] = 1
    for i in xrange(n):
        for j in xrange(m):
            for k in xrange(2):
                if dpdn[i][j][k] != -1:
                    if can_reach(i, j + 1, gmap, n, m):
                        dpdn[i][j + 1][0] = max(dpdn[i][j][k] + 1, dpdn[i][j + 1][0])
                    if can_reach(i + 1, j, gmap, n, m):
                        dpdn[i + 1][j][1] = max(dpdn[i][j][k] + 1, dpdn[i + 1][j][1])

    dpup[n - 1][m - 1][0] = 0
    for i in xrange(n - 1, -1, -1):
        for j in xrange(m - 1, -1, -1):
            for k in xrange(2):
                if dpup[i][j][k] != -1:
                    if can_reach(i, j - 1, gmap, n, m):
                        dpup[i][j - 1][0] = max(dpup[i][j][k] + 1, dpup[i][j - 1][0])
                    if can_reach(i - 1, j, gmap, n, m):
                        dpup[i - 1][j][1] = max(dpup[i][j][k] + 1, dpup[i - 1][j][1])

    ret = max(dpdn[n - 1][m - 1][0],dpdn[n - 1][m - 1][1])

    for i in xrange(n):
        for j in xrange(m):
            for k in xrange(2):
                if dpdn[i][j][0] != -1:
                    step = 0
                    while can_reach(i - step, j, gmap, n, m):
                        if dpup[i - step][j][0] != -1:
                            ret = max(ret, dpdn[i][j][0] + dpup[i - step][j][0] + step)
                        step += 1
                if dpdn[i][j][1] != -1:
                    step = 0
                    while can_reach(i, j - step, gmap, n, m):
                        if dpup[i][j - step][1] != -1:
                            ret = max(ret, dpdn[i][j][1] + dpup[i][j - step][1] + step)
                        step += 1

    return ret

GCJJob('HackCup_1401C', solve).run(True)
