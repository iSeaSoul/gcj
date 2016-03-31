/**
 * @author - iSea_baidu @ 2016-03-31 16:45
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

double tm[maxn], x[maxn];

int main() {
    repcase {
        double dis;
        int n, na;
        scanf("%lf%d%d", &dis, &n, &na);
        rep (i, n) {
            scanf("%lf%lf", &tm[i], &x[i]);
        }
        while (n > 0 && x[n - 1] >= dis) {
            --n;
        }
        if (n == 0) {
            tm[n] = 0; x[n] = dis;
        } else {
            double final_speed = (x[n] - x[n - 1]) / (tm[n] - tm[n - 1]);
            tm[n] = tm[n - 1] + (dis - x[n - 1]) / final_speed;
            x[n] = dis;
        }
        printf("Case #%d:\n", Case++);
        rep (i, na) {
            double acc;
            scanf("%lf", &acc);
            double wait_time = 0;
            repf (i, 0, n) {
                to_max(wait_time, tm[i] - sqrt(2 * x[i] / acc));
            }
            printf("%.10lf\n", wait_time + sqrt(2 * dis / acc));
        }
    }
    return 0;
}