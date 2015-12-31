/**
 * @author - liyan30 @ 2015-12-30 16:25
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
#define repcase int t, Case = 1; for (cin >> t; t; --t)

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

long long pow10[18];

int get_length(long long x) {
    return x < 10? 1 : get_length(x / 10) + 1;
}

long long get_rev_prefix(long long x, int prefix_len) {
    long long ret = 0;
    int length = get_length(x);
    rep (i, length) {
        int c = x % 10;
        x /= 10;
        if (i >= length - prefix_len) {
            ret = ret * 10 + c;
        }
    }
    return ret;
}

long long solve_greedy(long long n) {
    int length = get_length(n);
    if (length == 1) {
        return n;
    }
    long long ret = 0;
    for (int len = 1; len < length; ++len) {
        // 100 -> 109 -> 901 -> 999 -> 1000
        ret += pow10[len / 2] + pow10[(len + 1) / 2] - 1;
    }

    // 100000 -> 123 | 346
    long long left_ret = n - pow10[length - 1];
    int prefix_len = length / 2;
    int suffix_len = length - prefix_len;

    // check if the number can be reversed
    if (n % pow10[suffix_len] == 0) {
        return min(ret + left_ret, solve_greedy(n - 1) + 1);
    }

    return ret + min(left_ret, (n % pow10[suffix_len]) + get_rev_prefix(n, prefix_len));
}

int main() {
    freopen ("A.out", "w", stdout);
    pow10[0] = 1LL;
    repf (i, 1, 15) {
        pow10[i] = pow10[i - 1] * 10;
    }
    repcase {
        long long n;
        cin >> n;
        // solve_naive(n);
        cout << "Case #" << Case++ << ": " << solve_greedy(n) << endl;
    }
    return 0;
}