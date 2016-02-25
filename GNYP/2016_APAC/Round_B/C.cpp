/**
 * @author - iSea_baidu @ 2016-02-24 17:16
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

vector<pair<long long, int> > prime_factorization(long long x) {
    vector<pair<long long, int> > ret;
    for (long long i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                x /= i;
                ++cnt;
            }
            ret.push_back({i, cnt});
        }
    }
    if (x != 1) {
        ret.push_back({x, 1});
    }
    return move(ret);
}

const int maxn = (1 << 14) + 10;

bool vis[maxn], winst[maxn];
vector<pair<long long, int> > prime_facs;

long long get_prime_fac_item(int x) {
    long long ret = 1LL;
    rep (i, prime_facs[x].second) {
        ret *= prime_facs[x].first;
    }
    return ret;
}

bool is_prime(long long x) {
    return x == 1 || prime_factorization(x)[0].first == x;
}

bool is_good(long long x) {
    int sumx = 0;
    while (x) {
        sumx += x % 10;
        x /= 10;
    }
    return is_prime(sumx);
}

long long get_state_num(int st) {
    long long x = 1LL;
    rep (i, SZ(prime_facs)) {
        if ((st >> i) & 1) {
            x *= get_prime_fac_item(i);
        }
    }
    return x;
}

bool is_good_state(int st) {
    return is_good(get_state_num(st));
}

bool can_win(int st) {
    if (vis[st]) {
        return winst[st];
    }
    vis[st] = true;
    if (is_good_state(st)) {
        return winst[st] = false;
    }
    rep (i, SZ(prime_facs)) {
        if ((st >> i) & 1) {
            if (!can_win(st ^ (1 << i))) {
                return winst[st] = true;
            }
        }
    }
    return winst[st] = false;
}

int main() {
    repcase {
        long long x;
        NOTICE("solving case %d...", Case);
        scanf("%lld", &x);
        prime_facs = prime_factorization(x);
        memset(vis, 0, sizeof(vis));
        printf("Case #%d: %s\n", Case++, can_win((1 << SZ(prime_facs)) - 1)? "Laurence" : "Seymour");
    }
    return 0;
}