// Rain Dreamer MODEL
// iSea @ 2014-08-11 17:52
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

const int MAXN = 200 + 10;

double com[MAXN][MAXN];

void prep() {
	rep (i, MAXN) {
		com[i][0] = com[i][i] = 1.0;
		repf (j, 1, i - 1) {
			com[i][j] = com[i - 1][j] + com[i - 1][j - 1];
		}
	}
}

double pro[MAXN][MAXN], em[MAXN][MAXN];
bool flag[MAXN][MAXN];
char s[MAXN];
int len, empty[MAXN][MAXN];

int get_len(int l, int r) {
	return r >= l? r - l + 1 : len - l + r + 1;
}

void calc(int l, int r) {
	if (flag[l][r]) return ;
	flag[l][r] = true;

	empty[l][r] = pro[l][r] = em[l][r] = 0;

	// empty spots [l, r)
	for (int i = l; i != r; i = (i + 1) % len) {
		empty[l][r] += (s[i] == '.');
	}
	if (empty[l][r] == 0) {
		pro[l][r] = 1.0;
		return ;
	}

	for (int i = l; i != r; i = (i + 1) % len) {
		if (s[i] == '.') {
			// fill i-th spot, break [l, r(empty)] to [l, i(empty)] & [i + 1, r(empty)]
			int newr = i, newl = (i + 1) % len;
			calc(l, newr); calc(newl, r);

			int len1 = empty[l][newr], len2 = empty[newl][r];
			double pro_c = com[len1 + len2][len1];
			pro_c *= pow(1.0 * get_len(l, newr) / get_len(l, r), len1 + 1);
			pro_c *= pow(1.0 * get_len(newl, r) / get_len(l, r), len2);
			pro_c *= pro[l][newr] * pro[newl][r];
			pro[l][r] += pro_c;
			em[l][r] += pro_c * (em[l][newr] + em[newl][r] + len - (get_len(l, newr) - 1) / 2.0);
		}
	}
	em[l][r] /= pro[l][r];
}

int main() {
	freopen ("../D.out", "w", stdout);

	prep();

	repcase {
		fprintf(stderr, "solving case %d...\n", Case);

		scanf ("%s", s);
		len = strlen(s);

		memset (flag, 0, sizeof(flag));
		double ans = 0;
		rep (i, len) {
			if (s[i] == '.') {
				calc ((i + 1) % len, i);
				ans += pro[(i + 1) % len][i] * (em[(i + 1) % len][i] + (len + 1) / 2.0);
			}
		}
		printf ("Case #%d: %.10lf\n", Case++, ans);
	}
	return 0;
}