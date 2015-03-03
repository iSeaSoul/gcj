/**
 * @author - liyan30 @ 2015-02-28 14:17
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
#define repcase int t, Case = 1; for (cin >> t; t; --t)

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

struct interval {
    int st, ed, type;

    bool operator<(const interval& rhs) const {
        return st < rhs.st;
    }
};

const int ENDTIME = 80000000;
const int MAXN = 6000 + 10;

int n1, n2, lunch_len;
vector<interval> intervals;

int dp[MAXN][MAXN >> 1];

bool can_begin(int id) {
    return lunch_len > intervals[id].st;
}

bool can_end(int id) {
    return intervals[id].ed + lunch_len > ENDTIME;
}

bool eariler_than_lunch(int idj, int idi) {
    return intervals[idi].ed + lunch_len > intervals[idj].st;
}

void update(int& x, int y) {
    if (x == -1 || x > y) {
        x = y;
    }
}

int solve() {
    if (lunch_len > ENDTIME) {
        return 0;
    }

    sort(intervals.begin(), intervals.end());

    int ret = -1;

    memset (dp, -1, sizeof(dp));
    for (int idx = n1 + n2 - 1; idx >= 0; --idx) {
        int xtype = intervals[idx].type;
        if (can_end(idx)) {
            if (xtype == 0) {
                dp[idx][1] = 0;
            } else {
                dp[idx][0] = 1;
            }
            if (can_begin(idx)) {
                update(ret, 1);
            }
            continue;
        }

        // find valid intervals which end latest
        int nextid[2] = {-1, -1};
        for (int j = idx + 1; j < n1 + n2 && eariler_than_lunch(j, idx); ++j) {
            int iend = intervals[j].ed;
            int itype = intervals[j].type;
            if (nextid[itype] == -1 || iend > intervals[nextid[itype]].ed) {
                nextid[itype] = j;
            }
        }

        rep (idtype, 2) {
            int idy = nextid[idtype];
            if (idy != -1) {
                for (int first_num = 0; first_num <= min(n1, n1 + n2 - idy); ++first_num) {
                    if (dp[idy][first_num] != -1) {
                        if (xtype == 0) {
                            update(dp[idx][first_num + 1], dp[idy][first_num]);
                        } else {
                            update(dp[idx][first_num], dp[idy][first_num] + 1);
                        }
                    }
                }
            }
        }

        if (can_begin(idx)) {
            for (int first_num = 0; first_num <= min(n1, n1 + n2 - idx); ++first_num) {
                if (dp[idx][first_num] != -1) {
                    update(ret, max(first_num, dp[idx][first_num]));
                }
            }
        }
    }

    return ret;
}

int main() {
    repcase {
        scanf ("%d%d%d", &n1, &n2, &lunch_len);
        intervals.clear();
        rep (i, n1) {
            int start_t, end_t;
            scanf ("%d%d", &start_t, &end_t);
            intervals.push_back(interval{start_t, end_t, 0});
        }
        rep (i, n2) {
            int start_t, end_t;
            scanf ("%d%d", &start_t, &end_t);
            intervals.push_back(interval{start_t, end_t, 1});
        }

        int ans = solve();
        if (ans == -1) {
            printf ("Case #%d: Lunchtime\n", Case++);
        } else {
            printf ("Case #%d: %d\n", Case++, ans);
        }
    }
    return 0;
}
