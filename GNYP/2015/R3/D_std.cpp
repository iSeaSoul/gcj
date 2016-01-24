/**
 * @author - iSea_baidu @ 2016-01-22 17:52
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
#include <unordered_map>
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

    bool operator<(const sumitem& rhs) const {
        return val < rhs.val;
    }
};

vector<sumitem> sumitems;
int n;

int getlog(long long x) {
    return x == 1? 0 : getlog(x >> 1) + 1;
}

vector<sumitem> divide(long long x, vector<sumitem> sums) {
    vector<sumitem> newsums;
    if (x == 0) {
        for (const sumitem& s : sums) {
            newsums.push_back({s.val, s.num >> 1});
        }
        return newsums;
    }

    int idx = 0;
    for (const sumitem& s : sums) {
        if (s.num != 0) {
            while (idx < SZ(sums) && sums[idx].val < s.val + x) ++idx;
            newsums.push_back(s);
            sums[idx].num -= s.num;
        }
    }
    return move(newsums);
}

vector<long long> get_raw_gap(vector<sumitem> sums, int sn) {
    vector<long long> ret;
    rep (i, sn) {
        if (sums[0].num > 1) {
            ret.push_back(0);
            sums = divide(0, sums);
        } else {
            ret.push_back(sums[1].val - sums[0].val);
            sums = divide(sums[1].val - sums[0].val, sums);
        }
    }
    return move(ret);
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
        vector<long long> ret = get_raw_gap(sumitems, rawn);

        // generate all sum state
        vector<sumitem> pos_sums;
        pos_sums.push_back({0, 1LL});
        rep (i, rawn) {
            unordered_map<long long, long long> sum_mp;
            for (const auto& x : pos_sums) {
                sum_mp[x.val] += x.num;
                sum_mp[x.val + ret[i]] += x.num;
            }
            pos_sums.clear();
            for (const auto& x : sum_mp) {
                pos_sums.push_back({x.first, x.second});
            }
            sort(pos_sums.begin(), pos_sums.end());
        }

        // try nagate a number if possible
        long long target = -sumitems[0].val;
        for (int idx = rawn - 1; target != 0 && idx >= 0; --idx) {
            long long leftsum = target - ret[idx];
            int gidx = lower_bound(pos_sums.begin(), pos_sums.end(), sumitem{leftsum, 0}) - pos_sums.begin();
            if (pos_sums[gidx].val == leftsum) {
                pos_sums = divide(ret[idx], pos_sums);
                ret[idx] = -ret[idx];
                target = leftsum;
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