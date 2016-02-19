/**
 * @author - iSea_baidu @ 2016-02-18 14:34
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

const long long inf = (long long)1e16;

struct fraction {
    long long x;
    int y;

    bool operator<(const fraction& rhs) const {
        return x * rhs.y < y * rhs.x;
    }
    bool operator>(const fraction& rhs) const {
        return x * rhs.y > y * rhs.x;
    }
};

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        int n;
        scanf("%d", &n);
        bool has_full_percent = false, failed = false;
        long long ret;
        fraction leftlim = {0, 1}, rightlim = {inf, 1};
        rep (i, n) {
            long long num;
            int percent;
            scanf("%d%lld", &percent, &num);
            if (percent == 100) {
                if (has_full_percent) {
                    if (ret != num) {
                        failed = true;
                    }
                }
                has_full_percent = true;
                ret = num;
            } else if (percent == 0) {
                to_max(leftlim, {num * 100, 1});
            } else {
                to_max(leftlim, {num * 100, percent + 1});
                to_min(rightlim, {num * 100, percent});
            }
            // NOTICE("l %lld/%d, r %lld/%d", leftlim.x, leftlim.y, 
            //         rightlim.x, rightlim.y);
        }
        if (failed) {
            printf("Case #%d: -1\n", Case++);
            continue;
        }
        if (has_full_percent) {
            printf("Case #%d: %lld\n", Case++, ret);
            continue;
        }
        long long left = leftlim.x / leftlim.y + 1;
        long long right = rightlim.x / rightlim.y;
        if (left == right) {
            printf("Case #%d: %lld\n", Case++, right);
        } else {
            printf("Case #%d: -1\n", Case++);
        }
    }
    return 0;
}