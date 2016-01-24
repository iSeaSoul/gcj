/**
 * @author - iSea_baidu @ 2016-01-22 14:00
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

struct sumitem {
    long long val;
    long long num;
};

vector<sumitem> sumitems;
int n;

int getlog(long long x) {
    return x == 1? 0 : getlog(x >> 1) + 1;
}

bool can_divide(long long x, vector<sumitem> sums) {
    if (x == 0) {
        for (const sumitem& s : sums) {
            if (s.num % 2 != 0) {
                return false;
            }
        }
        return true;
    }
    if (x < 0) x = -x;
    int idx = 0;
    for (const sumitem& s : sums) {
        if (s.num != 0) {
            while (idx < SZ(sums) && sums[idx].val < s.val + x) ++idx;
            if (idx >= SZ(sums) || sums[idx].val != s.val + x || sums[idx].num < s.num) {
                return false;
            }
            sums[idx].num -= s.num;
        }
    }
    return true;
}

vector<sumitem> divide(long long x, vector<sumitem> sums) {
    vector<sumitem> newsums;
    if (x == 0) {
        for (const sumitem& s : sums) {
            newsums.push_back({s.val, s.num >> 1});
        }
        return newsums;
    }

    bool usebigger = false;
    if (x < 0) {
        x = -x;
        usebigger = true;
    }
    int idx = 0;
    for (const sumitem& s : sums) {
        if (s.num != 0) {
            while (idx < SZ(sums) && sums[idx].val < s.val + x) ++idx;
            if (usebigger) {
                newsums.push_back({sums[idx].val, s.num});
            } else {
                newsums.push_back(s);
            }
            sums[idx].num -= s.num;
        }
    }
    return newsums;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d", &n);
        sumitems.resize(n);
        rep (i, n) {
            scanf("%lld", &sumitems[i].val);
        }
        long long sumn = 0;
        rep (i, n) {
            scanf("%lld", &sumitems[i].num);
            sumn += sumitems[i].num;
        }

        int rawn = getlog(sumn);
        vector<long long> ret;
        rep (i, rawn) {
            for (const auto& x : sumitems) {
                if (can_divide(x.val, sumitems)) {
                    ret.push_back(x.val);
                    sumitems = divide(x.val, sumitems);
                    break;
                }
            }
        }
        sort(ret.begin(), ret.end());
        printf("Case #%d: ", Case++);
        rep (i, rawn) {
            printf("%lld%c", ret[i], " \n"[i == rawn - 1]);
        }
    }
    return 0;
}