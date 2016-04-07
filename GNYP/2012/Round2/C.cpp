/**
 * @author - iSea_baidu @ 2016-04-06 18:05
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

const int maxn = 2000 + 10;
const int maxh = 1000000000;

int n_mounts, local_highest[maxn];
int height[maxn], slope[maxn];

bool solve() {
    memset(height, -1, sizeof(height));
    int pointer = 0;
    while (pointer != n_mounts) {
        height[pointer] = maxh;
        slope[pointer] = 0;
        pointer = local_highest[pointer];
    }
    pointer = 1;
    while (pointer != n_mounts) {
        while (pointer != n_mounts && height[pointer] != -1) {
            ++pointer;
        }
        if (pointer == n_mounts) {
            break;
        }
        int ipointer = pointer;
        int previous_iptr = ipointer - 1;
        int limit = local_highest[previous_iptr];
        int same_slope_maxh = height[limit];
        while (ipointer < limit) {
            slope[ipointer] = slope[previous_iptr] + 1;
            height[ipointer] = same_slope_maxh - (limit - ipointer) * slope[ipointer];
            ipointer = local_highest[ipointer];
        }
        if (ipointer != limit) {
            // out of the interval
            return false;
        }
    }
    return true;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d", &n_mounts);
        rep (i, n_mounts - 1) {
            scanf("%d", &local_highest[i]);
            --local_highest[i];
        }
        local_highest[n_mounts - 1] = n_mounts;
        if (!solve()) {
            printf("Case #%d: Impossible\n", Case++);
        } else {
            printf("Case #%d: ", Case++);
            rep (i, n_mounts) {
                printf("%d%c", height[i], " \n"[i == n_mounts - 1]);
            }
        }
    }
    return 0;
}