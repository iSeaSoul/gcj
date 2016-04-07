/**
 * @author - iSea_baidu @ 2016-04-07 14:58
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

int n_foods;
long long total_m, fee;
map<long long, long long> t_minprice, purified_tminp;

// given buy times, calculate maximal days
long long calc_maxd(long long buy_times) {
    if (buy_times == 0) return 0;
    long long left_m = total_m - buy_times * fee;
    long long maxd = 0;
    long long prev_d = -1;
    for (const auto& tp : purified_tminp) {
        long long food_d = tp.first - prev_d;
        prev_d = tp.first;
        if (buy_times <= (left_m / tp.second) / food_d) {
            left_m -= buy_times * food_d * tp.second;
            maxd += food_d * buy_times;
        } else {
            maxd += max(0LL, left_m / tp.second);
            break;
        }
    }
    return maxd;
}

int main() {
    repcase {
        scanf("%lld%lld%d", &total_m, &fee, &n_foods);
        t_minprice.clear();
        purified_tminp.clear();
        rep (i, n_foods) {
            long long price, maxvalidt;
            scanf("%lld%lld", &price, &maxvalidt);
            if (!t_minprice.insert({maxvalidt, price}).second) {
                t_minprice[maxvalidt] = min(t_minprice[maxvalidt], price);
            }
        }

        // make the price ascending
        auto prev_it = t_minprice.rbegin();
        auto it = t_minprice.rbegin();
        for (++it; it != t_minprice.rend(); ++it) {
            if (it->second >= prev_it->second) {
                continue;
            }
            purified_tminp[prev_it->first] = prev_it->second;
            prev_it = it;
        }
        purified_tminp[prev_it->first] = prev_it->second;

        // do ternary search
        long long l = 0, r = total_m / fee + 1;
        long long maxt = 0;
        while (l <= r) {
            long long mid1 = (2 * l + r) / 3;
            long long mid2 = (l + 2 * r) / 3;
            long long maxd1 = calc_maxd(mid1);
            long long maxd2 = calc_maxd(mid2);
            to_max(maxt, max(maxd1, maxd2));
            if (maxd1 > maxd2) {
                r = mid2 - 1;
            } else {
                l = mid1 + 1;
            }
        }
        printf("Case #%d: %lld\n", Case++, maxt);
    }
    return 0;
}