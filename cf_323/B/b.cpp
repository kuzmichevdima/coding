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

const int maxval = 300;

int cnt[maxval + 5];
int ans, n;
int tree[maxval * 4 + 5];
int a[maxval];

void myfill(vector <pii> & v)
{
    forn(iter, n)
        forn(pos, n)
           v.pb(mp(a[pos], 1));
}

int get(int i, int l, int r, int p)
{
    if (l + 1 == r)
        return tree[i];
    int m = (l + r ) / 2;
    if (p < m)
        return max(tree[i], get(i * 2, l, m, p));
    else return max(tree[i], get(i * 2 + 1, m, r, p));
}

void upd(int i, int l, int r, int a, int b, int dp)
{
    if (l >= b || a >= r)
        return;
    if (l == a && r == b)
    {
        tree[i] = max(tree[i], dp);
        return;
    }
    int m = (l + r) / 2;
    upd(i * 2, l, m, a, min(m, b), dp);
    upd(i * 2 + 1, m, r, max(m, a), b, dp);
}

inline int get(int pos)
{
    return get(1, 1, maxval + 1, pos);
}

inline void upd(int start, int dp)
{
    upd(1, 1, maxval + 1, start, maxval + 1, dp);
}

void solve(vector <pii> v)
{
    memset(tree, 0, sizeof(tree));
    forn(j, v.size())
    {
        int val = v[j].fi;
        int dp = get(val) + v[j].se;
        ans = max(ans, dp);
        upd(val, dp);
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
    int T;
    scanf("%d%d", &n, &T);
    forn(j, n)
    {
        scanf("%d", &a[j]);
        cnt[a[j]]++;
    }
    if (T - 2 * n > 0)
    {
        forn(j, n)
        {
            vector <pii> v;
            myfill(v); 
            v.pb(mp(a[j], (T - 2 * n) * cnt[a[j]]));
            myfill(v);
            solve(v);
        }
    }
    else
    {
        vector <pii> v;
        forn(iter, T)
            forn(j, n)
                v.pb(mp(a[j], 1));
        solve(v);
    }

    printf("%d\n", ans);
}
