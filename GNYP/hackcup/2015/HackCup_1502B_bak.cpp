/*
 * Not the fish.
 * liyan30 @ 2015-02-15 14:25
 */

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

const double eps = 1e-9;

const int MAXN = 20;

int main() {
    double C[MAXN + 1][MAXN + 1];
    repf (i, 0, MAXN) {
        C[i][0] = C[i][i] = 1.0;
        repf (j, 1, i - 1) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    repcase {
        double p;
        scanf ("%lf", &p);
        double p_pow[MAXN + 1];
        repf (i, 0, MAXN) {
            p_pow[i] = C[MAXN][i] * pow(p, i) * pow(1 - p, MAXN - i);
            // printf ("%lf%c", p_pow[i], " \n"[i == MAXN]);
        }

        double dp[2][MAXN] = {0.0};
        dp[1][0] = 1.0;

        int g_round = 1;
        bool flag = 0;
        double res = 0;

        rep (X, 1000) {
            memset (dp[flag], 0, sizeof(dp[flag]));
            for (int i = 0; i < MAXN; ++i) {
                double undone_psum = 0;
                for (int get = 0; i + get <= MAXN; ++get) {
                    if (get + i == MAXN) {
                        // printf ("add %d %lf\n", g_round, dp[!flag][i] * (1 - undone_psum));
                        res += g_round * dp[!flag][i] * (1 - undone_psum);
                    } else {
                        dp[flag][get + i] += dp[!flag][i] * p_pow[get];
                        undone_psum += p_pow[get];
                    }
                }
            }
            // for (int i = 0; i < MAXN; ++i) {
            //     printf ("%lf%c", dp[flag][i], " \n"[i == MAXN - 1]);
            // }
            g_round += 1;
            flag = !flag;
            if (g_round * accumulate(dp[flag], dp[flag] + MAXN, 0.0) < eps) {
                break;
            }
        }
        printf ("Case #%d: %.8lf\n", Case++, res);
    }
    return 0;
}