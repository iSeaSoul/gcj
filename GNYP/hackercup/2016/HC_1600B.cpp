/**
 * @author - liyan30 @ 2016-01-10 22:53
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

const int maxn = 1000 + 10;

int dp[maxn][3][3], n;
char maze[2][maxn];

int update(int& x, int y) {
    if (x == -1 || x > y) {
        x = y;
    }
}

int main() {
    freopen ("out", "w", stdout);
    repcase {
        fprintf(stderr, "solve case %d\n", Case);
        scanf("%d", &n);
        rep (i, 2) {
            scanf("%s", maze[i]);
        }
        memset(dp, -1, sizeof(dp));
        dp[0][0][0] = 0;
        // 0 - no guard but cleared
        // 1 - has guard previous
        // 2 - need guard
        rep (i, n) {
            if (maze[0][i] == 'X' && maze[1][i] == 'X') {
                repf (ps1, 0, 1) repf (ps2, 0, 1) {
                    if (dp[i][ps1][ps2] != -1) {
                        update(dp[i + 1][0][0], dp[i][ps1][ps2]);
                    }
                }
            } else if (maze[0][i] == 'X') {
                repf (ps1, 0, 1) {
                    if (dp[i][ps1][0] != -1) {
                        update(dp[i + 1][0][2], dp[i][ps1][0]);
                        update(dp[i + 1][0][1], dp[i][ps1][0] + 1);
                    }
                    if (dp[i][ps1][1] != -1) {
                        update(dp[i + 1][0][1], dp[i][ps1][1]);
                    }
                    if (dp[i][ps1][2] != -1) {
                        update(dp[i + 1][0][2], dp[i][ps1][2]);
                        update(dp[i + 1][0][1], dp[i][ps1][2] + 1);
                    }
                }
            } else if (maze[1][i] == 'X') {
                repf (ps2, 0, 1) {
                    if (dp[i][0][ps2] != -1) {
                        update(dp[i + 1][2][0], dp[i][0][ps2]);
                        update(dp[i + 1][1][0], dp[i][0][ps2] + 1);
                    }
                    if (dp[i][1][ps2] != -1) {
                        update(dp[i + 1][1][0], dp[i][1][ps2]);
                    }
                    if (dp[i][2][ps2] != -1) {
                        update(dp[i + 1][2][0], dp[i][2][ps2]);
                        update(dp[i + 1][1][0], dp[i][2][ps2] + 1);
                    }
                }
            } else {
                if (dp[i][0][0] != -1) {
                    update(dp[i + 1][2][2], dp[i][0][0]);
                    update(dp[i + 1][1][0], dp[i][0][0] + 1);
                    update(dp[i + 1][0][1], dp[i][0][0] + 1);
                    update(dp[i + 1][1][1], dp[i][0][0] + 2);
                }
                if (dp[i][0][1] != -1) {
                    update(dp[i + 1][2][1], dp[i][0][1]);
                    update(dp[i + 1][1][1], dp[i][0][1] + 1);
                }
                if (dp[i][0][2] != -1) {
                    update(dp[i + 1][2][2], dp[i][0][2]);
                    update(dp[i + 1][0][1], dp[i][0][2] + 1);
                    update(dp[i + 1][1][2], dp[i][0][2] + 1);
                    update(dp[i + 1][1][1], dp[i][0][2] + 2);
                }
                if (dp[i][1][0] != -1) {
                    update(dp[i + 1][1][2], dp[i][1][0]);
                    update(dp[i + 1][1][1], dp[i][1][0] + 1);
                }
                if (dp[i][1][1] != -1) {
                    update(dp[i + 1][1][1], dp[i][1][1]);
                }
                if (dp[i][1][2] != -1) {
                    update(dp[i + 1][1][2], dp[i][1][2]);
                    update(dp[i + 1][1][1], dp[i][1][2] + 1);
                }
                if (dp[i][2][0] != -1) {
                    update(dp[i + 1][2][2], dp[i][2][0]);
                    update(dp[i + 1][1][0], dp[i][2][0] + 1);
                    update(dp[i + 1][2][1], dp[i][2][0] + 1);
                    update(dp[i + 1][1][1], dp[i][2][0] + 2);
                }
                if (dp[i][2][1] != -1) {
                    update(dp[i + 1][2][1], dp[i][2][1]);
                    update(dp[i + 1][1][1], dp[i][2][1] + 1);
                }
                if (dp[i][2][2] != -1) {
                    update(dp[i + 1][2][2], dp[i][2][2]);
                    update(dp[i + 1][1][2], dp[i][2][2] + 1);
                    update(dp[i + 1][2][1], dp[i][2][2] + 1);
                    update(dp[i + 1][1][1], dp[i][2][2] + 2);
                }
            }
        }
        int ret = -1;
        repf (s1, 0, 1) repf (s2, 0, 1) {
            if (dp[n][s1][s2] != -1) {
                update(ret, dp[n][s1][s2]);
            }
        }
        cout << "Case #" << Case++ << ": " << ret << endl;
    }
    return 0;
}