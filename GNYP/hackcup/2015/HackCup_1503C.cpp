/**
 * @author - liyan30 @ 2015-02-28 16:48
 * @brief - From sky to the sea.
 **/

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

#define LOG(level, fmt, arg...) \
    printf("[" #level "] [Line:%d] " fmt"\n", __LINE__, ##arg);

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
#define repcase int t, Case = 1; for (cin >> t; t; --t)

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

const int MAXN = 500 + 10;

struct graph {
    static const int maxn = MAXN * 2;
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

int n, m;
vector<int> g[MAXN];

int dfn[MAXN], low[MAXN], st[MAXN], mark[MAXN];
int tms, top, sccnt;
bool inst[MAXN];

int sc_size[MAXN];
bool DAG_mat[MAXN][MAXN];

void dfs(int x) {
    dfn[x] = low[x] = ++tms;
    inst[x] = true;
    st[++top] = x;
    for (vector<int>::iterator it = g[x].begin(); it != g[x].end();++it) {
        if (!dfn[*it]) {
            dfs(*it);
            low[x] = min(low[x], low[*it]);
        } else if (inst[*it]) {
            low[x] = min(low[x], dfn[*it]);
        }
    }
    if (low[x] == dfn[x]) {
        int count = 0;
        do {
            count += 1;
            mark[st[top]] = sccnt;
            inst[st[top]] = false;
        } while (st[top--] != x);
        // ++sccnt;
        sc_size[sccnt++] = count;
    }
}

void shrink_to_DAG() {
    top = tms = sccnt = 0;
    memset (inst, 0, sizeof(inst));
    memset (dfn, 0, sizeof(dfn));

    rep (i, n) {
        if (!dfn[i]) {
            dfs(i);
        }
    }

    memset (DAG_mat, 0, sizeof(DAG_mat));
    rep (i, n) {
        // NOTICE("%d->%d", i, mark[i]);
        for (const int& next : g[i]) {
            if (mark[i] != mark[next]) {
                DAG_mat[mark[i]][mark[next]] = true;
            }
        }
    }
}

int solve() {
    shrink_to_DAG();

    rep (k, sccnt) rep (i, sccnt) rep (j, sccnt) {
        DAG_mat[i][j] |= (DAG_mat[i][k] & DAG_mat[k][j]);
    }

    maxflow_g.clear();
    int S = 0, T = 2 * n + 1;

    rep (i, sccnt) rep (j, sccnt) {
        if (DAG_mat[i][j]) {
            maxflow_g.insert(i + 1, j + sccnt + 1, graph::inf);
        }
    }
    rep (i, sccnt) {
        maxflow_g.insert(S, i + 1, sc_size[i]);
        maxflow_g.insert(i + sccnt + 1, T, sc_size[i]);
    }

    return n - maxflow_g.maxflow(S, T);
}

int main() {
    repcase {
        scanf ("%d%d", &n, &m);
        rep (i, n) {
            g[i].clear();
        }
        rep (i, m) {
            int foo, bar;
            scanf ("%d%d", &foo, &bar);
            g[foo].push_back(bar);
        }
        printf ("Case #%d: %d\n", Case++, solve());
    }
    return 0;
}
