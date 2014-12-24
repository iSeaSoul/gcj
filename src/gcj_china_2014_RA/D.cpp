// Rain Dreamer MODEL
// iSea @ 2014-08-05 21:20
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
const int MAXD = 10000;

int n, sx, sy, ex, ey;
char maze[MAXN][MAXN];

const int di[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const char str_di[5] = "ESWN";

inline int nextd(int d) { return (d + 1) & 3; }
inline int prevd(int d) { return (d + 3) & 3; }

bool is_valid(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == '.';
}

bool can_move(int x, int y, int d) {
	return is_valid(x + di[d][0], y + di[d][1]);
}

/*
 * only one choice can make
 * left wall ends: try turn left
 * else: move straight until blocked
 * if blocked: find next valid direction
 */
string solve() {
	string ans = "";
	int cx = sx, cy = sy, cd = 0;
	// find beginning dir
	if (cx == 0) {
		cd = (cy == 0? 0 : 1);
	} else {
		cd = (cy == 0? 3 : 2);
	}
	rep (step, MAXD) {
		// check left exist
		cd = prevd(cd);
		int begin_cd = cd;
		while (!can_move(cx, cy, cd)) {
			cd = nextd(cd);
			if (cd == begin_cd) {
				return "";
			}
		}
		cx += di[cd][0], cy += di[cd][1];
		ans += str_di[cd];
		if (cx == ex && cy == ey) {
			return ans;
		}
	}
	return "";
}

int main() {
	freopen ("D.out", "w", stdout);
	repcase {
		scanf ("%d", &n);
		rep (i, n) scanf ("%s", maze[i]);
		scanf ("%d%d%d%d", &sx, &sy, &ex, &ey);
		--sx, --sy, --ex, --ey;

		printf ("Case #%d: ", Case++);
		string ans = solve();
		if (sz(ans) == 0) {
			puts ("Edison ran out of energy.");
		} else {
			printf ("%d\n", sz(ans));
			puts(ans.c_str());
		}
	}
	return 0;
}