/**
 * @author - iSea_baidu @ 2016-02-25 17:06
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

const int maxn = 500 + 10;

int n, m, q, dp[maxn];
vector<pair<int, vector<int> > > g[maxn];

struct node {
    int x, d;

    bool operator<(const node& n) const {
        return d > n.d;
    }
};

int calc_shortest_tm(int target_idx, int start_tm) {
    memset(dp, -1, sizeof(dp));
    dp[0] = start_tm;
    priority_queue<node> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        node cur = pq.top(); pq.pop();
        if (dp[cur.x] == -2) {
            continue;
        }
        if (cur.x == target_idx) {
            return cur.d; 
        }
        for (const auto& next : g[cur.x]) {
            int nextx = next.first;
            int nextd = cur.d + next.second[(cur.d + start_tm) % 24];
            if (dp[nextx] == -1 || dp[nextx] > nextd) {
                pq.push({nextx, nextd});
                dp[nextx] = nextd;
            }
        }
        dp[cur.x] = -2;
    }
    return -1;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d%d", &n, &m, &q);
        rep (i, n) {
            g[i].clear();
        }
        rep (i, m) {
            int v, u;
            scanf("%d%d", &v, &u);
            --v, --u;
            vector<int> length(24);
            rep (k, 24) {
                scanf("%d", &length[k]);
            }
            g[v].push_back({u, length});
            g[u].push_back({v, length});
        }
        printf("Case #%d:", Case++);
        rep (i, q) {
            int target, start_tm;
            scanf("%d%d", &target, &start_tm);
            printf(" %d", calc_shortest_tm(--target, start_tm));
        }
        puts("");
    }
    return 0;
}