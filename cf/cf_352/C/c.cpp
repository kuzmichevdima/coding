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

const int maxn = 2e5+5;

i64 H[maxn];
i64 tree[maxn * 8];
i64 app[maxn * 8];
int n;
vi list[maxn];
int a[maxn];

void push(int i, int sz) {
    if (!app[i])
        return;
    app[i * 2] = app[i * 2 + 1] = app[i];
    tree[i] = app[i] * sz;
    app[i] = 0;
}

void upd(int i, int L, int R, int A, int B, int val) {
    if (L >= B || A >= R)
        return;
    if (L == A && R == B) {
        app[i] = val;
        return;
    }
    push(i, R - L);
    int m = (L + R) / 2;
    upd(i * 2, L, m, A, min(m, B), val);
    upd(i * 2 + 1, m, R, max(L, A), B, val);
    tree[i] = (app[i * 2] ? app[i * 2] * (m - L) : tree[i * 2]) + (app[i * 2 + 1] ? app[i * 2 + 1] * (R - m) : tree[i * 2 + 1]);
}

int get(int i, int L, int R, int pos) {
    if (L + 1 == R)
        return app[i] ? app[i] : tree[i];
    push(i, R - L);
    int m = (L + R) / 2;
    if (pos < m)
        return get(i * 2, L, m, pos);
    else return get(i * 2 + 1, m, R, pos);
}

void build(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i] = L;
        return;
    }
    int m = (L + R) / 2;
    build(i * 2, L, m);
    build(i * 2 + 1, m, R);
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void upd_max(int L, int R, int val) {
    if (L >= R)
        return;
//    printf("L = %d R = %d val = %d\n", L, R, val);
    int s = L;
    int f = R - 1;
    while(s < f) {
        int m = (s + f) / 2 + 1;
        if (get(1, 0, n, m) >= val)
            f = m - 1;
        else s = m;
    }
    if (get(1, 0, n, s) < val) {
        upd(1, 0, n, L, s + 1, val);
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    int max_val = 0;
    forn(j, n) {
        scanf("%d", &a[j]);
        for (int d = 1; d * d <= a[j]; d++) {
            if (a[j] % d == 0) {
                list[d].pb(j);
                if (d * d != a[j])
                    list[a[j] / d].pb(j);
            }
        }
        max_val = max(max_val, a[j]);
    }
    build(1, 0, n);
    for (int i = max_val; i >= 0; i--) {
        H[i] = (i64)n * n - tree[1]; 
        if (list[i].size() > 1) {
            upd_max(list[i][1] + 1, n, n);
            upd_max(list[i][0] + 1, list[i][1] + 1, list[i].back());
            upd_max(0, list[i][0] + 1, list[i][(int)list[i].size() - 2]);
        }
    }
    i64 ans = 0;
    for (int i = max_val; i >= 1; i--)
        ans += (H[i] - H[i - 1]) * i;
    cout << ans;
}
