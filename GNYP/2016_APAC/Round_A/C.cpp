/**
 * @author - iSea_baidu @ 2016-03-17 16:04
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
#include <map>
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

const int inf = 1000000000;
const int maxn = 100 + 10;

struct edge {
    int u, v, w;
};

int n, m, g[maxn][maxn];
vector<edge> edges;

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d", &n, &m);
        rep (i, n) {
            g[i][i] = 0;
            rep (j, i) {
                g[i][j] = g[j][i] = inf;
            }
        }
        edges.clear();
        rep (i, m) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            edges.push_back({u, v, w});
            to_min(g[u][v], w);
            to_min(g[v][u], w);
        }
        rep (k, n) rep (i, n) rep (j, n) {
            to_min(g[i][j], g[i][k] + g[k][j]);
        }
        printf("Case #%d:\n", Case++);
        rep (i, m) {
            if (g[edges[i].u][edges[i].v] != edges[i].w) {
                printf("%d\n", i);
            }
        }
    }
    return 0;
}