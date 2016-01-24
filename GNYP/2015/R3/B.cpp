/**
 * @author - iSea_baidu @ 2016-01-13 17:21
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

int n, k, sum[maxn];
int mindif[maxn], maxdif[maxn], dif[maxn];

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d", &n, &k);
        rep (i, n - k + 1) {
            scanf("%d", &sum[i]);
        }
        rep (i, k) {
            mindif[i] = maxdif[i] = 0;
        }
        repf (i, k, n - 1) {
            // dif (i - k) -> (i)
            dif[i] = sum[i - k + 1] - sum[i - k];
            if (i >= 2 * k) {
                dif[i] += dif[i - k];
            }
            to_min(mindif[i % k], dif[i]);
            to_max(maxdif[i % k], dif[i]);
        }

        int cursum = sum[0];
        rep (i, k) {
            // x[i] -> x[i] + mindif
            cursum += mindif[i];
            maxdif[i] -= mindif[i];
        }
        int max_maxdif = *max_element(maxdif, maxdif + k);
        int extra_mod = (cursum % k + k) % k;
        rep (i, k) {
            extra_mod -= (max_maxdif - maxdif[i]);
        }
        if (extra_mod > 0) {
            ++max_maxdif;
        }
        printf("Case #%d: %d\n", Case++, max_maxdif);
    }
    return 0;
}