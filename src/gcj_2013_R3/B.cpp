// Rain Dreamer MODEL
// iSea @ 2014-08-11 22:26
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

struct point {
	double x, y;

	point(double _x = 0, double _y = 0): x(_x), y(_y) {
	}

	void input() {
		scanf ("%lf%lf", &x, &y);
	}
	void print() {
		printf ("%lf %lf\n", x, y);
	}

	bool operator<(const point& p) const {
		return sgn(x - p.x) == 0? sgn(y - p.y) < 0 : sgn(x - p.x) < 0;
	}
	bool operator==(const point& p) const {
		return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
	}
	point operator+(const point& p) const {
		return point(x + p.x, y + p.y);
	}
	point operator-(const point& p) const {
		return point(x - p.x, y - p.y);
	}
	point operator*(const double& d) const {
		return point(d * x, d * y);
	}
	double operator^(const point& p) const {
		return x * p.x + y * p.y;
	}
	double operator*(const point& p) const {
		return x * p.y - y * p.x;
	}
	double len() const {
		return sqrt(x * x + y * y);
	}
	double dis(const point& p) const {
		return (*this - p).len();
	}
};

const int max_n = 1000 + 10;

int dn, hd[max_n], un, hu[max_n];
int ch[max_n], chn;

void get_convex_hull(point* p, int n) {
	dn = un = 2;
	hd[0] = hu[0] = 0;
	hd[1] = hu[1] = 1;
	for (int i = 2; i < n; ++i) {
		// here we allow multi points on a line
		// if not allowed change it to <= 0
		for (; dn > 1 && sgn((p[hd[dn - 1]] - p[hd[dn - 2]]) * (p[i] - p[hd[dn - 1]])) < 0; --dn);
		for (; un > 1 && sgn((p[hu[un - 1]] - p[hu[un - 2]]) * (p[i] - p[hu[un - 1]])) > 0; --un);
		hd[dn++] = hu[un++] = i;
	}
	chn = 0;
	rep (i, dn) {
		ch[chn++] = hd[i];
	}
	repd (i, un - 2, 1) {
		ch[chn++] = hu[i];
	}
}

double get_area(vector<int> pid, point* p, int n) {
	double ret = 0.0;
	rep (i, n) {
		ret += p[pid[i]] * p[pid[(i + 1) % n]];
	}
	return abs(ret) / 2;
}

bool vis[max_n];
point p[max_n], cp[max_n];
int n;

void print(vector<int> vec) {
	repeach (it, vec) {
		rep (i, n) {
			if (p[*it] == cp[i]) {
				printf (" %d", i);
				break ;
			}
		}
	}
	puts ("");
}

int main() {
	freopen ("../B.out", "w", stdout);

	repcase {
		scanf ("%d", &n);
		rep (i, n) {
			p[i].input();
			cp[i] = p[i];
		}

		sort (p, p + n);
		get_convex_hull(p, n);
		vector<int> ups, dns;

		memset (vis, 0, sizeof(vis));
		rep (i, un) {
			ups.push_back(hu[i]);
			vis[hu[i]] = true;
		}
		repd (i, n - 1, 0) {
			if (!vis[i]) {
				ups.push_back(i);
			}
		}

		memset (vis, 0, sizeof(vis));
		rep (i, dn) {
			dns.push_back(hd[i]);
			vis[hd[i]] = true;
		}
		repd (i, n - 1, 0) {
			if (!vis[i]) {
				dns.push_back(i);
			}
		}

		printf ("Case #%d:", Case++);
		if (get_area(ups, p, n) > get_area(dns, p, n)) {
			print (ups);
		} else {
			print (dns);
		}
	}
	return 0;
}