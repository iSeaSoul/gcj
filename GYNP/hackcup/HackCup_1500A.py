import sys
sys.path.append('../')

from utils.GCJTemplate import *

def solve():
    rstr = raw_input()
    minv, maxv = int(rstr), int(rstr)

    for i in xrange(len(rstr)):
        for j in xrange(i):
            nstr = rstr[0:j] + rstr[i] + rstr[j+1:i] + rstr[j] + rstr[i+1:]
            if nstr[0] != '0':
                minv = min(minv, int(nstr))
                maxv = max(maxv, int(nstr))

    return "%d %d" % (minv, maxv)

GCJJob('A', solve).run(True)
