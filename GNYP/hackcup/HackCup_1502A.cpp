/*
 * Not the fish.
 * liyan30 @ 2015-02-15 13:47
 */

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

#define sz(x) ((int)((x).size()))
#define out(x) cout << #x << ' ' << x << endl;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (cin >> t; t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

const int MAXN = 100000 + 10;

int n, a[MAXN];

int main() {
    repcase {
        scanf ("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf ("%d", &a[i]);
        }
        int maxi = 0, mini = 0;
        int head = 1, tail = n - 1;
        bool can_sort = true;
        auto try_stack = [&](int x) {
            if (a[maxi] == a[x] - 1) {
                maxi = x;
                return true;
            }
            if (a[mini] == a[x] + 1) {
                mini = x;
                return true;
            }
            return false;
        };
        auto try_sort = [&]() {
            for (int i = 1; i < n; ++i) {
                if (try_stack(head)) {
                    ++head;
                } else if (try_stack(tail)) {
                    --tail;
                } else {
                    can_sort = false;
                    break;
                }
            }
        };
        try_sort();
        if (!can_sort) {
            maxi = n - 1, mini = n - 1;
            head = 0, tail = n - 2;
            can_sort = true;
            try_sort();
        }
        printf ("Case #%d: %s\n", Case++, can_sort? "yes" : "no");
    }
    return 0;
}