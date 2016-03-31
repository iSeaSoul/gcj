/**
 * @author - iSea_baidu @ 2016-03-18 14:42
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

int main() {
    repcase {
        int nPeople, nSp, bestscore;
        scanf("%d%d%d", &nPeople, &nSp, &bestscore);
        int ret = 0, possible_ret = 0;
        rep (i, nPeople) {
            int tot_score;
            scanf("%d", &tot_score);
            if (tot_score >= 3 * bestscore - 2) {
                ++ret;
            } else if (tot_score >= max(bestscore, 3 * bestscore - 4)) {
                ++possible_ret;
            }
        }
        ret += min(nSp, possible_ret);
        printf("Case #%d: %d\n", Case++, ret);
    }
    return 0;
}