// Rain Dreamer MODEL
// iSea @ 2014-08-04 11:10
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

char buf[102], format[102];

void init() {
	scanf ("%s%s", buf, format);
}

char *nums[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *scs[9] = {"double", "triple", "quadruple", "quintuple", "sextuple", "septuple",
	"octuple", "nonuple", "decuple"};

void read_term(char num, int len) {
	if (len > 10 || len == 1) {
		rep (i, len) printf (" %s", nums[num - '0']);
	} else {
		printf (" %s %s", scs[len - 2], nums[num - '0']);
	}
}

void read(int l, int r) {
	repf (i, l, r - 1) {
		char cur = buf[i];
		int len = 1;
		while (i + 1 < r && buf[i + 1] == cur) {
			i++; len++;
		}
		read_term(cur, len);
	}
}

void solve() {
	int idx = 0, len;
	for (int i = 0; format[i]; ) {
		while (format[i] == '-') ++i;
		len = format[i++] - '0';
		while (format[i] >= '0' && format[i] <= '9') {
			len = len * 10 + format[i++] - '0';
		}
		read(idx, idx + len);
		idx += len;
	}
	puts ("");
}

int main() {
	freopen ("A.out", "w", stdout);
	repcase {
		printf ("Case #%d:", Case++);
		init();
		solve();
	}
	return 0;
}
