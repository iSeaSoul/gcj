import sys
sys.path.append('../')

from utils.GCJTemplate import *

def solve():
    N, M, G = read_int()
    num = (G + N - 1) // N
    num_empty = max(0, N - M // num)

    return G + num_empty

GCJJob('HackCup_1401B', solve).run(True)
