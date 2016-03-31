/**
 * @author - iSea_baidu @ 2016-03-16 11:28
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

int solve(long long pos, long long period_length) {
    if (period_length == 1LL || pos == period_length) {
        return 0;
    }
    return period_length < pos? 1 - solve(period_length * 2 - pos, period_length >> 1):
            solve(pos, period_length >> 1);
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        long long x;
        scanf("%lld", &x);
        long long period_length = 1LL;
        while (x / 2 >= period_length) period_length <<= 1;
        printf("Case #%d: %d\n", Case++, solve(x, period_length));
    }
    return 0;
}