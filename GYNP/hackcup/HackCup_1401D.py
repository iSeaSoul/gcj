import sys
sys.path.append('../')

from utils.GCJTemplate import *

def process_less(num, n, k):
    ret = 0
    has_zero, bigger_idx = False, n

    for i in xrange(n):
        if num[i] == 0:
            has_zero = True
        if num[i] <= k:
            ret += k - num[i]
        else:
            bigger_idx = i
            break

    if has_zero:
        ret -= k

    return n - bigger_idx, num[bigger_idx:], ret

def gen_prime(plen, pbound):
    is_prime = make_array(True, (pbound, ))
    primes = []
    for i in xrange(2, pbound):
        if is_prime[i]:
            primes.append(i)
            if len(primes) >= plen:
                break
            for j in xrange(2 * i, pbound, i):
                is_prime[j] = False
    return primes

def get_prime_mask(primes, num):
    if num <= 1:
        return 0

    ret = 0
    for i in xrange(len(primes)):
        if num % primes[i] == 0:
            num /= primes[i]
            ret |= (1 << i)
            while num % primes[i] == 0:
                num /= primes[i]
            if num == 1:
                break
    return ret

def solve():
    n, k = read_int()
    num = sorted(read_int())
    n, num, ret = process_less(num, n, k)

    if n == 0:
        return ret

    for i in xrange(n):
        fixed_item = ((num[i] + k - 1) // k) * k
        ret += fixed_item - num[i]
        num[i] = fixed_item // k

    plen = 20
    primes = gen_prime(plen, 100)
    num_prime_mask = [get_prime_mask(primes, i) for i in xrange(55)]

    update = lambda x, y: y if x == -1 or y < x else x

    dp = make_array(-1, (n + 1, 1 << plen))
    dp[0][0] = 0
    for i in xrange(n):
        for mask in xrange(1 << plen):
            if dp[i][mask] == -1:
                continue

            pmask = num_prime_mask[num[i]]
            if (pmask & mask) == 0:
                dp[i + 1][mask | pmask] = update(dp[i + 1][mask | pmask], dp[i][mask])
            else:
                for j in xrange(plen):
                    if ((mask >> j) & 1) == 0 and primes[j] > num[i]:
                        dp[i + 1][mask | (1 << j)] = update(dp[i + 1][mask | (1 << j)], dp[i][mask] + primes[j] - num[i])
                        break

    dpret = -1
    for mask in xrange(1 << plen):
        if dp[n][mask] != -1:
            dpret = update(dpret, dp[n][mask])

    return ret + dpret * k

GCJJob('HackCup_1401D', solve).run(True)
