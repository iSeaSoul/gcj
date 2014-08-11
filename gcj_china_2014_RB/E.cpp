// Rain Dreamer MODEL
// iSea @ 2014-08-11 13:57
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

bool is_comment() {
	char ch;
	if (cin.get(ch)) {
		if (ch == '*') {
			// char nch;
			// if (cin.get(nch)) {
			// 	if (nch == '/') {
			// 		cin.putback(nch);
			// 		cin.putback(ch);
			// 		return false;
			// 	}
			// } 
			return true;
		}
		cin.putback(ch);
	}
	return false;
}

bool is_comment_end() {
	char ch;
	if (cin.get(ch)) {
		if (ch == '/') {
			return true;
		}
		cin.putback(ch);
	}
	return false;
}

int main() {
	freopen ("../E.out", "w", stdout);

	printf ("Case #1:\n");
	int comment_lv = 0;
	char ch;
	while (cin.get(ch)) {
		if (comment_lv == 0) {
			if (ch == '/' && is_comment()) {
				comment_lv++;
			} else {
				putchar (ch);
			}
		} else if (ch == '*' && is_comment_end()) {
			comment_lv--;
		} else if (ch == '/' && is_comment()) {
			comment_lv++;
		}
	}
	return 0;
}