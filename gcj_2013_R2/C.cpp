// Rain Dreamer MODEL
// iSea @ 2014-08-12 02:47
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

const int MAXN = 2000 + 10;

set<int> smaller[MAXN];
int n, a[MAXN], b[MAXN], ans[MAXN];

int main() {
	freopen ("../C.out", "w", stdout);

	repcase {
		fprintf(stderr, "solving case %d / %d...\n", Case, t + Case - 1);

		scanf ("%d", &n);
		rep (i, n) {
			smaller[i].clear();
			ans[i] = 0;
		}
		rep (i, n) {
			scanf ("%d", &a[i]);
		}
		rep (i, n) {
			for (int j = i - 1; j >= 0; --j) {
				if (a[i] == a[j]) {
					smaller[j].insert (i);
					break;
				}
			}
			for (int j = i - 1; j >= 0; --j) {
				if (a[i] == a[j] + 1) {
					smaller[i].insert (j);
					break;
				}
			}
		}
		rep (i, n) {
			scanf ("%d", &b[i]);
		}
		rep (i, n) {
			for (int j = i + 1; j < n; ++j) {
				if (b[i] == b[j]) {
					smaller[j].insert (i);
					break;
				}
			}
			for (int j = i + 1; j < n; ++j) {
				if (b[i] == b[j] + 1) {
					smaller[i].insert (j);
					break;
				}
			}
		}

		repf (id, 1, n) {
			rep (i, n) if (!ans[i] && smaller[i].empty()) {
				ans[i] = id;
				rep (j, n) smaller[j].erase(i);
				break;
			}
		}
		printf ("Case #%d: ", Case++);
		rep (i, n) {
			printf ("%d%c", ans[i], i == n - 1? '\n' : ' ');
		}
	}
	return 0;
}