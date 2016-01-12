import sys
sys.path.append('../../')

from utils import GCJTemplate as gt

def to_pint(x):
    return int(x * 1000)

def to_p(x):
    return x / 1000.0

def solve():
    n_matches, p_s, p_r, p_i, p_u, p_up, p_d, p_dp = gt.read_double()
    n_matches = int(n_matches)
    p_s, p_r, p_i, p_u, p_up, p_d, p_dp = \
            to_pint(p_s), to_pint(p_r), to_pint(p_i), to_pint(p_u), \
            to_pint(p_up), to_pint(p_d), to_pint(p_dp)
    dp = gt.make_array(0, (2, n_matches, 1001))

    dp[0][1][p_i] += to_p(p_s) * to_p(p_i)
    dp[0][0][p_i] += to_p(1000 - p_s) * to_p(p_i)
    dp[0][1][1000 - p_i] = to_p(p_r) * to_p(1000 - p_i)
    dp[0][0][1000 - p_i] += to_p(1000 - p_r) * to_p(1000 - p_i)

gt.GCJJob('HackCup_1400C', solve).run(True)
