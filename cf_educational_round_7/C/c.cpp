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

pii tree[maxn * 4];
int a[maxn];

pii get(int i, int L, int R, int A, int B) {
    if (A >= R || L >= B)
        return mp(-1, -1);
    if (A == L && B == R)
        return tree[i];
    int m = (L + R) / 2;
    pii g1 = get(i * 2, L, m, A, min(m, B));
    pii g2 = get(i * 2 + 1, m, R, max(A, m), B);
    pii res = mp(g2.fi == -1 || (g1.fi != -1 && a[g1.fi] < a[g2.fi]) ? g1.fi : g2.fi,
            g2.se == -1 || (g1.se != -1 && a[g1.se] > a[g2.se]) ? g1.se : g2.se);
//    printf("i = %d L = %d R = %d A = %d B = %d res = %d %d\n", i, L, R, A, B, res.fi, res.se);
    return res;
}

void build(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i] = mp(L, L);
        return;
    }
    int m = (L + R) / 2;
    build(i * 2, L, m);
    build(i * 2 + 1, m, R);

    tree[i] =  mp(a[tree[i * 2].fi] < a[tree[i * 2 + 1].fi] ? tree[i * 2].fi : tree[i * 2 + 1].fi,
            a[tree[i * 2].se] > a[tree[i * 2 + 1].se] ? tree[i * 2].se : tree[i * 2 + 1].se);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    fore(i, 1, n)
        scanf("%d", &a[i]);
    build(1, 1, n + 1);
    forn(it, m) {
        int L, R, x;
        scanf("%d%d%d", &L, &R, &x);
        pii p = get(1, 1, n + 1, L, R + 1);
 //       printf("L = %d R = %d x = %d p = %d %d\n", L, R, x, p.fi, p.se);
        int ans;
        if (a[p.fi] == x && a[p.se] == x)
            ans = -1;
        else if (a[p.fi] == x)
            ans = p.se;
        else ans = p.fi;
        printf("%d\n", ans);
    }
}
