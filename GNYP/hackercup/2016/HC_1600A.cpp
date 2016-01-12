/**
 * @author - liyan30 @ 2016-01-10 22:34
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

const int maxn = 2000 + 10;

int n, x[maxn], y[maxn];

int sqr(int x) { return x * x; }

int main() {
    freopen ("out", "w", stdout);
    repcase {
        fprintf(stderr, "solve case %d\n", Case);
        scanf("%d", &n);
        rep (i, n) {
            scanf("%d%d", &x[i], &y[i]);
        }
        long long ret = 0;
        rep (i, n) {
            unordered_map<int, int> len_map;
            rep (j, n) if (j != i) {
                int dis2 = sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
                ret += len_map[dis2]++;
            }
        }
        cout << "Case #" << Case++ << ": " << ret << endl;
    }
    return 0;
}