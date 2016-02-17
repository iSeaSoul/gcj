/**
 * @author - iSea_baidu @ 2016-02-17 21:10
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

const int maxn = 100 + 10;
const int maxh = 1000 + 10;

struct balloon {
    int pos, height;
};

int n, H, max_energy, velocity[maxh];
balloon balloons[maxn];

bool can_reach(int dis, int vel, int tm) {
    if (dis == 0) {
        return true;
    }
    if (vel == 0) {
        return false;
    }
    int dis_sign = dis / abs(dis);
    int vel_sign = vel / abs(vel);
    if (dis_sign == vel_sign) {
        return false;
    }
    return vel * tm * vel_sign >= dis * dis_sign;
}

bool can_move_within_limited_time(int tm) {
    int left_enerey = max_energy;
    rep (i, n) {
        int need_enerey = 0;
        while (true) {
            if (balloons[i].height + need_enerey >= H && 
                    balloons[i].height - need_enerey < 0) {
                // failed
                return false;
            }
            if (balloons[i].height + need_enerey < H) {
                int dis = balloons[i].pos;
                int vel = velocity[balloons[i].height + need_enerey];
                if (can_reach(dis, vel, tm)) {
                    break;
                }
            }
            if (balloons[i].height - need_enerey >= 0) {
                int dis = balloons[i].pos;
                int vel = velocity[balloons[i].height - need_enerey];
                if (can_reach(dis, vel, tm)) {
                    break;
                }
            }
            ++need_enerey;
        }
        left_enerey -= need_enerey;
        if (left_enerey < 0) {
            return false;
        }
    }
    return true;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d%d", &n, &H, &max_energy);
        rep (i, H) {
            scanf("%d", &velocity[i]);
        }
        rep (i, n) {
            scanf("%d%d", &balloons[i].pos, &balloons[i].height);
        }

        int l = 0, r = 10001;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (can_move_within_limited_time(mid)) {
                // try less
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        if (r == 10001) {
            printf("Case #%d: IMPOSSIBLE\n", Case++);
        } else {
            printf("Case #%d: %d\n", Case++, r + 1);
        }
    }
    return 0;
}