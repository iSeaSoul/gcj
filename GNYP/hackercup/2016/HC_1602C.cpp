/**
 * @author - iSea_baidu @ 2016-01-24 02:45
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

struct ladder {
    int x, h;
    void input() {
        scanf("%d%d", &x, &h);
    }
};

const int maxn = 200000 + 10;
const int mod = 1000000007;

ladder ladders[maxn];
int n;

int st[maxn], top;
long long sum[maxn], sumx[maxn], sumx2[maxn];

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d", &n);
        rep (i, n) {
            ladders[i].input();
        }
        sort(ladders, ladders + n, [](ladder x, ladder y) -> bool {
            return x.x < y.x;
        });
        top = -1;
        long long ret = 0;
        rep (i, n) {
            while (top != -1 && ladders[st[top]].h < ladders[i].h) --top;
            if (top != -1 && ladders[st[top]].h == ladders[i].h) {
                // NOTICE("ok %d h %d -> %lld %lld %lld", i, ladders[i].h, sum[top], sumx[top], sumx2[top]);
                long long newx2 = (long long)ladders[i].x * ladders[i].x % mod;
                ret += sum[top] * newx2 % mod;
                ret += sumx2[top];
                ret -= (long long)2 * ladders[i].x * sumx[top] % mod;
                ret = (ret % mod + mod) % mod;

                sum[top] += 1;
                sumx[top] += ladders[i].x;
                sumx2[top] += newx2;
            } else {
                long long newx2 = (long long)ladders[i].x * ladders[i].x % mod;
                st[++top] = i;
                sum[top] = 1;
                sumx[top] = ladders[i].x;
                sumx2[top] = newx2;
            }
            sumx[top] %= mod;
            sumx2[top] %= mod;
        }
        printf("Case #%d: %lld\n", Case++, (ret % mod + mod) % mod);
    }
    return 0;
}