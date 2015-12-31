/**
 * @author - liyan30 @ 2015-12-30 14:52
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

namespace single_str_match {

/**
 * @usage : calculate the matching position
 * @meaning : next[cur_len][next_ch]
 **/

int get_id(char ch) {
    return ch - 'A';
}

void calc_nxt(char *str, int (*nxt)[26]) {
    int len = strlen(str);
    int fail = 0;
    nxt[0][get_id(str[0])] = 1;
    repf (i, 1, len - 1) {
        int cur = get_id(str[i]);
        rep (j, 26) {
            if (j == cur) {
                nxt[i][j] = i + 1;
            } else {
                nxt[i][j] = nxt[fail][j];
            }
        }
        fail = nxt[fail][cur];
    }
    rep (i, 26) {
        nxt[len][i] = nxt[fail][i];
    }
}

}

const int maxn = 100 + 10;

int len_mother, len_target, len_tot;
char mother[maxn], target[maxn];
int nxt[maxn][26];
double dp[maxn][maxn];

bool check_letters() {
    // check if all letters are contained in mother keyboard
    unordered_set<char> all_letters;
    rep (i, len_mother) {
        all_letters.insert(mother[i]);
    }
    rep (i, len_target) {
        if (all_letters.find(target[i]) == all_letters.end()) {
            return false;
        }
    }
    return true;
}

double calc_max() {
    if (!check_letters()) {
        return 0;
    }
    if (len_target > len_tot) {
        return 0;
    }
    // calculate overlap length
    int overlap_len = 0;
    for (int olen = len_target - 1; olen >= 1; --olen) {
        bool failed = false;
        for (int i = 0; i < olen; ++i) {
            if (target[i] != target[len_target - olen + i]) {
                failed = true;
                break;
            }
        }
        if (!failed) {
            overlap_len = olen;
            break;
        }
    }
    return (len_tot - len_target) / (len_target - overlap_len) + 1;
}

double calc_exp() {
    single_str_match::calc_nxt(target, nxt);

    // calculate probability of each letter
    double pro[26] = {0};
    rep (i, len_mother) {
        pro[single_str_match::get_id(mother[i])]++;
    }
    rep (i, 26) {
        pro[i] /= len_mother;
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1.0;
    double ret = 0;
    repf (i, 0, len_tot) {
        repf (j, 0, len_target) {
            // printf("go [%d][%d] = %lf\n", i, j, dp[i][j]);
            if (j == len_target) {
                ret += dp[i][j];
            }
            rep (k, 26) {
                dp[i + 1][nxt[j][k]] += pro[k] * dp[i][j];
            }
        }
    }
    return ret;
}

double solve() {
    int ret = calc_max();
    if (ret == 0) {
        return 0;
    }
    return ret - calc_exp();
}

int main() {
    freopen ("B.out", "w", stdout);
    repcase {
        scanf("%d%d%d", &len_mother, &len_target, &len_tot);
        scanf("%s%s", mother, target);

        printf("Case #%d: %.8lf\n", Case++, solve());
    }
    return 0;
}