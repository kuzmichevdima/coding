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

const int maxn = 150005;

vi tree[maxn * 8];
vector <i64> sums[maxn * 8];
int a[maxn];

void build(int i, int l, int r) {
    if (l + 1 == r) {
        tree[i].pb(a[l]);
        sums[i].pb(a[l]);
        return;
    }
    int m = (l + r) / 2;
    build(i * 2, l, m);
    build(i * 2 + 1, m, r);
    tree[i].resize(tree[i * 2].size() + tree[i * 2 + 1].size());
    merge(tree[i * 2].begin(), tree[i * 2].end(), tree[i * 2 + 1].begin(), tree[i * 2 + 1].end(), tree[i].begin());
    sums[i].pb(tree[i][0]);
    fore(j, 1, (int)tree[i].size() - 1)
        sums[i].pb(sums[i].back() + tree[i][j]);
}

i64 get(int i, int tl, int tr, int A, int B, i64 s) {
    if (tl >= B || A >= tr)
        return 0;
    if (tl == A && tr == B) {
        int pos = upper_bound(tree[i].begin(), tree[i].end(), s) - tree[i].begin();
        i64 res = (pos == 0 ? 0 : sums[i][pos - 1]);
        return res;
    }
    int m = (tl + tr) / 2;
    return get(i * 2, tl, m, A, min(m, B), s) + get(i * 2 + 1, m, tr, max(A, m), B, s);
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
    forn(i, m) {
        int l, r;
        scanf("%d%d", &l, &r);
        i64 s = 1;
        i64 delta1 = 0;
        while(true) {
  //          cout << l << " " << r << endl;
            i64 delta = get(1, 1, n + 1, l, r + 1, s);
//            cout << s << " " << delta << endl;
  //          exit(0);
            if (delta == delta1)
                break;
            s += delta - delta1;
            delta1 = delta;
        }
        cout << s << endl;
    }
}
