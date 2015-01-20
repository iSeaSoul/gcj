/*
 * Not the fish.
 * iSea @ 2015-01-18 10:25
 */
#pragma comment(linker, "/STACK:1024000000,1024000000") 

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

#define sz(x) ((int)((x).size()))
#define out(x) cout << #x << ' ' << x << endl;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (cin >> t; t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

const int MAXN = 2000000 + 10;

int n, dp[MAXN][20];
vector<int> g[MAXN];

int calc(int x, int f) {
    if (dp[x][f] != -1) {
        return dp[x][f];
    }
    int& ret = dp[x][f];
    ret = f + 1;
    repeach (ch, g[x]) {
        int mincost = (-1u) >> 1;
        rep (k, 20) {
            if (k != f) {
                to_min(mincost, calc(*ch, k));
            }
        }
        ret += mincost;
    }
    return ret;
}

int main() {
    freopen ("D.out", "w", stdout);

    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));

    repcase {
        scanf ("%d", &n);
        rep (i, n) {
            g[i].clear();
        }
        rep (i, n) {
            int pid;
            scanf ("%d", &pid);
            if (pid == 0) continue;
            g[--pid].push_back(i);
        }
        memset (dp, -1, sizeof(dp));
        int ret = calc(0, 0);
        repf (i, 1, 19) {
            to_min(ret, calc(0, i));
        }
        printf ("Case #%d: %d\n", Case++, ret);
    }
    return 0;
}