/**
 * @author - iSea_baidu @ 2016-01-15 18:45
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

void read_array(int* a, int len) {
    scanf("%d", &a[0]);
    int A, C, M;
    scanf("%d%d%d", &A, &C, &M);
    repf (i, 1, len - 1) {
        a[i] = ((long long)a[i - 1] * A + C) % M;
    }
}

const int maxn = 1000000 + 10;
const int offset = maxn;

int n, d, p[maxn], s[maxn];
vector<int> g[maxn];
int range[maxn << 1];

void dfs(int x, int lf, int rt) {
    if (lf > rt) return;
    range[lf + offset] += 1;
    range[rt + offset + 1] -= 1;

    for (const auto& nxt : g[x]) {
        dfs(nxt, max(lf, s[nxt] - d), min(rt, s[nxt]));
    }
}

struct node {
    int x, lf, rt;
};

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d", &n, &d);
        read_array(s, n);
        read_array(p, n);
        rep (i, n) {
            g[i].clear();
        }
        repf (i, 1, n - 1) {
            p[i] %= i;
            g[p[i]].push_back(i);
        }

        memset(range, 0, sizeof(range));
        // dfs(0, s[0] - d, s[0]);
        queue<node> q;
        q.push({0, s[0] - d, s[0]});
        while (!q.empty()) {
            node cur = q.front(); q.pop();
            if (cur.lf > cur.rt) continue;
            range[cur.lf + offset] += 1;
            range[cur.rt + offset + 1] -= 1;

            for (const auto& nxt : g[cur.x]) {
                q.push({nxt, max(cur.lf, s[nxt] - d), min(cur.rt, s[nxt])});
            }
        }

        int ret = 0;
        repf (p, 1, offset * 2 - 1) {
            range[p] += range[p - 1];
            to_max(ret, range[p]);
        }
        printf("Case #%d: %d\n", Case++, ret);
    }
    return 0;
}