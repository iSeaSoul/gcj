/*
 * Not the fish.
 * liyan30 @ 2015-02-15 15:49
 */

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

#define sz(x) ((int)((x).size()))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (cin >> t; t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

#define LOG(level, fmt, arg...) \
    printf("[" #level "] [%s:%d] " fmt"\n",\
    __FILE__, __LINE__, ##arg); \

#define LOG_WARNING(fmt, arg...) LOG(WARNING, fmt, ##arg)
#define LOG_NOTICE(fmt, arg...) LOG(NOTICE, fmt, ##arg)
#define LOG_FATAL(fmt, arg...) LOG(FATAL, fmt, ##arg)

const int MAXN = 20000 + 10;
const int MAXK = 100 + 10;

struct Trie {
    struct node {
        int cnt;
        int end_cnt;
        int next[26];

        node() {
            cnt = end_cnt = 0;
            memset (next, -1, sizeof(next));
        }
    };

    vector<node> nodes;

    void clear() {
        nodes.clear();
        nodes.push_back(node());
    }
    void insert(char *word) {
        int idx = 0;
        nodes[idx].cnt += 1;
        for (int i = 0; word[i]; ++i) {
            int ch = word[i] - 'a';
            if (nodes[idx].next[ch] == -1) {
                nodes[idx].next[ch] = sz(nodes);
                nodes.push_back(node());
            }
            idx = nodes[idx].next[ch];
            nodes[idx].cnt += 1;
        }
        nodes[idx].end_cnt += 1;
    }
};

char buf[MAXN];
Trie tree;
int n, k;

int dp[MAXN][MAXK], dpsz[MAXN];

void update(int& x, int y) {
    if (x == -1 || x > y) {
        x = y;
    }
}

void run_dp(int tree_id) {
    if (tree.nodes[tree_id].cnt == 1) {
        dp[tree_id][0] = 0; dp[tree_id][1] = 1;
        dpsz[tree_id] = 1;
        return;
    }

    int bound_count = min(k, tree.nodes[tree_id].cnt);
    memset(dp[tree_id], -1, sizeof(int) * (bound_count + 1));
    dp[tree_id][0] = 0;
    int max_count = 0;

    rep (i, 26) {
        if (tree.nodes[tree_id].next[i] != -1) {
            int subtree_id = tree.nodes[tree_id].next[i];
            run_dp(subtree_id);
            // combine subtrees
            repd (p_word, max_count, 0) {
                if (dp[tree_id][p_word] == -1) continue;
                for (int s_word = 1; s_word <= dpsz[subtree_id] && s_word + p_word <= bound_count; ++s_word) {
                    if (dp[subtree_id][s_word] != -1) {
                        update(dp[tree_id][s_word + p_word], dp[tree_id][p_word] + dp[subtree_id][s_word] + s_word);
                        to_max(max_count, s_word + p_word);
                    }
                }
            }
        }
    }
    repd (p_word, max_count, 0) {
        if (dp[tree_id][p_word] == -1) continue;
        repf (e_word, 1, tree.nodes[tree_id].end_cnt) {
            update(dp[tree_id][e_word + p_word], dp[tree_id][p_word] + e_word);
            to_max(max_count, e_word + p_word);
        }
    }
    if (max_count >= 1) {
        dp[tree_id][1] = 1;
    }
    dpsz[tree_id] = max_count;
}

int main() {
    repcase {
        scanf ("%d%d", &n, &k);
        tree.clear();
        rep (i, n) {
            scanf ("%s", buf);
            tree.insert(buf);
        }
        if (k == 1) {
            printf ("Case #%d: 1\n", Case++);
            continue;
        }
        run_dp(0);
        printf ("Case #%d: %d\n", Case++, dp[0][k] - k);
    }
    return 0;
}
