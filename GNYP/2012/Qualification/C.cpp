/**
 * @author - iSea_baidu @ 2016-03-18 16:04
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

int calc_rotated_pairs(int x, int lim, int pow10len) {
    int shifted_x = (x % 10) * pow10len + x / 10;
    int ret = 0;
    while (shifted_x != x) {
        if (shifted_x > x && shifted_x <= lim) {
            ++ret;
        }
        shifted_x = (shifted_x % 10) * pow10len + shifted_x / 10;
    }
    return ret;
}

int main() {
    repcase {
        int A, B;
        scanf("%d%d", &A, &B);
        long long ret = 0;
        int temp = A / 10, pow10len = 1;
        while (temp) {
            temp /= 10;
            pow10len *= 10;
        }
        repf (i, A, B) {
            ret += calc_rotated_pairs(i, B, pow10len);
        }
        printf("Case #%d: %lld\n", Case++, ret);
    }
    return 0;
}