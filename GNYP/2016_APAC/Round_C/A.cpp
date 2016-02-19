/**
 * @author - iSea_baidu @ 2016-02-18 14:04
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
#include <unordered_map>
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

int valid_rank, n_match, max_valid_score_cnt;
int scores[102];

int main() {
    repcase {
        scanf("%d", &valid_rank);
        rep (i, valid_rank) {
            scanf("%d", &scores[i]);
        }
        unordered_map<string, vector<int> > players;
        scanf("%d", &n_match);
        rep (i, n_match) {
            int weight;
            scanf("%d", &weight);
            rep (j, valid_rank) {
                char buf[12];
                scanf("%s", buf);
                players[string(buf)].push_back(weight * scores[j]);
            }
        }
        scanf("%d", &max_valid_score_cnt);
        vector<pair<int, string> > final_scores;
        for (auto player : players) {
            sort(player.second.begin(), player.second.end(), [](int x, int y) {
                return x > y;
            });
            int sum_score = 0;
            for (int idx = 0; idx < max_valid_score_cnt && idx < SZ(player.second); ++idx) {
                sum_score += player.second[idx];
            }
            final_scores.push_back({sum_score, player.first});
        }
        sort(final_scores.begin(), final_scores.end(), [](pair<int, string> x, pair<int, string> y) {
            return x.first == y.first? x.second < y.second : x.first > y.first;
        });
        int crank = 1;
        printf("Case #%d:\n", Case++);
        rep (i, SZ(final_scores)) {
            if (i != 0 && final_scores[i].first != final_scores[i - 1].first) {
                ++crank;
                to_max(crank, i + 1);
            }
            printf("%d: %s\n", crank, final_scores[i].second.c_str());
        }
    }
    return 0;
}