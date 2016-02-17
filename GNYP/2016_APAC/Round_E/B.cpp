/**
 * @author - iSea_baidu @ 2016-02-15 14:16
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
#include <unordered_map>
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

int n, k, robots[4][maxn];
unordered_map<int, int> xorsum_dict;

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d", &n, &k);
        rep (i, 4) {
            rep (j, n) {
                scanf("%d", &robots[i][j]);
            }
        }
        xorsum_dict.clear();
        rep (s1, n) rep (s2, n) {
            xorsum_dict[robots[0][s1] ^ robots[1][s2]] += 1;
        }
        long long ret = 0LL;
        rep (s1, n) rep (s2, n) {
            ret += xorsum_dict[k ^ robots[2][s1] ^ robots[3][s2]];
        }
        printf("Case #%d: %lld\n", Case++, ret);
    }
    return 0;
}