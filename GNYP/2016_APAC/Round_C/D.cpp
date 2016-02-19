/**
 * @author - iSea_baidu @ 2016-02-19 16:33
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

const int maxn = 3000 + 10;

int A[maxn], B[maxn], num[maxn][maxn];
int nAll, nWin, C, X;

int stack_row[maxn][maxn], sr_head[maxn], sr_tail[maxn];
int stack_col[maxn], sc_head, sc_tail;

int get_stack_row_head(int rowid) {
    return num[rowid][stack_row[rowid][sr_head[rowid]]];
}

long long calc_current_row_sliding_windows() {
    sc_head = 0;
    sc_tail = -1;
    rep (i, nWin) {
        while (sc_tail >= sc_head && get_stack_row_head(stack_col[sc_tail]) <= get_stack_row_head(i)) {
            --sc_tail;
        }
        stack_col[++sc_tail] = i;
    }
    long long ret = get_stack_row_head(stack_col[sc_head]);
    repf (i, nWin, nAll - 1) {
        int left_lim = i - nWin;
        while (sc_tail >= sc_head && stack_col[sc_head] <= left_lim) {
            ++sc_head;
        }
        while (sc_tail >= sc_head && get_stack_row_head(stack_col[sc_tail]) <= get_stack_row_head(i)) {
            --sc_tail;
        }
        stack_col[++sc_tail] = i;
        ret += get_stack_row_head(stack_col[sc_head]);
    }
    return ret;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d%d%d", &nAll, &nWin, &C, &X);
        rep (i, nAll) {
            scanf("%d", &A[i]);
        }
        rep (i, nAll) {
            scanf("%d", &B[i]);
        }
        rep (i, nAll) rep (j, nAll) {
            num[i][j] = ((i + 1LL) * A[i] + (j + 1LL) * B[j] + C) % X;
        }
        memset(sr_head, 0, sizeof(sr_head));
        memset(sr_tail, -1, sizeof(sr_tail));
        rep (i, nAll) {
            rep (j, nWin) {
                while (sr_tail[i] >= sr_head[i] && num[i][stack_row[i][sr_tail[i]]] <= num[i][j]) {
                    --sr_tail[i];
                }
                stack_row[i][++sr_tail[i]] = j;
            }
        }
        long long ret = calc_current_row_sliding_windows();
        repf (j, nWin, nAll - 1) {
            rep (i, nAll) {
                int left_lim = j - nWin;
                while (sr_tail[i] >= sr_head[i] && stack_row[i][sr_head[i]] <= left_lim) {
                    ++sr_head[i];
                }
                while (sr_tail[i] >= sr_head[i] && num[i][stack_row[i][sr_tail[i]]] <= num[i][j]) {
                    --sr_tail[i];
                }
                stack_row[i][++sr_tail[i]] = j;
            }
            ret += calc_current_row_sliding_windows();
        }
        printf("Case #%d: %lld\n", Case++, ret);
    }
    return 0;
}