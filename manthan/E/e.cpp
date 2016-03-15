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

#define ld long double

const int inf = 2e9;
const int maxn = 1e6+5;

pii tree[maxn * 4];
int c[maxn];
int v[maxn];

pii get(int i, int L, int R, int A, int B)
{
//    printf("%d %d %d %d %d\n", i, L, R, A, B);
    if (L >= B || A >= R)
        return mp(-inf, inf);
    if (L == A && R == B)
        return tree[i];
    int m = (L + R) / 2;
    pii g1 = get(i * 2, L, m, A, min(B, m));
    pii g2 = get(i * 2 + 1, m, R, max(A, m), B);
    return mp(max(g1.fi, g2.fi), min(g1.se, g2.se));
}

void build(int i, int L, int R)
{
    if (L + 1 == R)
    {
        tree[i] = mp(v[L], c[L]);
        return;
    }
    int m = (L + R) / 2;
    build(i * 2, L, m);
    build(i * 2 + 1, m, R);
    tree[i] = mp(max(tree[i * 2].fi, tree[i * 2 + 1].fi), min(tree[i * 2].se, tree[i * 2 + 1].se));
}


int n, k;
vi p;

pii get(int A, int B)
{
    return get(1, 0, n, A, B); 
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    forn(j, n)
    {
        scanf("%d", &v[j]);
        v[j] *= 100;
    }
    forn(j, n)
        scanf("%d", &c[j]);
    build(1, 0, n);
    forn(L, n)
    {
        int start = L;
        int finish = n - 1;
        while(start < finish)
        {
//            printf("%d %d\n", start, finish);
            int middle = (start + finish) / 2 + 1;
            pii g = get(L, middle + 1);
            if (g.fi <= g.se)
                start = middle;
            else finish = middle - 1;
        }
        pii tmp = get(L, start + 1);
        //printf("L = %d start = %d tmp = %d %d\n", L, start, tmp.fi, tmp.se);
        int res1 = min(tmp.fi, tmp.se);
        int res2 = (start == n - 1 ? -inf : min(get(L, start + 2).se, get(L, start + 2).fi));
        p.pb(max(res1, res2));
        printf("+ %d\n", max(res1, res2));
    }
    sort(p.begin(), p.end());
    //for (int x : p)
      //  printf("%d ", x);
    ld ans = 0.0;
    ld cur = 1;
    fore(j, 1, k)
        cur = cur * (ld)j / (ld)(n - k + j);
    int s = k - 1;
    for (int pos = n - k; pos >= 0; pos--)
    {
        ans += cur * p[pos];
        s++;
        cur *= (ld)s / (ld)(s - k + 1);
    }
    printf("%.10Lf\n", ans);
}
