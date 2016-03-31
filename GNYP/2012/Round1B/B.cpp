/**
 * @author - iSea_baidu @ 2016-03-25 17:27
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
const int dis[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
const double inf = 1e20;

const int lim_move = 50;
const int lim_kyayk = 20;
const double time_kyayk = 1;
const double time_drag_kyayk = 10;
const double water_dropping_speed = 10;

int n, m, init_wlevel;
int h_ceiling[maxn][maxn], h_floor[maxn][maxn];
bool vis[maxn][maxn];
double earilest_tm[maxn][maxn];

bool is_inside_map(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs_move_before_tide_dropping(int x, int y) {
    vis[x][y] = true;
    earilest_tm[x][y] = 0;
    rep (dir, 4) {
        int nx = x + dis[dir][0];
        int ny = y + dis[dir][1];
        if (is_inside_map(nx, ny) && !vis[nx][ny]) {
            int cur_floor = max(init_wlevel, max(h_floor[x][y], h_floor[nx][ny]));
            int cur_ceiling = min(h_ceiling[x][y], h_ceiling[nx][ny]);
            if (cur_ceiling - cur_floor >= lim_move) {
                dfs_move_before_tide_dropping(nx, ny);
            }
        }
    }
}

void move_before_tide_dropping() {
    dfs_move_before_tide_dropping(0, 0);
}

struct node {
    int x, y;
    double earilest_tm;
};

double solve() {
    rep (i, n) rep (j, m) {
        vis[i][j] = false;
        earilest_tm[i][j] = inf;
    }
    move_before_tide_dropping();
    if (vis[n - 1][m - 1]) {
        // can move to exit before tide dropping
        return 0;
    }

    auto comp_func = [](node l, node r) {
        return l.earilest_tm > r.earilest_tm;
    };
    priority_queue<node, vector<node>, decltype(comp_func)> pq(comp_func);
    rep (i, n) rep (j, m) {
        if (vis[i][j]) {
            pq.push({i, j, 0});
        }
    }
    memset(vis, 0, sizeof(vis));
    while (!pq.empty()) {
        node cur_node = pq.top(); pq.pop();
        if (cur_node.x == n - 1 && cur_node.y == m - 1) {
            return cur_node.earilest_tm;
        }
        if (vis[cur_node.x][cur_node.y]) {
            continue;
        }
        vis[cur_node.x][cur_node.y] = true;

        rep (dir, 4) {
            int nx = cur_node.x + dis[dir][0];
            int ny = cur_node.y + dis[dir][1];
            if (is_inside_map(nx, ny) && !vis[nx][ny]) {
                int cur_floor = max(h_floor[cur_node.x][cur_node.y], h_floor[nx][ny]);
                int cur_ceiling = min(h_ceiling[cur_node.x][cur_node.y], h_ceiling[nx][ny]);
                double cur_wlevel = init_wlevel - cur_node.earilest_tm * water_dropping_speed;

                if (cur_ceiling - cur_floor < lim_move) {
                    // impossible to get there
                    continue;
                }
                double need_time = 0;
                if (cur_ceiling - cur_wlevel < lim_move) {
                    // wait till u can move
                    need_time = (lim_move - (cur_ceiling - cur_wlevel)) / water_dropping_speed;
                }
                cur_wlevel -= need_time * water_dropping_speed;
                if (cur_wlevel - h_floor[cur_node.x][cur_node.y] >= lim_kyayk) {
                    need_time += time_kyayk;
                } else {
                    need_time += time_drag_kyayk;
                }
                if (cur_node.earilest_tm + need_time < earilest_tm[nx][ny]) {
                    pq.push({nx, ny, cur_node.earilest_tm + need_time});
                    earilest_tm[nx][ny] = cur_node.earilest_tm + need_time;
                }
                
            }
        }
    }
    // failed
    return -1;
}

int main() {
    repcase {
        NOTICE("solving case %d...", Case);
        scanf("%d%d%d", &init_wlevel, &n, &m);
        rep (i, n) rep (j, m) {
            scanf("%d", &h_ceiling[i][j]);
        }
        rep (i, n) rep (j, m) {
            scanf("%d", &h_floor[i][j]);
        }
        printf("Case #%d: %.10lf\n", Case++, solve());
    }
    return 0;
}