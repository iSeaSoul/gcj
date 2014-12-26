import sys
sys.path.append('../')

from utils.GCJTemplate import *

def solve():
    a, b = read()
    return a + b

GCJJob('A', solve).run(True)
