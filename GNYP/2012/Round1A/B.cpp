/**
 * @author - iSea_baidu @ 2016-03-21 19:04
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

struct event {
    int threshold_1, threshold_2;
    int state; // 0 / 1 / 2
};

vector<event> events;
int n;

int main() {
    repcase {
        scanf("%d", &n);
        events.clear();
        rep (i, n) {
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            events.push_back({t1, t2, 0});
        }
        sort(events.begin(), events.end(), [](event x, event y) -> bool {
            return x.threshold_2 < y.threshold_2;
        });
        int score = 0, res = 0;
        int event_alldone_sliding_idx = 0;
        while (score < 2 * n) {
            if (events[event_alldone_sliding_idx].threshold_2 <= score) {
                score += 2 - events[event_alldone_sliding_idx++].state;
            } else {
                // greedy
                // find event satisfy state=0, threshold_1<=score and has maximal threshold_2
                int greedily_idx = -1;
                for (int idx = n - 1; idx >= event_alldone_sliding_idx; --idx) {
                    if (events[idx].state == 0 && events[idx].threshold_1 <= score) {
                        greedily_idx = idx;
                        break;
                    }
                }
                if (greedily_idx == -1) {
                    // failed
                    break;
                }
                score += 1;
                events[greedily_idx].state = 1;
            }
            ++res; // round ++
        }
        if (score < 2 * n) {
            printf("Case #%d: Too Bad\n", Case++);
        } else {
            printf("Case #%d: %d\n", Case++, res);
        }
    }
    return 0;
}