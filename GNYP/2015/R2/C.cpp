/**
 * @author - iSea_baidu @ 2016-01-12 16:37
 * @brief - From sky to the sea.
 **/

#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>
#include <queue>
#include <unordered_map>
#include <set>
using namespace std;

// SELF TEMPLATE CODE BGEIN

#define LOG(level, fmt, arg...) \
    fprintf(stderr, "[" #level "] [Line:%d] " fmt"\n", __LINE__, ##arg);
#define NOTICE(fmt, arg...) LOG(NOTICE, fmt, ##arg)
#define FATAL(fmt, arg...) LOG(FATAL, fmt, ##arg)
#define DEBUG(x) do { \
    stringstream ss; \
    ss << #x << ": " << x; \
    NOTICE("%s", ss.str().c_str()) \
} while(0)

#define SZ(x) ((int)((x).size()))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repcase int t, Case = 1; for (scanf("%d", &t); t; --t)
template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

struct graph {
    static const int maxn = 2000 * 2 + 200;
    static const int inf = (-1u) >> 1;

    struct Adj {
        int v, c, b;
        Adj() {}
        Adj(int _v, int _c, int _b):
            v(_v), c(_c), b(_b) {}
    };
    int n, S, T, h[maxn], cnt[maxn];
    vector<Adj> adj[maxn];
    void clear() {
        for (int i = 0; i < n; ++i)
            adj[i].clear();
        n = 0;
    }
    void insert(int u, int v, int c, int d = 0) {
        // NOTICE("insert %d -> %d flow %d", u, v, c);
        n = max(n, max(u, v) + 1);
        adj[u].push_back(Adj(v, c, adj[v].size()));
        adj[v].push_back(Adj(u, c * d, adj[u].size() - 1));
    }
    int maxflow(int _S, int _T) {
        S = _S, T = _T;
        fill(h, h + n, 0);
        fill(cnt, cnt + n, 0);
        int flow = 0;
        while (h[S] < n) {
            flow += dfs(S, inf);
        }
        return flow;
    }
    int dfs(int u, int flow) {
        if (u == T) {
            return flow;
        }
        int minh = n - 1, ct = 0;
        for (vector<Adj>::iterator it = adj[u].begin(); flow && it != adj[u].end(); ++it) {
            if (it->c) {
                if (h[it->v] + 1 == h[u]) {
                    int k = dfs(it->v, min(it->c, flow));
                    if (k) {
                        it->c -= k;
                        adj[it->v][it->b].c += k;
                        flow -= k;
                        ct += k;
                    }
                    if (h[S] >= n) {
                        return ct;
                    }
                }
                minh = min(minh, h[it->v]);
            }
        }
        if (ct) {
            return ct;
        }
        if (--cnt[h[u]] == 0) {
            h[S] = n;
        }
        h[u] = minh + 1;
        ++cnt[h[u]];
        return 0;
    }
};

graph maxflow_g;

int get_vid(int x, int f) {
    return (x << 1) | f;
}

int get_id(int& idx, string word, unordered_map<string, int>& word_id, 
            bool& is_new) {
    if (word_id.find(word) == word_id.end()) {
        is_new = true;
        word_id[word] = idx++;
        return idx - 1;
    }
    is_new = false;
    return word_id[word];
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        unordered_map<string, int> word_id;
        bool is_new;
        int n, idx = 0;
        scanf("%d", &n);
        maxflow_g.clear();
        rep (i, n) {
            char buf[12], nxt;
            while (scanf("%s%c", buf, &nxt) != EOF) {
                int cid = get_id(idx, string(buf), word_id, is_new);
                if (is_new) {
                    maxflow_g.insert(n + get_vid(cid, 0), n + get_vid(cid, 1), 1);
                }
                maxflow_g.insert(i, n + get_vid(cid, 0), graph::inf);
                maxflow_g.insert(n + get_vid(cid, 1), i, graph::inf);
                if (nxt == '\n') break;
            }
        }
        printf("Case #%d: %d\n", Case++, maxflow_g.maxflow(0, 1));
    }
    return 0;
}