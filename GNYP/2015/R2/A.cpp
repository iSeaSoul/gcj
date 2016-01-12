/**
 * @author - iSea_baidu @ 2016-01-08 14:38
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

int r, c;
char maze[maxn][maxn];
int invalid_state[maxn][maxn];

int get_cur_dir(char ch) {
    switch (ch) {
        case '^' : return 0;
        case 'v' : return 1;
        case '<' : return 2;
        case '>' : return 3;
    }
    // invalid
    return -1;
}

int solve() {
    memset(invalid_state, 0, sizeof(invalid_state));
    rep (i, r) {
        int cid = 0;
        while (cid < c && maze[i][cid] == '.') ++cid;
        if (cid < c) {
            // cannot left
            invalid_state[i][cid] |= (1 << 2);
        }
        cid = c - 1;
        while (cid >= 0 && maze[i][cid] == '.') --cid;
        if (cid >= 0) {
            // cannot right
            invalid_state[i][cid] |= (1 << 3);
        }
    }
    rep (i, c) {
        int rid = 0;
        while (rid < r && maze[rid][i] == '.') ++rid;
        if (rid < r) {
            // cannot up
            invalid_state[rid][i] |= (1 << 0);
        }
        rid = r - 1;
        while (rid >= 0 && maze[rid][i] == '.') --rid;
        if (rid >= 0) {
            // cannot down
            invalid_state[rid][i] |= (1 << 1);
        }
    }
    int ret = 0;
    rep (i, r) rep (j, c) {
        if (maze[i][j] != '.') {
            int cur_dir = get_cur_dir(maze[i][j]);
            // check if cur dir ok
            // NOTICE("%d, %d -> st %d, dir %d", i, j, invalid_state[i][j], cur_dir);
            if (((invalid_state[i][j] >> cur_dir) & 1) == 0) {
                continue;
            }
            if (invalid_state[i][j] != 15) {
                ++ret;
            } else {
                return -1;
            }
        }
    }
    return ret;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d", &r, &c);
        rep (i, r) {
            scanf("%s", maze[i]);
        }
        int ans = solve();
        if (ans == -1) {
            printf("Case #%d: IMPOSSIBLE\n", Case++);
        } else {
            printf("Case #%d: %d\n", Case++, ans);
        }
    }
    return 0;
}