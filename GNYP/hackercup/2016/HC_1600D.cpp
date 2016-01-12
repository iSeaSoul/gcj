/**
 * @author - liyan30 @ 2016-01-10 23:34
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

int calc_lcp(const string& x, const string& y) {
    int id;
    for (id = 0; id < SZ(x) && id < SZ(y); ++id) {
        if (x[id] != y[id]) {
            break;
        }
    }
    return id;
}

int update(int& x, int y) {
    if (x == -1 || x > y) {
        x = y;
    }
}

const int maxn = 300 + 10;

int n, k;
string word[maxn];
int len[maxn], dp[maxn][maxn], lcp[maxn][maxn];

int main() {
    freopen ("text_editor.txt", "r", stdin);
    freopen ("out", "w", stdout);
    repcase {
        fprintf(stderr, "solve case %d\n", Case);
        cin >> n >> k;
        rep (i, n) {
            cin >> word[i];
        }
        sort(word, word + n);
        rep (i, n) {
            len[i] = SZ(word[i]);
        }
        rep (i, n) rep (j, i) {
            lcp[j][i] = calc_lcp(word[i], word[j]);
        }

        memset(dp, -1, sizeof(dp));
        rep (i, n) {
            rep (j, i) repf (z, 1, j + 1) {
                update(dp[i][z + 1], dp[j][z] + len[j] - 2 * lcp[j][i] + 1 + len[i]);
            }
            update(dp[i][1], len[i] + 1);
        }
        int ret = -1;
        repf (i, k - 1, n - 1) {
            update(ret, dp[i][k] + len[i]);
        }
        cout << "Case #" << Case++ << ": " << ret << endl;
    }
    return 0;
}