#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>

using namespace std;

#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define fs first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

struct Point {
    int x, y, num;
    double coeff;
};

const int maxn = 1e5 + 5;

int tree[maxn* 4];
Point p[maxn];

bool operator < (Point fi, Point se) {
    return fi.x < se.x;
}

int get(int i, int L, int R, int A, int B) {
    if (L >= A && R <= B)
        return tree[i];
    if (L >= B || A >= R)
        return 0;
    int M = (L + R) / 2;
    return get(i * 2, L, M, A, B) + get(i * 2 + 1, M, R, A, B);
}

void upd(int i, int L, int R, int pos) {
    if (L + 1 == R) {
        tree[i]++;
        return;
    }
    int M = (L + R) / 2;
    if (pos < M)
        upd(i * 2, L, M, pos);
    else upd(i * 2 + 1, M, R, pos);
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    vector<double> uniq;
    forn(i, n) {
        scanf("%d%d", &p[i].x, &p[i].y);
        p[i].num = i;
        p[i].coeff = (double)p[i].y / p[i].x;
        uniq.pb(p[i].coeff);
    }
    vi ans(n);
    sort(uniq.begin(), uniq.end());
    uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());
    sort(p, p + n);
    forn(i, n) {
        Point q = p[i];
        int pos = lower_bound(uniq.begin(), uniq.end(), q.coeff) - uniq.begin();
        ans[q.num] = get(1, 0, uniq.size(), 0, pos);
        upd(1, 0, uniq.size(), pos);
    }
    forn(i, n)
        printf("%d\n", ans[i]);
}

