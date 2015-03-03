import sys
sys.path.append('../')

from utils.GCJTemplate import *

C_MAXN = 10**7 + 2
is_prime = make_array(True, (4003, ))
primacity = make_array(-1, (C_MAXN, ))
primes = []

def gen_prime():
    for i in xrange(2, 4000):
        if is_prime[i]:
            primes.append(i)
            for j in xrange(i << 1, 4000, i):
                is_prime[j] = False

def divide(x):
    primacity_cnt = 0
    for p in primes:
        if p * p > x:
            break
        if x % p == 0:
            primacity_cnt += 1
            x /= p
            while x % p == 0:
                x /= p
            if x == 1:
                break
    if x != 1:
        primacity_cnt += 1
    return primacity_cnt

def gen_primacity():
    for i in xrange(2, C_MAXN):
        primacity[i] = divide(i)
        # if i % 1000 == 0:
        #     print i, primacity[i]

def solve():
    A, B, K = read_int()
    ret = 0
    for i in xrange(A, B + 1):
        if primacity[i] == K:
            ret += 1
    return ret

gen_prime()
gen_primacity()

GCJJob('A', solve).run(True)
