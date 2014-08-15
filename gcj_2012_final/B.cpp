// iSea, "not the fish"
// iSea @ 2014-08-15 13:39
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
#define out(x) cout << #x << ' ' << x << endl
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

vector<double> p;
int n, k;

void input() {
	scanf ("%d%d", &n, &k);
	p.clear();
	rep (i, n) {
		int a, b, ki;
		scanf ("%d/%d %d", &a, &b, &ki);
		double pro = 1.0 * a / b;
		rep (i, ki) {
			p.push_back(pro);
		}
	}
	sort (p.begin(), p.end());
	n = sz(p);
}

struct mat {
	double a[3][3];

	mat(double _di = 0.0) {
		rep (i, 3) rep (j, 3) {
			a[i][j] = i == j? _di : 0.0;
		}
	}

	void init(double pro) {
		a[0][0] = a[1][2] = pro;
		a[0][1] = a[1][1] = 1 - pro;
		a[2][2] = 1;
	}

	mat operator*(const mat& rhs) const {
		mat res;
		rep (i, 3) rep (j, 3) rep (k, 3) {
			res.a[i][j] += a[i][k] * rhs.a[k][j];
		}
		return res;
	}

	void print() const {
		rep (i, 3) rep (j, 3) {
			printf ("%lf%c", a[i][j], j == 2? '\n' : ' ');
		}
		puts ("----");
	}
};

const int MAXN = 1000000 + 10;

mat best[MAXN], m[MAXN];

void solve() {
	rep (i, n) {
		m[i].init(p[i]);
	}
	best[0] = mat(1.0);
	rep (i, k) {
		best[i + 1] = m[i] * best[i];
	}
	double ret = 1.0;
	mat temp(1.0);
	rep (i, k + 1) {
		mat cur = temp * best[k - i];
		ckmin (ret, cur.a[0][2]);
		temp = temp * m[n - 1 - i];
	}
	printf ("%.10lf\n", ret);
}

int main() {
	freopen ("../B.out", "w", stdout);

	repcase {
		fprintf(stderr, "solving case %d / %d...\n", Case, t + Case - 1);
		printf ("Case #%d: ", Case++);

		input();

		solve();
	}
	return 0;
}