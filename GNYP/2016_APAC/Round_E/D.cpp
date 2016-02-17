/**
 * @author - iSea_baidu @ 2016-02-16 16:51
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

const int maxn = 2000000 + 10;

int arr[maxn], n, q;
long long sum[maxn], sumsum[maxn];

struct ret_t {
    long long sum;  // sum of sum less than K
    long long num;  // num of sum less than K
};

ret_t calc_sumnum_less_than(long long X) {
    long long rsum = 0LL, rnum = 0LL;
    int idx = 0; // sliding window pointer
    repf (i, 1, n) {
        while (idx <= i && sum[i] - sum[idx] >= X) ++idx;
        rnum += (i - idx);
        // sum[i] - sum[idx]
        // sum[i] - sum[idx + 1]
        // ...
        // sum[i] - sum[i - 1]
        rsum += sum[i] * (i - idx) - 
            (sumsum[i - 1] - (idx == 0? 0 : sumsum[idx - 1]));
    }
    return {rsum, rnum};
}

long long calc_sumsum_with_given_rank(long long rank) {
    long long l = 0, r = n * 111LL;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        ret_t cret = calc_sumnum_less_than(mid);
        if (cret.num + 1 <= rank) {
            // num (of sum less than mid) + 1 -> rank (of mid)
            // try bigger
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    ret_t final_ret = calc_sumnum_less_than(l - 1);
    // maximum num satisfy {num < rank}
    return final_ret.sum + (rank - final_ret.num) * (l - 1);
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d", &n, &q);
        sum[0] = sumsum[0] = 0LL;
        repf (i, 1, n) {
            scanf("%d", &arr[i]);
            sum[i] = sum[i - 1] + arr[i];
            sumsum[i] = sumsum[i - 1] + sum[i];
        }
        printf("Case #%d:\n", Case++);
        rep (i, q) {
            long long L, R;
            scanf("%lld%lld", &L, &R);
            printf("%lld\n", calc_sumsum_with_given_rank(R) -
                    calc_sumsum_with_given_rank(L - 1));
        }
    }
    return 0;
}