/**
 * @author - liyan30 @ 2015-12-30 15:45
 * @brief - From sky to the sea.
 **/

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

#define LOG(level, fmt, arg...) \
    printf("[" #level "] [Line:%d] " fmt"\n", __LINE__, ##arg);

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

int main() {
    freopen ("C.out", "w", stdout);
    repcase {
        int c, n, maxv, a[102];
        scanf("%d%d%d", &c, &n, &maxv);
        rep (i, n) {
            scanf("%d", &a[i]);
        }
        sort(a, a + n);
        long long sum = 0;
        int ret = 0;
        int idx = 0;
        while (sum < maxv) {
            if (idx == n) {
                // no more existed coins
                while (sum < maxv) {
                    // add {sum + 1}
                    sum += (sum + 1) * c;
                    ++ret;
                }
                break;
            }
            while (sum < maxv && sum + 1 < a[idx]) {
                // add {sum + 1}
                sum += (sum + 1) * c;
                ++ret;
            }
            for (; idx < n && sum < maxv && a[idx] <= sum + 1; ++idx) {
                sum += (long long)a[idx] * c;
            }
        }
        printf("Case #%d: %d\n", Case++, ret);
    }
    return 0;
}