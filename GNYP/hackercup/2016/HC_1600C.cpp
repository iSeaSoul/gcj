/**
 * @author - liyan30 @ 2016-01-10 23:24
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

const int maxn = 100000 + 10;

long long sum[maxn];
int n, p, b[maxn];

int main() {
    freopen ("the_price_is_correct.txt", "r", stdin);
    freopen ("out", "w", stdout);
    repcase {
        fprintf(stderr, "solve case %d\n", Case);
        scanf("%d%d", &n, &p);
        rep (i, n) {
            scanf("%d", &b[i]);
        }
        repf (i, 1, n) {
            sum[i] = sum[i - 1] + b[i - 1];
        }
        long long ret = 0;
        repf (i, 1, n) {
            int cnt = lower_bound(sum, sum + i, sum[i] - p) - sum;
            ret += i - cnt;
        }
        cout << "Case #" << Case++ << ": " << ret << endl;
    }
    return 0;
}