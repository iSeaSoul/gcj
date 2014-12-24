// Rain Dreamer MODEL
// iSea @ 2014-08-05 19:55
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

typedef pair<int, int> pii;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_len(unsigned long long x) { return x == 0? 0 : count_len(x >> 1) + 1; }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

void solve_n(unsigned long long n) {
	int len = count_len(n);
	unsigned long long p = 1, q = 1;
	rep (i, len - 1) {
		if ((n >> (len - 2 - i)) & 1) {
			p += q;
		} else {
			q += p;
		}
	}
	cout << p << ' ' << q << endl;
}

void solve_pq(unsigned long long p, unsigned long long q) {
	unsigned long long n = 0;
	int bit = 0;
	while (p != q) {
		if (p > q) {
			p -= q;
			n |= (1ull << bit);
		} else {
			q -= p;
		}
		bit++;
	}
	cout << (n | (1ull << bit)) << endl;
}

int main() {
	freopen ("B.out", "w", stdout);
	repcase {
		int optype;
		unsigned long long n, p, q;

		printf ("Case #%d: ", Case++);
		scanf ("%d", &optype);
		if (optype == 1) {
			cin >> n;
			solve_n(n);
		} else {
			cin >> p >> q;
			solve_pq(p, q);
		}
	}
	return 0;
}