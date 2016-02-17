/**
 * @author - iSea_baidu @ 2016-02-17 21:03
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

const int maxn = 100 + 10;

char maze[maxn][maxn];
int R, C, q;
bool vis[maxn][maxn];

void dfs(int x, int y) {
    if (x < 0 || y < 0 || x >= R || y >= C || vis[x][y] || maze[x][y] != '1') {
        return;
    }
    vis[x][y] = true;
    dfs(x + 1, y); dfs(x - 1, y);
    dfs(x, y + 1); dfs(x, y - 1);
}

int query() {
    memset(vis, 0, sizeof(vis));
    int ret = 0;
    rep (i, R) rep (j, C) {
        if (maze[i][j] == '1' && !vis[i][j]) {
            ++ret;
            dfs(i, j);
        }
    }
    return ret;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d", &R, &C);
        rep (i, R) {
            scanf("%s", maze[i]);
        }
        scanf("%d", &q);
        printf("Case #%d:\n", Case++);
        while (q--) {
            char op[2];
            scanf("%s", op);
            if (strcmp(op, "Q") == 0) {
                printf("%d\n", query());
            } else if (strcmp(op, "M") == 0) {
                int x, y, z;
                scanf("%d%d%d", &x, &y, &z);
                maze[x][y] = (char)('0' + z);
            }
        }
    }
    return 0;
}