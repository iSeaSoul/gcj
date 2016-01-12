# liyan30 @ 2015-05-10 16:06

import sys
sys.path.append('../')

from utils import GCJTemplate as gt

def cal_all(length):
    half_len = length / 2
    o_half_len = length - half_len
    return 10 ** o_half_len + 10 ** half_len - 1

def get_revnum(num, l, r):
    return int(str(num)[l:r][::-1])

def get_num(num, l, r):
    return int(str(num)[l:r])

def min_step(n):
    if n <= 10:
        return n
    len_n = len(str(n))
    ret = sum([cal_all(i) for i in xrange(1, len_n)])
    ans = n - 10 ** (len_n - 1)
    half_len = len_n / 2
    l = get_revnum(n, 0, half_len)
    r = get_num(n, half_len, len_n + 1)
    if r == 0:
        return min_step(n - 1) + 1
    return ret + min(l + r, ans)

def solve():
    return min_step(gt.read_int()[0])

gt.GCJJob('A', solve).run(True)
