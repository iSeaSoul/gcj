### **Qualification Round**

**Cooking the Books 15pts**

Simple Enumeration. O(length) is available.

**New Year's Resolution 30pts**

BitMask Enumeration or DFS.

**Laser Maze 55pts**

BFS using (time % 4, position) as state. Record the minimum step to achieve the state.

To accelerate, BFS to mark all valid grids that the laser cannot reach first.

### **Round 1**

**Homework 10pts**

Generate all primacity by brute force: divide it into primes and count.

**Autocomplete 25pts**

Build a Trie by the given word order. For each word query, traverse on the tree till reach a node whose word count equals 1, and this's the minimum length for auto-complete this word.

**Winning at Sports 25pts**

As scores <= 2000. Straightforward `DP[score_1][score_2]` is acceptable. 

For the first type, `score_1` always > `score_2`. 

For the second type, `score_1` always <= `score_2` until `score_1 = score_2 = final_score_2`.

**Corporate Gifting 40pts**

Given a tree, assign a value for each node that value of any two adjacent nodes are not same. Maximize the sum of all value.

Two kinds of value is enough. Why we need more?

Consider the kind of tree:

![](http://m2.img.srcdd.com/farm5/d/2015/0228/18/863D620DCD61FEC45C9CDB2A57845443_B500_900_500_243.png)

If only two kinds of values are used, both the size of second layer and third layer is huge. But if assign node-1 with 3, node-2 with 2, others all with 1. The result is obviously better.

Now the new question comes, what's the bound of the value kind?

The answer is O(logN). Hence simple `DP[node_id][value]` is good enough.

Simple proof of the bound:

1.  Root always has the maximal priced color, say K. (Otherwises switch them!)

2.  So if root has one child, the sub-problem can be reduced to K-1;
    If root has two children, that means K-2, ..., and so on.
    That is, Num(K) >= Sigma(Num(i)) (0 <= i < k) >= 2^K.

    (Here Num(K) means the total number of different kinds of tree structure with optimal answer no larger than K)

### **Round 2**

**Lazy Sort 10pts**

Enumerate whether the first chosen number is the top or the bottom. The the rest order is fixed. Simulate the process to check if it can be finished.

**All Critical 20pts**

Given the probability of collecting one star, and each time the (virtual) bag contains each star slot independently. Calculating the expectation of collecting all stars in each slot.

Use `probability[round, got_star]` to do dp until the `probability * round` are small enough. In each round, if new S stars are obtained from the unobtained K stars, the probability is `C[K][S] * P^S * (1-P)^(K-S)`.

**Autocomplete Strikes Back 25pts**

Also build a Trie first.

Choose K words so that the typing times is minimal. As K <= 100, use `min_time[trie_node_id, chosen_word_number]` to dp is feasible. Combine subtrees like knapsack problems. For words end at this node, also combine them together.

If without autocomplete, this DP will result in the sum of the all choose words' length. But it's not much difficult to handle with that, just always mark `dp[tree_node_id][1] = 1`.

**Fox Socks 45pts (UNDONE)**

Typical Segment Tree problems. Adding an arithmetic sequence can be handled by segment tree. The extra trick maybe the parity count query.

### **Round 3**

**Boomerang 10pts**

Enumerate the directory of the first run, sum up all touched points. Then sort the angle of every vector which starts at this position and ends at the given point, i.e. using [atan2](http://www.cplusplus.com/reference/cmath/atan2/). Deal with the same points specially. 

**Lunch Scheduling 15pts**

Sort all the intervals with their start time ascending. Keep state `min_second_number[interval_idx, min_first_number]` to run DP. But Naive DP is O(N^3), some optimization is needed.

For an interval, the next chosen interval should be fixed: the interval begins before the lunchtime can be inserted and ends at the latest. So the DP transferring is O(1), which leads a total O(N^2).

**Gentrification 35pts**

Given a directed map, find the maximum size of subsets in which every two nodes are  either strongly connected or disconnected.

Get SCC to shrink the map to a DAG first. Then a minimum cut can be used to find the maximum independent set in vertex-weighted DAG. The way to construct the map is like the way to build a bipartite map, N - maxflow is the final answer.

**Fox Rocks 45pts(UNDONE)**

Markov Chain?

### **Code Link**

<https://github.com/iSeaSoul/gcj/tree/master/GNYP/hackcup/2015>