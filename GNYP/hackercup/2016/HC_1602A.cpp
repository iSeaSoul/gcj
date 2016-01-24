/**
 * @author - iSea_baidu @ 2016-01-24 01:53
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

const int maxn = 100000 + 10;

int n, num[maxn];
char target[maxn], ori[maxn];

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d", &n);
        scanf("%s%s", ori, target);
        num[n] = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (i < n - 1) {
                num[i] = num[i + 1];
                if (target[i] != target[i + 1]) {
                    ++num[i];
                }
            } else {
                num[i] = 1;
            }
        }
        int same_idx = -1;
        int cnum = 0;
        int ret = num[0];
        rep (i, n) {
            if (i > same_idx) {
                same_idx = i;
                while (same_idx < n && target[same_idx] == ori[same_idx]) ++same_idx;
            }
            // [i, same_idx)
            to_min(ret, max(cnum, num[same_idx]));
            // after
            if (i == 0) {
                cnum = 1;
            } else {
                if (target[i] != target[i - 1]) {
                    ++cnum;
                }
            }
        }
        printf("Case #%d: %d\n", Case++, ret);
    }
    return 0;
}