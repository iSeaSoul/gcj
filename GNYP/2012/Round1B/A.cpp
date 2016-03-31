/**
 * @author - iSea_baidu @ 2016-03-21 19:34
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

const int maxn = 200 + 10;
const double eps = 1e-12;

int n;
double p[maxn];

int sgn(double x) {
    return (x > eps) - (x < -eps);
}

double calc_minimum_radio(int idx) {
    double l = 0, r = 1;
    rep (iter_tms, 200) {
    // while (sgn(l - r) < 0) {
        double mid = (l + r) / 2;
        double sum = 0;
        rep (i, n) {
            sum += max(0.0, p[idx] + mid - p[i]);
        }
        if (sgn(sum - 1) < 0) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l * 100;
}

int main() {
    repcase {
        scanf("%d", &n);
        double sum = 0;
        rep (i, n) {
            scanf("%lf", &p[i]);
            sum += p[i];
        }
        rep (i, n) {
            p[i] /= sum;
        }
        printf("Case #%d:", Case++);
        rep (i, n) {
            printf(" %.10lf", calc_minimum_radio(i));
        }
        puts("");
    }
    return 0;
}