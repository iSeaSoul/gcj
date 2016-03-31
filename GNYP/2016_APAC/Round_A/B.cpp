/**
 * @author - iSea_baidu @ 2016-03-17 15:03
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

int n, m;
double arr[maxn], sumarr[maxn];

int main() {
    repcase {
        scanf("%d%d", &n, &m);
        rep (i, n) {
            scanf("%lf", &arr[i]);
            arr[i] = log(arr[i]);
            sumarr[i + 1] = sumarr[i] + arr[i];
        }
        printf("Case #%d:\n", Case++);
        rep (i, m) {
            int l, r;
            scanf("%d%d", &l, &r);
            double ret = sumarr[r + 1] - sumarr[l];
            ret /= (r - l + 1);
            printf("%.10lf\n", exp(ret));
        }
    }
    return 0;
}