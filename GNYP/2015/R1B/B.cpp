/**
 * @author - liyan30 @ 2015-12-31 11:29
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

int max_delete_score(int cells_4, int cells_3, int cells_2, int delete_cells) {
    int ret = 0;
    if (delete_cells > 0) {
        int delnum = min(delete_cells, cells_4);
        delete_cells -= delnum;
        ret += delnum * 4;
    }
    if (delete_cells > 0) {
        int delnum = min(delete_cells, cells_3);
        delete_cells -= delnum;
        ret += delnum * 3;
    }
    if (delete_cells > 0) {
        int delnum = min(delete_cells, cells_2);
        delete_cells -= delnum;
        ret += delnum * 2;
    }
    return ret;
}

int solve(int w, int h, int n) {
    int max_zero_cells = (w * h + 1) >> 1;
    if (n <= max_zero_cells) {
        return 0;
    }

    if (w > h) swap(w, h);
    int delete_cells = w * h - n;

    if (w == 1) {
        int tot_score = h - 1;
        return tot_score - delete_cells * 2;
    }

    int tot_score = (w - 2) * (h - 2) * 4 + (w - 2 + h - 2) * 2 * 3 + 4 * 2;
    tot_score >>= 1;
    if (w % 2 == 0 || h % 2 == 0) {
        int cells_4 = (w - 2) * (h - 2) / 2;
        int cells_3 = (w - 2 + h - 2);
        int cells_2 = 2;
        return tot_score - max_delete_score(cells_4, cells_3, cells_2, delete_cells);
    }

    // 2*3*3*2
    // *4*4*4*
    // 3*4*4*3
    // *4*4*4*
    // 2*3*3*2
    int cells_4 = ((w - 2) * (h - 2) + 1) / 2;
    int cells_3 = (w - 3 + h - 3);
    int cells_2 = 4;
    int score1 = max_delete_score(cells_4, cells_3, cells_2, delete_cells);

    // *3*3*3*
    // 3*4*4*3
    // *4*4*4*
    // 3*4*4*3
    // *3*3*3*
    cells_4 = ((w - 2) * (h - 2)) / 2;
    cells_3 = (w - 1 + h - 1);
    cells_2 = 0;
    int score2 = max_delete_score(cells_4, cells_3, cells_2, delete_cells);

    return tot_score - max(score1, score2);
}

int main() {
    freopen ("B.out", "w", stdout);
    repcase {
        int w, h, n;
        scanf("%d%d%d", &w, &h, &n);
        printf("Case #%d: %d\n", Case++, solve(w, h, n));
    }
    return 0;
}