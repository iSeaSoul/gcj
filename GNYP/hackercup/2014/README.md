## Facebook HackerCup 2014 Solution

### **Round 1**

**Labelmaker 10pts**

Get the length of the target string, then do a K-inary switching.

**Coins Game 20pts**

A tricky greedy problems: Distribute K coins in N boxes, then the order of boxes may be shuffled, for one guess, point a box and check the box, gain one coin if it contains at least one, what's the minimum guess time to find C coins?

First, calculate the minimum X each box should contains so that `N * X >= C`, which is, the minimum number so that each move will ensure a coin found. Then for X, calculate the maximum number M of non-empty boxes coins can fill. Keep the other boxes empty, which will waste us at most one time, at the other boxes will ensure at least X coins found.

The final code is fairly simple:

```py
def solve():
    N, K, C = read_int()
    min_num = (C + N - 1) // N
    num_empty = max(0, N - K // min_num)
    return G + num_empty
```

P.S. The maximum guess time should be G + N - 1.

**AAAAAA 25pts**

Given a maze, find the longest path from the upper-left corner to the lower-right corner. Only one upwards or leftwards is allowed.

Calculate two DP values, enumerate the row line or column line to make a single connection. That's an `O(N^3)` solution.

Use the state `max_step[pos_x, pos_y, dir, turn_used]` can we make a `O(N^2)` dp solution.

**Preventing Alzheimer's 40pts**

Given N numbers, add each of them a delta-value so that GCD of any two of them is K. Minimize the sum of the delta-values.

As the value less than 50 and number N <= 20. At most N prime factors are needed. So a bitmask DP is feasible. Increase the number less than K to K first, if has one or more zero, keep a single zero. Then for the left number, increase them be the multiple of K, use the divisor for the bitmask DP with state `min_delta_value_sum[idx, mask]`.