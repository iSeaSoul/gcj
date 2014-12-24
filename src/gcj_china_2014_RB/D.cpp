// Rain Dreamer MODEL
// iSea @ 2014-08-11 13:31
// Comment - 

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

// Self Template Code BGEIN

#define sz(x) ((int)((x).size()))
#define out(x) printf(#x" %d\n", x)
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (scanf ("%d", &t); t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

const int MAXN = 100 + 10;
const int di[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int n, m, sx, sy, ex, ey;
int maze[MAXN][MAXN], maxp_mind[MAXN][MAXN];

struct state {
	int x, y, s;

	bool operator<(const state& rhs) const {
		return s < rhs.s;
	}
};

bool is_valid(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != -1;
}

int solve() {
	memset (maxp_mind, -1, sizeof(maxp_mind));
	priority_queue<state> pq[2];
	pq[0].push(state{sx, sy, maze[sx][sy]});
	maxp_mind[sx][sy] = maze[sx][sy];

	int cur = 0;
	while (!pq[cur].empty()) {
		while (!pq[cur].empty()) {
			state c = pq[cur].top(); pq[cur].pop();
			if (c.x == ex && c.y == ey) {
				return c.s;
			}
			rep (d, 4) {
				int nx = c.x + di[d][0], ny = c.y + di[d][1];
				if (is_valid(nx, ny) && maxp_mind[nx][ny] == -1) {
					maxp_mind[nx][ny] = c.s + maze[nx][ny];
					pq[!cur].push(state{nx, ny, maxp_mind[nx][ny]});
				}
			}
		}
		cur = !cur;
	}
	return -1;
}

int main() {
	freopen ("../D.out", "w", stdout);

	repcase {
		scanf ("%d%d", &n, &m);
		scanf ("%d%d%d%d", &sx, &sy, &ex, &ey);
		rep (i, n) rep (j, m) {
			scanf ("%d", &maze[i][j]);
		}

		printf ("Case #%d: ", Case++);
		int res = solve();
		if (res == -1) {
			puts ("Mission Impossible.");
		} else {
			printf ("%d\n", res);
		}
	}
	return 0;
}