/**
 * @author - iSea_baidu @ 2016-02-17 16:05
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

struct subnet {
    int dim;
    unsigned int masknum;

    static const int full_length = 32;

    void read() {
        unsigned int a, b, c, d;
        scanf("%u.%u.%u.%u/%u", &a, &b, &c, &d, &dim);
        masknum = (a << 24) | (b << 16) | (c << 8) | d;
        masknum = (masknum >> (full_length - dim));
    }
    void print() const {
        if (dim == 0) {
            printf("0.0.0.0/0\n");
            return;
        }
        unsigned int fullnum = getfullnum();
        printf("%u.%u.%u.%u/%d\n", getmask(fullnum, 24), getmask(fullnum, 16),
            getmask(fullnum, 8), getmask(fullnum, 0), dim);
    }

    unsigned int getmask(unsigned int num, int shift_length) const {
        return (num >> shift_length) & 255;
    }

    unsigned int getfullnum() const {
        return (masknum << (full_length - dim));
    }

    bool operator<(const subnet& rhs) const {
        return getfullnum() == rhs.getfullnum()?
                dim < rhs.dim : getfullnum() < rhs.getfullnum();
    }

    bool is_sub(const subnet& psub) const {
        return dim >= psub.dim && psub.masknum == (masknum >> (dim - psub.dim));
    }
};

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        int n;
        scanf("%d", &n);
        vector<unsigned int> allmasks[33];
        rep (i, n) {
            subnet foo;
            foo.read();
            // foo.print();
            allmasks[foo.dim].push_back(foo.masknum);
        }
        vector<subnet> ret;
        for (int dim = 32; dim >= 1; --dim) {
            sort(allmasks[dim].begin(), allmasks[dim].end());
            allmasks[dim].erase(unique(allmasks[dim].begin(), allmasks[dim].end()), 
                        allmasks[dim].end());
            for (int i = 0; i < SZ(allmasks[dim]); ++i) {
                if (i + 1 < SZ(allmasks[dim])) {
                    // combine 10/11 -> 1
                    if ((allmasks[dim][i] ^ allmasks[dim][i + 1]) == 1) {
                        allmasks[dim - 1].push_back(allmasks[dim][i] >> 1);
                        ++i;
                        continue;
                    }
                }
                ret.push_back({dim, allmasks[dim][i]});
            }
        }
        sort(ret.begin(), ret.end());
        printf("Case #%d:\n", Case++);
        if (SZ(allmasks[0]) != 0) {
            printf("0.0.0.0/0\n");
            continue;
        }
        rep (i, SZ(ret)) {
            bool has_fa = false;
            rep (j, i) {
                if (ret[i].is_sub(ret[j])) {
                    has_fa = true;
                    break;
                }
            }
            if (!has_fa) {
                ret[i].print();
            }
        }
    }
    return 0;
}