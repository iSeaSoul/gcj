/**
 * @author - iSea_baidu @ 2016-02-15 16:21
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

double calc_expect_val(int begin, int op, int a, int b, int c, int n) {
    double dp[2][2] = {0.0};
    dp[0][begin] = 1.0;
    dp[0][1 - begin] = 0.0;
    rep (i, n) {
        int cur = !(i & 1);
        int pre = 1 - cur;
        dp[cur][0] = dp[cur][1] = 0.0;
        rep (curnum, 2) {
            dp[cur][curnum & op] += dp[pre][curnum] * a / 100.0;
            dp[cur][curnum | op] += dp[pre][curnum] * b / 100.0;
            dp[cur][curnum ^ op] += dp[pre][curnum] * c / 100.0;
        }
    }
    return dp[n & 1][1];
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        int n, x, k, a, b, c;
        scanf("%d%d%d%d%d%d", &n, &x, &k, &a, &b, &c);
        double expect_val[2][2];
        rep (begin_bit, 2) rep (change_bit, 2) {
            expect_val[begin_bit][change_bit] = calc_expect_val(begin_bit, change_bit, a, b, c, n);
        }
        double ret = 0;
        rep (bit_idx, 32) {
            ret += expect_val[(x >> bit_idx) & 1][(k >> bit_idx) & 1] * (1 << bit_idx);
        }
        printf("Case #%d: %.10lf\n", Case++, ret);
    }
    return 0;
}