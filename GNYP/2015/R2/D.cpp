/**
 * @author - iSea_baidu @ 2016-01-12 20:28
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

int lcm(int x, int y) {
    return x * y / __gcd(x, y);
}

template <int mod>
struct int_mod {
    int data;

    int_mod(int _d = 0): data(_d % mod) {}

    bool zero() const { 
        return data == 0; 
    }
};

template <int mod>
int_mod<mod> operator+(const int_mod<mod>& lhs, const int_mod<mod>& rhs) {
    int ret = lhs.data + rhs.data;
    if (ret >= mod) ret -= mod;
    return {ret};
}

template <int mod>
int_mod<mod> operator-(const int_mod<mod>& lhs, const int_mod<mod>& rhs) {
    return {(lhs.data + mod - rhs.data) % mod};
}

template <int mod>
int_mod<mod> operator*(const int_mod<mod>& lhs, const int_mod<mod>& rhs) {
    return {int((long long)lhs.data * rhs.data % mod)};
}

template <int mod>
int_mod<mod> operator^(int_mod<mod> a, int p) {
    int_mod<mod> ret(1);
    while (p) {
        if (p & 1) ret = ret * a;
        a = a * a;
        p >>= 1;
    }
    return ret;
}

template <int mod>
int_mod<mod> operator/(const int_mod<mod>& lhs, const int_mod<mod>& rhs) {
    // WARNING: only work if mod is a prime number
    return lhs * (rhs ^ (mod - 2));
}

template <int mod>
ostream& operator<<(ostream& os, const int_mod<mod>& m) {
    return os << m.data;
}

const int mod = 1000000007;
using mint = int_mod<mod>;

const int alter_permutation[4][2] = {
    {1, 1},
    // 2...
    {3, 2},
    // 122...
    // 122...
    {6, 2},
    // 222112...
    // 112222...
    {4, 3}
    // 2212...
    // 1212...
    // 1222...
};

void update(mint& x, mint y) {
    x = x + y;
}

mint solve(int R, int C) {
    mint dp[102][13][2] = {0};
    // pstate: 0/1 - noneed/need 2 lines of 333
    // curlcm: [1, 12] - current lcm
    dp[0][1][0] = dp[0][1][1] = 1;
    rep (i, R) {
        repf (curlcm, 1, 12) {
            if (!dp[i][curlcm][1].zero()) {
                // NOTICE("%d,%d,%d -> %d", i, curlcm, 1, dp[i][curlcm][1].data);
                if (i + 2 <= R) {
                    update(dp[i + 2][curlcm][0], dp[i][curlcm][1]);
                }
            }
            if (!dp[i][curlcm][0].zero()) {
                // NOTICE("%d,%d,%d -> %d", i, curlcm, 0, dp[i][curlcm][0].data);
                rep (k, 4) {
                    if (C % alter_permutation[k][0] == 0 && i + alter_permutation[k][1] <= R) {
                        int newlcm = lcm(curlcm, alter_permutation[k][0]);
                        update(dp[i + alter_permutation[k][1]][newlcm][1],
                                dp[i][curlcm][0] * mint(alter_permutation[k][0]));
                    }
                }
            }
        }
    }
    mint ret = 0;
    repf (curlcm, 1, 12) rep (pstate, 2) {
        // NOTICE("%d,%d -> %d", curlcm, pstate, dp[C][curlcm][pstate].data);
        update(ret, dp[R][curlcm][pstate] / mint(curlcm));
    }
    return ret;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        int r, c;
        cin >> r >> c;
        cout << "Case #" << Case++ << ": " << solve(r, c) << endl;
    }
    return 0;
}