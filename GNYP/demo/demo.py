import sys
sys.path.append('../')

from utils import GCJTemplate as gt

def solve():
    a, b = gt.read_int()
    return a + b

gt.GCJJob('demo', solve).run(True)
