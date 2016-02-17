/**
 * @author - iSea_baidu @ 2016-02-15 14:05
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
#include <unordered_set>
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

const int maxn = 1000 + 10;
const int mod = 1000000007;

char buf[maxn];

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%s", buf);
        long long ret = 1LL;
        for (int idx = 0; buf[idx]; ++idx) {
            unordered_set<char> possible_char;
            for (int offset = -1; offset <= 1; ++offset) {
                int valid_idx = idx + offset;
                if (valid_idx >= 0 && buf[valid_idx]) {
                    possible_char.insert(buf[valid_idx]);
                }
            }
            ret *= SZ(possible_char);
            ret %= mod;
        }
        printf("Case #%d: %d\n", Case++, (int)ret);
    }
    return 0;
}