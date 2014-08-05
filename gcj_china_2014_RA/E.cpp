// Rain Dreamer MODEL
// iSea @ 2014-08-05 22:05
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

std::map<string, int> colmp;
int colID;

void clear_col() {
	colmp.clear();
	colID = 0;
}

int get_id(const string& s) {
	if (colmp.find(s) == colmp.end()) {
		return colmp[s] = colID++;
	}
	return colmp[s];
}

const int MAXR = 80000 + 10;
const int MAXN = 36 * 36 + 10;

int id[MAXR], n, m, q, dis[MAXN];
vector<pii> g[MAXN];

struct node {
	int x, d;

	bool operator<(const node& rhs) const {
		return d > rhs.d;
	}
};

int get_dis(int x, int y) {
	memset (dis, -1, sizeof(dis));
	priority_queue<node> pq;
	pq.push(node{x, 0});
	dis[x] = 0;

	while (!pq.empty()) {
		node cur = pq.top(); pq.pop();
		if (cur.x == y) {
			return cur.d;
		}
		if (cur.d > dis[cur.x]) {
			continue ;
		}
		repeach (it, g[cur.x]) {
			int nx = it->first, nd = cur.d + it->second;
			if (dis[nx] == -1 || dis[nx] > nd) {
				dis[nx] = nd;
				pq.push(node{nx, nd});
			}
		}
	}
	return -1;
}

int main() {
	freopen ("E.out", "w", stdout);
	repcase {
		scanf ("%d", &n);
		clear_col();
		rep (i, n) {
			char colbuf[3];
			scanf ("%s", colbuf);
			id[i] = get_id(string(colbuf));
			g[id[i]].clear();
		}
		scanf ("%d", &m);
		rep (i, m) {
			int u, v, w;
			scanf ("%d%d%d", &u, &v, &w);
			g[id[--u]].push_back(pii(id[--v], w));
		}
		printf ("Case #%d:\n", Case++);
		scanf ("%d", &q);
		rep (i, q) {
			int x, y;
			scanf ("%d%d", &x, &y);
			printf ("%d\n", get_dis(id[--x], id[--y]));
		}
	}
	return 0;
}