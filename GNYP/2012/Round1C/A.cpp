/**
 * @author - iSea_baidu @ 2016-03-30 17:13
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

const int maxn = 1000 + 10;

vector<int> g[maxn];
bool vis[maxn];
int n;

bool dfs(int x) {
    if (vis[x]) {
        return true;
    }
    vis[x] = true;
    for (const int& nxt : g[x]) {
        if (dfs(nxt)) {
            return true;
        }
    }
    return false;
}

int main() {
    repcase {
        scanf("%d", &n);
        rep (i, n) {
            int edge_count;
            scanf("%d", &edge_count);
            g[i].clear();
            rep (j, edge_count) {
                int foo;
                scanf("%d", &foo);
                g[i].push_back(--foo);
            }
        }
        bool has_morethan_one_path = false;
        rep (i, n) {
            memset(vis, 0, sizeof(vis));
            if (dfs(i)) {
                has_morethan_one_path = true;
            }
        }
        printf("Case #%d: %s\n", Case++, has_morethan_one_path? "Yes" : "No");
    }
    return 0;
}