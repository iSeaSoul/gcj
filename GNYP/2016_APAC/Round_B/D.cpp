/**
 * @author - iSea_baidu @ 2016-02-24 14:34
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
const int mod = 1000000007;

int add(int x, int y) {
    x += y;
    return x >= mod? x - mod : x;
}

int mul(int x, int y) {
    return (long long)x * y % mod;
}

int com[maxn][maxn], ways_equal[maxn][maxn];
int single_dp[maxn][maxn], multi_dp[maxn][maxn], num[maxn][4];
char buf[maxn];

void prepare() {
    rep (i, maxn) {
        com[i][0] = com[i][i] = 1;
        repf (j, 1, i - 1) {
            com[i][j] = add(com[i - 1][j - 1], com[i - 1][j]);
        }
    }
    repf (i, 1, maxn - 1) repf (j, 1, i) {
        ways_equal[i][j] = 0;
        repf (k, 0, j) {
            ways_equal[i][j] = add(ways_equal[i][j], mul(com[i][k], com[j][k]));
        }
        ways_equal[j][i] = ways_equal[i][j];
    }
    rep (i, maxn) {
        ways_equal[i][0] = ways_equal[0][i] = 1;
    }
}

// can be optimized
// preprecess next[x, 0] -> position of next 'a' after x
// then use it while enumerating

int calc_single(int l, int r) {
    if (single_dp[l][r] != -1) {
        return single_dp[l][r];
    }
    int& ret = single_dp[l][r];
    ret = 0;
    if (buf[l] != 'a' || r - l < 3) {
        return ret;
    }
    repf (bidx, l + 1, r) if (buf[bidx] == 'b') {
        int num_a = num[bidx][0] - num[l + 1][0];
        repf (cidx, bidx + 1, r) if (buf[cidx] == 'c') {
            int num_b = num[cidx][1] - num[bidx + 1][1];
            repf (didx, cidx + 1, r) if (buf[didx] == 'd') {
                int num_c = num[didx][2] - num[cidx + 1][2];
                int num_d = num[r + 1][3] - num[didx + 1][3];
                ret = add(ret, mul(ways_equal[num_a][num_c], ways_equal[num_b][num_d]));
            }
        }
    }
    // NOTICE("calc_single %d %d -> %d", l, r, ret);
    return ret;
}

int calc_multi(int l, int r) {
    if (multi_dp[l][r] != -1) {
        return multi_dp[l][r];
    }
    while (l <= r && buf[l] != 'a') ++l;
    if (r - l < 3) {
        return multi_dp[l][r] = 0;
    }
    int& ret = multi_dp[l][r];
    ret = calc_single(l, r);
    repf (i, l + 1, r - 3) {
        if (buf[i] == 'a') {
            ret = add(ret, mul(calc_single(l, i - 1), calc_multi(i, r)));
        }
    }
    // NOTICE("calc_multi %d %d -> %d", l, r, ret);
    return ret;
}

int main() {
    prepare();
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%s", buf);
        int len = strlen(buf);
        rep (k, 4) num[0][k] = 0;
        rep (i, len) {
            rep (k, 4) num[i + 1][k] = num[i][k];
            num[i + 1][buf[i] - 'a'] += 1;
        }
        memset(single_dp, -1, sizeof(single_dp));
        memset(multi_dp, -1, sizeof(multi_dp));
        int ret = 0;
        rep (i, len) {
            if (buf[i] == 'a') {
                ret = add(ret, calc_multi(i, len - 1));
            }
        }
        printf("Case #%d: %d\n", Case++, ret);
    }
    return 0;
}