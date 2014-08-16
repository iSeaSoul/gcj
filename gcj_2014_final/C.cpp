// GCJ
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

const int MAXN = 10000 + 10;

vector<int> g[MAXN];
int c[MAXN], n;

map<pii, int> hash;
map<pii, bool> canc_mp;

int get_col(char ch) {
	return ch - 'A';
}

void input() {
	scanf ("%d", &n);
	rep (i, n) {
		char buf[2];
		scanf ("%s", buf);
		c[i] = get_col(buf[0]);
	}
	rep (i, n) {
		g[i].clear();
	}
	rep (i, n - 1) {
		int u, v;
		scanf ("%d%d", &u, &v);
		g[--u].push_back(--v);
		g[v].push_back(u);
	}
}

const int BEGIN = 201408;
const int MUVAL = 999729;
const int MOD = 19900810;

int get_val(int x) {
	return (BEGIN + x) % MOD;
}

int get_hash(int x, int f) {
	pii t = pii(x, f);
	if (hash.find(t) != hash.end()) {
		return hash[t];
	}

	vector<int> sons;
	repeach (it, g[x]) {
		if (*it != f) {
			sons.push_back(get_hash(*it, x));
		}
	}

	sort (sons.begin(), sons.end());

	int res = get_val(c[x]);
	repeach (it, sons) {
		res = ((res * MUVAL) ^ (*it)) % MOD;
	}
	return hash[t] = res;
}

bool can_centre(int x, int f) {
	pii c = pii(x, f);
	if (canc_mp.find(c) != canc_mp.end()) {
		return canc_mp[c];
	}

	vector<pii> sons;
	repeach (it, g[x]) {
		if (*it != f) {
			sons.push_back(pii(get_hash(*it, x), *it));
		}
	}
	sort (sons.begin(), sons.end());
	bool ret = true;
	if (sz(sons) % 2 == 0) {
		for (int i = 0; i < sz(sons); i += 2) {
			if (sons[i].first != sons[i + 1].first) {
				ret = false;
				break;
			}
		}
	} else {
		int id;
		for (id = 0; id < sz(sons); id += 2) {
			if (sons[id].first != sons[id + 1].first) {
				break;
			}
		}
		int single_id = id;
		for (id++; id < sz(sons); id += 2) {
			if (sons[id].first != sons[id + 1].first) {
				ret = false;
				break;
			}
		}
		if (ret) {
			ret = can_centre(sons[single_id].second, x);
		}
	}
	return canc_mp[c] = ret;
}

void solve() {
	hash.clear();
	canc_mp.clear();

	rep (i, n) {
		repeach (it, g[i]) {
			if (get_hash(i, *it) == get_hash(*it, i)) {
				puts ("SYMMETRIC");
				return ;
			}
		}
	}
	rep (i, n) {
		if (can_centre (i, -1)) {
			puts ("SYMMETRIC");
			return ;
		}
	}
	puts ("NOT SYMMETRIC");
}

int main() {
	freopen ("C2.out", "w", stdout);

	repcase {
		fprintf(stderr, "solving case %d / %d...\n", Case, t + Case - 1);
		printf ("Case #%d: ", Case++);

		input();

		solve();
	}
	return 0;
}
