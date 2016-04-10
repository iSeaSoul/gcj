/**
 * @author - iSea_baidu @ 2016-04-09 21:42
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

long long next_layer_pos(long long d, int c, int k) {
    return (d - 1) * k + c;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        int k, c, s;
        scanf("%d%d%d", &k, &c, &s);
        int least_s = (k + c - 1) / c;
        if (s < least_s) {
            printf("Case #%d: IMPOSSIBLE\n", Case++);
        } else {
            printf("Case #%d:", Case++);
            for (int idx = 1; idx <= k; idx += c) {
                long long num = idx;
                for (int idj = 1; idj < c && idx + idj <= k; ++idj) {
                    num = next_layer_pos(num, idx + idj, k);
                }
                printf(" %lld", num);
            }
            puts("");
        }
    }
    return 0;
}