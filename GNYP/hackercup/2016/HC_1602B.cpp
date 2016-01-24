/**
 * @author - iSea_baidu @ 2016-01-24 02:28
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
#define repcase int t, Case = 1; for (cin >> t; t; --t)
template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

const int maxn = 3000 + 10;

long double com[maxn][maxn];
int n, k;
long double p, powp[maxn], pownp[maxn];
long double prob[maxn], dp[maxn];

int main() {
    rep (i, maxn) {
        com[i][0] = com[i][i] = 1.0;
        repf (j, 1, i - 1) {
            com[i][j] = com[i - 1][j - 1] + com[i - 1][j];
        }
    }
    repcase {
        NOTICE("solving case %d...", Case);
        cin >> n >> k >> p;
        powp[0] = pownp[0] = 1.0;
        repf (i, 1, n) {
            powp[i] = powp[i - 1] * p;
            pownp[i] = pownp[i - 1] * (1 - p);
        }
        repf (y, k, n) {
            prob[y] = 0.0;
            repf (z, k, y) {
                prob[y] += com[y][z] * powp[z] * pownp[y - z];
            }
            // NOTICE("%d -> %Lf", y, prob[y]);
        }
        rep (i, n + 1) {
            dp[i] = 0.0;
        }
        for (int x = n; x; --x) {
            for (int y = k; y <= x; ++y) {
                to_max(dp[x - y], dp[x] + prob[y]);
            }
        }
        printf("Case #%d: %.10Lf\n", Case++, dp[0]);
    }
    return 0;
}