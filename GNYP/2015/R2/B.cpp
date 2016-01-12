/**
 * @author - iSea_baidu @ 2016-01-11 16:32
 * @brief - From sky to the sea.
 **/

#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
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
#define repcase int t, Case = 1; for (cin >> t; t; --t)
template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

const int maxn = 100 + 10;
const long double eps = 1e-12;

int sgn(long double x) {
    return (x > eps) - (x < -eps);
}

struct source {
    long double rate, temp;
    void input() {
        // scanf("%lf%lf", &rate, &temp);
        cin >> rate >> temp;
    }
};

source sources[maxn];
long double totv, tempX;
int n;

long double solve() {
    sort(sources, sources + n, [](source x, source y) -> bool {
        return x.temp < y.temp;
    });
    if (sources[n - 1].temp < tempX - 1e-6 || sources[0].temp > tempX + 1e-6) {
        return -1;
    }
    long double init_tdif = 0;
    // initial temperature diff
    long double init_frate = 0;
    // initial flow rate
    rep (i, n) {
        init_tdif += sources[i].rate * (sources[i].temp - tempX);
        init_frate += sources[i].rate;
    }
    // try adjust flow rate
    if (init_tdif > 1e-8) {
        for (int id = n - 1; id >= 0; --id) {
            long double i_tdif = (sources[id].temp - tempX);
            if (i_tdif > 0) {
                long double max_contribute_drate = min(sources[id].rate, init_tdif / i_tdif);
                init_tdif -= max_contribute_drate * i_tdif;
                init_frate -= max_contribute_drate;
                if (abs(init_tdif) < 1e-8) {
                    break;
                }
            } else {
                break;
            }
        }
    }
    if (init_tdif < -1e-8) {
        for (int id = 0; id < n; ++id) {
            long double i_tdif = (sources[id].temp - tempX);
            if (i_tdif < 0) {
                long double max_contribute_drate = min(sources[id].rate, init_tdif / i_tdif);
                init_tdif -= max_contribute_drate * i_tdif;
                init_frate -= max_contribute_drate;
                if (abs(init_tdif) < 1e-8) {
                    break;
                }
            } else {
                break;
            }
        }
    }
    if (abs(init_tdif) < 1e-8) {
        return totv / init_frate;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(8);

    repcase {
        NOTICE("solving case %d...", Case);
        // scanf("%d%lf%lf", &n, &totv, &tempX);
        cin >> n >> totv >> tempX;
        rep (i, n) {
            sources[i].input();
        }
        long double ret = solve();
        if (ret == -1) {
            // printf("Case #%d: IMPOSSIBLE\n", Case++);
            cout << "Case #" << Case++ << ": IMPOSSIBLE" << endl;
        } else {
            // printf("Case #%d: %.10lf\n", Case++, ret);
            cout << "Case #" << Case++ << ": " << ret << endl;
        }
    }
    return 0;
}