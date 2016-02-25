/**
 * @author - iSea_baidu @ 2016-02-25 16:00
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

struct fraction {
    long long x, y;

    fraction() = default;
    fraction(long long _x, long long _y) {
        long long _g = __gcd(_x, _y);
        x = _x / _g;
        y = _y / _g;
    }

    bool operator<(const fraction& rhs) const {
        return x * rhs.y < y * rhs.x;
    }
    bool operator>(const fraction& rhs) const {
        return x * rhs.y > y * rhs.x;
    }
    bool operator==(const fraction& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

const int maxn = 2000 + 10;

set<fraction> frac_b;
int na, nb, nc, q, a[maxn], b[maxn], c[maxn];

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d%d", &na, &nb, &nc);
        rep (i, na) {
            scanf("%d", &a[i]);
        }
        rep (i, nb) {
            scanf("%d", &b[i]);
        }
        rep (i, nc) {
            scanf("%d", &c[i]);
        }
        frac_b.clear();
        rep (i, nb) rep (j, i) {
            frac_b.insert(fraction(b[i], b[j]));
            frac_b.insert(fraction(b[j], b[i]));
        }
        printf("Case #%d:\n", Case++);
        scanf("%d", &q);
        rep (i, q) {
            int xa, xb;
            scanf("%d%d", &xa, &xb);
            bool found = false;
            for (int i = 0; !found && i < na; ++i) rep (j, nc) {
                long long finala = (long long)xa * c[j];
                long long finalb = (long long)xb * a[i];
                if (frac_b.find(fraction(finala, finalb)) != frac_b.end()) {
                    found = true;
                }
            }
            puts(found? "Yes" : "No");
        }
    }
    return 0;
}