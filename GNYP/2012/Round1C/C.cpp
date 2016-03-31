/**
 * @author - iSea_baidu @ 2016-03-30 17:49
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

const int maxn = 100 + 10;

struct segment {
    long long length;
    int type;

    void input() {
        scanf("%lld%d", &length, &type);
    }
};

int len_a, len_b;
segment segments_a[maxn], segments_b[maxn];
long long dp[maxn][maxn];

int main() {
    repcase {
        scanf("%d%d", &len_a, &len_b);
        rep (i, len_a) {
            segments_a[i].input();
        }
        rep (i, len_b) {
            segments_b[i].input();
        }

        memset(dp, 0, sizeof(dp));
        rep (ida, len_a) rep (idb, len_b) {
            if (segments_a[ida].type == segments_b[idb].type) {
                // try match
                long long num_a = segments_a[ida].length;
                long long num_b = segments_b[idb].length;
                int pointer_a = ida - 1, pointer_b = idb - 1;
                dp[ida + 1][idb + 1] = dp[pointer_a + 1][pointer_b + 1] + min(num_a, num_b);
                while (true) {
                    if (num_a == num_b) {
                        break;
                    }
                    if (num_a < num_b) {
                        while (pointer_a >= 0 && segments_a[pointer_a].type != segments_a[ida].type) {
                            --pointer_a;
                        }
                        if (pointer_a < 0) {
                            break;
                        }
                        num_a += segments_a[pointer_a--].length;
                    } else {
                        while (pointer_b >= 0 && segments_b[pointer_b].type != segments_b[idb].type) {
                            --pointer_b;
                        }
                        if (pointer_b < 0) {
                            break;
                        }
                        num_b += segments_b[pointer_b--].length;
                    }
                    dp[ida + 1][idb + 1] = max(dp[ida + 1][idb + 1], dp[pointer_a + 1][pointer_b + 1] + min(num_a, num_b));
                }
            }
            dp[ida + 1][idb + 1] = max(dp[ida + 1][idb + 1], max(dp[ida][idb + 1], dp[ida + 1][idb]));
        }
        printf("Case #%d: %lld\n", Case++, dp[len_a][len_b]);
    }
    return 0;
}