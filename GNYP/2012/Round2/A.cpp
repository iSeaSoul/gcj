/**
 * @author - iSea_baidu @ 2016-04-06 16:53
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

const int maxn = 10000 + 10;

int n_veins, target;
int dis[maxn], max_length[maxn], max_freelen[maxn];

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d", &n_veins);
        rep (i, n_veins) {
            scanf("%d%d", &dis[i], &max_length[i]);
            max_freelen[i] = -1;
        }
        scanf("%d", &target);
        max_freelen[0] = dis[0];

        bool can_reach = false;
        rep (i, n_veins) {
            if (max_freelen[i] == -1) {
                continue;
            }
            if (dis[i] + max_freelen[i] >= target) {
                can_reach = true;
                break;
            }
            int pointer = i + 1;
            while (pointer < n_veins && dis[pointer] - dis[i] <= max_freelen[i]) {
                int possible_freelen = dis[pointer] - dis[i];
                to_min(possible_freelen, max_length[pointer]);
                // if (possible_freelen <= max_length[pointer]) {
                    to_max(max_freelen[pointer], possible_freelen);
                // }
                ++pointer;
            }
        }
        printf("Case #%d: %s\n", Case++, can_reach? "YES" : "NO");
    }
    return 0;
}