// Rain Dreamer MODEL
// iSea @ 2014-08-11 16:15
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

struct edge {
	int u, v, max, min;

	void input() {
		scanf ("%d%d%d%d", &u, &v, &min, &max);
		max <<= 1, min <<= 1;
	}
};

struct adj_node {
	int id, min, max, eid;
};

const int MAXN = 1000 + 10;
const int MAXM = 2000 + 10;
const int inf = (-1u) >> 1;

vector<adj_node> g[MAXN];
edge e[MAXM];
int good[MAXM], dis_f[MAXN], dis_s[MAXN];
bool vis_f[MAXN], vis_s[MAXN];
int n, m, p, path[MAXN];

bool can_prefix(int pid) {
	memset (good, 0, sizeof(good));
	repf (i, 1, n) {
		dis_f[i] = dis_s[i] = inf;
		vis_f[i] = vis_s[i] = false;
	}
	int sum_path = 0;
	repf (i, 0, pid) {
		good[path[i]] = 1;
		sum_path += e[path[i]].min;
	}
	// the faster has given prefix
	dis_f[e[path[pid]].v] = sum_path;
	// the slower begins later
	dis_s[1] = 1;

	rep (dij_tms, 2 * n) {
		int mind = inf, mini, min_type;
		repf (i, 1, n) {
			if (!vis_s[i] && dis_s[i] < mind) {
				mind = dis_s[i];
				mini = i; min_type = 0;
			}
			if (!vis_f[i] && dis_f[i] < mind) {
				mind = dis_f[i];
				mini = i; min_type = 1;
			}
		}
		if (mind == inf) {
			return false;
		}
		if (mini == 2) {
			// if reached goal, the faster one should be eariler
			return min_type == 1;
		}
		if (min_type == 1) {
			// the slower will use the minimal length if the slower hasn't used
			// otherwise use the maximal
			repeach (it, g[mini]) {
				int len;
				if (good[it->eid] == -1) {
					len = it->max;
				} else {
					len = it->min;
					good[it->eid] = 1;
				}
				if (dis_f[it->id] > dis_f[mini] + len) {
					dis_f[it->id] = dis_f[mini] + len;
				}
			}
			vis_f[mini] = true;
		} else {
			// the slower will use the maximal length if the faster hasn't used
			// otherwise use the minimal
			repeach (it, g[mini]) {
				int len;
				if (good[it->eid] == 1) {
					len = it->min;
				} else {
					len = it->max;
					good[it->eid] = -1;
				}
				if (dis_s[it->id] > dis_s[mini] + len) {
					dis_s[it->id] = dis_s[mini] + len;
				}
			}
			vis_s[mini] = true;
		}
	}
	return false;
}

int solve() {
	rep (i, p) {
		if (!can_prefix(i)) {
			return path[i];
		}
	}
	return -1;
}

int main() {
	freopen ("../C.out", "w", stdout);

	repcase {
		scanf ("%d%d%d", &n, &m, &p);
		repf (i, 1, n) {
			g[i].clear();
		}
		repf (i, 1, m) {
			e[i].input();
			g[e[i].u].push_back(adj_node{e[i].v, e[i].min, e[i].max, i});
		}
		rep (i, p) {
			scanf ("%d", &path[i]);
		}

		int res = solve();
		if (res == -1) {
			printf ("Case #%d: Looks Good To Me\n", Case++);
		} else {
			printf ("Case #%d: %d\n", Case++, res);
		}
	}
	return 0;
}