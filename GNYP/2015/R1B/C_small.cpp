/**
 * @author - liyan30 @ 2015-12-31 16:11
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
#define repcase int t, Case = 1; for (scanf("%d", &t); t; --t)

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

struct hiker {
    int pos, tm;

    long long get_reach_tm(int reach_cnt) {
        return 360LL * reach_cnt * tm + (360LL - pos) * tm;
    }
};

int main() {
    freopen ("C.out", "w", stdout);
    repcase {
        int n;
        scanf("%d", &n);
        vector<hiker> hikers;
        rep (i, n) {
            int pos, cnt, tm;
            scanf("%d%d%d", &pos, &cnt, &tm);
            rep (j, cnt) {
                hikers.push_back({pos, tm + j});
            }
        }
        n = SZ(hikers);
        int ret = n;
        rep (i, n) {
            repf (reach_cnt, 0, n) {
                long long cur_tm = hikers[i].get_reach_tm(reach_cnt);
                // cur_tm actually +eps
                long long cnt = 0;
                rep (k, n) {
                    if (cur_tm < hikers[k].get_reach_tm(0)) {
                        cnt += 1;
                    } else if (cur_tm >= hikers[k].get_reach_tm(1)) {
                        cnt += (cur_tm - hikers[k].get_reach_tm(0)) / (360LL * hikers[k].tm);
                    }
                }
                if (cnt < ret) {
                    ret = cnt;
                }
                // NOTICE("%I64d -> %I64d", cur_tm, cnt);
            }
        }
        printf("Case #%d: %d\n", Case++, ret);
    }
    return 0;
}