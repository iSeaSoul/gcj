/**
 * @author - iSea_baidu @ 2016-01-25 17:34
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

const int maxn = 500 + 10;
const long double inf = 1e100;

struct rabbit {
    int x, v;

    bool operator<(const rabbit& r) const {
        return v == r.v? x > r.x : v > r.v;
    }

    long double getpos(long double cur_tm) const {
        return x + cur_tm * v;
    }
};

rabbit rabbits[maxn];
int my_v, n;
vector<rabbit> left_rabbits, right_rabbits;

// state : [left uncaught fastest rabbit, right uncaught fastest rabbit]
// value : fastest time for the state
long double dp[maxn][maxn];
long double buffer_tm[maxn];

long double get_reach_tm(rabbit r, long double passed_tm) {
    return (r.x + r.v * passed_tm) / (my_v - r.v) + passed_tm;
}

long double solve() {
    sort(left_rabbits.begin(), left_rabbits.end());
    sort(right_rabbits.begin(), right_rabbits.end());

    int ln = SZ(left_rabbits);
    int rn = SZ(right_rabbits);

    repf (i, 0, ln) repf (j, 0, rn) {
        dp[i][j] = inf;
    }
    dp[0][0] = 0;

    long double ret = inf;
    repf (l, 0, ln) repf (r, 0, rn) {
        if (dp[l][r] == inf) {
            continue;
        }
        // go left
        repf (nl, l, ln - 1) {
            buffer_tm[nl] = get_reach_tm(left_rabbits[nl], dp[l][r]);
        }
        int idx = l, idy;
        while (idx < ln) {
            for (idy = idx + 1; idy < ln && buffer_tm[idy] <= buffer_tm[idx]; ++idy) ;
            to_min(dp[idy][r], buffer_tm[idx] + left_rabbits[idx].getpos(buffer_tm[idx]) / my_v);
            if (idy == ln && r == rn) {
                // if catch all, no need to return
                to_min(ret, buffer_tm[idx]);
            }
            idx = idy;
        }
        // go right
        repf (nr, r, rn - 1) {
            buffer_tm[nr] = get_reach_tm(right_rabbits[nr], dp[l][r]);
        }
        idx = r;
        while (idx < rn) {
            for (idy = idx + 1; idy < rn && buffer_tm[idy] <= buffer_tm[idx]; ++idy) ;
            to_min(dp[l][idy], buffer_tm[idx] + right_rabbits[idx].getpos(buffer_tm[idx]) / my_v);
            if (l == ln && idy == rn) {
                // if catch all, no need to return
                to_min(ret, buffer_tm[idx]);
            }
            idx = idy;
        }
    }
    return ret;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d", &my_v, &n);
        rep (i, n) {
            scanf("%d", &rabbits[i].x);
        }
        rep (i, n) {
            scanf("%d", &rabbits[i].v);
        }
        left_rabbits.clear();
        right_rabbits.clear();
        rep (i, n) {
            if (rabbits[i].x < 0) {
                // left_rabbits.push_back(rabbits[i]);
                left_rabbits.push_back({-rabbits[i].x, rabbits[i].v});
            } else {
                right_rabbits.push_back(rabbits[i]);
            }
        }

        printf("Case #%d: %.10Lf\n", Case++, solve());
    }
    return 0;
}