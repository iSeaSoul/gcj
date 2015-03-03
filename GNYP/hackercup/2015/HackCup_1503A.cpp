/**
 * @author - liyan30 @ 2015-02-28 11:24
 * @brief - From sky to the sea.
 **/

#include <bits/stdc++.h>

using namespace std;

// SELF TEMPLATE CODE BGEIN

#define LOG(level, fmt, arg...) \
    printf("[" #level "] [Line:%d] " fmt"\n", __LINE__, ##arg);

#define NOTICE(fmt, arg...) LOG(NOTICE, fmt, ##arg)
#define FATAL(fmt, arg...) LOG(FATAL, fmt, ##arg)

#define DEBUG(x) do { \
    stringstream ss; \
    ss << #x << ": " << x; \
    NOTICE("%s", ss.str().c_str()) \
} while (0)

#define SZ(x) ((int)((x).size()))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repcase int t, Case = 1; for (cin >> t; t; --t)

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }

template<class T> inline void to_min(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void to_max(T &a, const T b) { if (b > a) a = b; }

// SELF TEMPLATE CODE END

template <class T>
struct point {
    T x, y;

    point<T>(T _x = T(0), T _y = T(0)): x(_x), y(_y) {
    }

    point<T> operator-(const point<T>& p) const {
        return point<T>(x - p.x, y - p.y);
    }

    T operator*(const point<T>& p) const {
        return x * p.y - y * p.x;
    }

    double length() const {
        return sqrt(1.0 * x * x + 1.0 * y * y);
    }

    point<T> extend(const point<T>& dir, double dis) const {
        double len = dir.length();
        return point<T>(x + dir.x * dis / len, y + dir.y * dis / len);
    }

    void input() {
        cin >> x >> y;
    }
};

typedef point<double> pt;

template <class T>
ostream& operator<<(ostream& os, const point<T>& p) {
    return os << p.x << ' ' << p.y;
}

const int MAXN = 3000 + 10;

pt my_pos;
pt p[MAXN];
int n_points, max_exd;

bool is_on_segment(const pt& check_pt, const pt& p1, const pt& p2) {
    // check if cpt on [p1, p2] segment
    return sgn((check_pt - p1) * (check_pt - p2)) == 0 &&
            sgn((check_pt.x - p1.x) * (check_pt.x - p2.x)) <= 0 &&
            sgn((check_pt.y - p1.y) * (check_pt.y - p2.y)) <= 0 ;
}

int solve() {
    int max_score = 0;
    rep (first_d, n_points) {
        // first throw direction
        pt dir = p[first_d] - my_pos;
        if (sgn(dir.x) == 0 && sgn(dir.y) == 0) {
            continue;
        }

        int first_score = 0;
        pt first_pos = my_pos.extend(dir, max_exd);
        rep (i, n_points) {
            if (is_on_segment(p[i], my_pos, first_pos)) {
                ++first_score;
            }
        }

        // sort all atan2 from first position
        int samep_cnt = 0;
        vector<double> atan2_dirs;
        rep (i, n_points) {
            if (sgn(p[i].y - first_pos.y) == 0 &&
                    sgn(p[i].x - first_pos.x) == 0) {
                ++samep_cnt;
                continue;
            }
            atan2_dirs.push_back(atan2(p[i].y - first_pos.y,
                    p[i].x - first_pos.x));
        }
        sort(atan2_dirs.begin(), atan2_dirs.end());
        double prev_dir = 1e100;
        int second_score = 0;
        int current_score = 0;
        for (const double& atan2_dir : atan2_dirs) {
            if (sgn(atan2_dir - prev_dir) == 0) {
                ++current_score;
            } else {
                current_score = 1;
            }
            to_max(second_score, current_score);
            prev_dir = atan2_dir;
        }
        second_score += samep_cnt;

        to_max(max_score, first_score * second_score);
    }
    return max_score;
}

int main() {
    ios::sync_with_stdio(false);

    repcase {
        my_pos.input();
        cin >> max_exd >> n_points;
        rep (i, n_points) {
            p[i].input();
        }
        // printf ("Case #%d: %d\n", Case++, solve());
        cout << "Case #" << Case++ << ": " << solve() << endl;
    }
    return 0;
}
