/**
 * @author - iSea_baidu @ 2016-03-18 17:43
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

const int maxn = 100000 + 10;

int n, length;
double p_right[maxn];

double press_ok_directly() {
    if (n == length) {
        double pro_right = 1.0;
        rep (i, n) pro_right *= p_right[i];
        return 1 + (1 - pro_right) * (length + 1);
    }
    return length + 2;
}

int main() {
    repcase {
        scanf("%d%d", &n, &length);
        rep (i, n) {
            scanf("%lf", &p_right[i]);
        }
        double ret = press_ok_directly();
        double pro_right = 1.0;
        repf (left, 0, n) {
            double exp_press = (n - left + length - left + 1);
            exp_press += (1 - pro_right) * (length + 1);
            to_min(ret, exp_press);
            if (left < n) {
                pro_right *= p_right[left];
            }
        }
        printf("Case #%d: %.10lf\n", Case++, ret);
    }
    return 0;
}