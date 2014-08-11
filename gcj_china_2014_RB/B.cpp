// Rain Dreamer MODEL
// iSea @ 2014-08-05 23:42
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

const int MAXN = 1000000 + 10;

pii vx[MAXN], vy[MAXN], p[MAXN];
long long ans[MAXN];
int n, pid;

void add_p(int x, int y) {
	ans[pid] = 0;
	vx[pid] = pii(x, pid);
	vy[pid] = pii(y, pid);
	p[pid++] = pii(x, y);
}

void solve_d(pii *v) {
	sort (v, v + pid);
	long long sumv = 0LL;
	rep (i, pid) {
		sumv += v[i].first;
	}
	long long cursum = 0LL;
	rep (i, pid) {
		cursum += v[i].first;
		ans[v[i].second] += (sumv - cursum) - (long long)v[i].first * (pid - 1 - i);
		ans[v[i].second] += (long long)v[i].first * (i + 1) - cursum;
	}
}

int main() {
	freopen ("B.out", "w", stdout);
	repcase {
		scanf ("%d", &n);
		pid = 0;
		rep (i, n) {
			int x1, y1, x2, y2;
			scanf ("%d%d%d%d", &x1, &y1, &x2, &y2);
			repf (i, x1, x2) repf (j, y1, y2) {
				add_p(i, j);
			}
		}
		solve_d(vx); solve_d(vy);
		int ansi = 0;
		repf (i, 1, pid - 1) {
			if (ans[i] < ans[ansi]) {
				ansi = i;
			} else if (ans[i] == ans[ansi] && p[i] < p[ansi]) {
				ansi = i;
			}
		}
		printf ("Case #%d: %d %d %I64d\n", Case++, p[ansi].first, p[ansi].second, ans[ansi]);
	}
	return 0;
}