/*
 * Not the fish.
 * iSea @ 2015-01-18 09:05
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

const int MAXN = 1000000 + 10;

struct Trie {
    struct node {
        int cnt;
        int next[26];

        node() {
            cnt = 0;
            memset (next, -1, sizeof(next));
        }
    };

    vector<node> nodes;

    void clear() {
        nodes.clear();
        nodes.push_back(node());
    }
    void insert(char *word) {
        int idx = 0;
        for (int i = 0; word[i]; ++i) {
            int ch = word[i] - 'a';
            if (nodes[idx].next[ch] == -1) {
                nodes[idx].next[ch] = sz(nodes);
                nodes.push_back(node());
            }
            idx = nodes[idx].next[ch];
            nodes[idx].cnt += 1;
        }
    }
    int count(char *word) {
        int ret = 0;
        int idx = 0;
        for (int i = 0; word[i]; ++i) {
            int ch = word[i] - 'a';
            idx = nodes[idx].next[ch];
            ret += 1;
            if (nodes[idx].cnt == 1) {
                break;
            }
        }
        return ret;
    }
};

char buf[MAXN];
Trie tree;

int main() {
    freopen ("B.out", "w", stdout);

    repcase {
        int n;
        scanf ("%d", &n);
        tree.clear();
        int ret = 0;
        rep (i, n) {
            scanf ("%s", buf);
            tree.insert(buf);
            ret += tree.count(buf);
        }
        printf ("Case #%d: %d\n", Case++, ret);
    }

    return 0;
}