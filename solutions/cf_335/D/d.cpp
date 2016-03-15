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

struct Elem
{
    int a, b, c, d;
};

const int maxn = 2e5+5;
const int inf = 1e9;

Elem v[maxn];
int tree[maxn * 4];
int d[maxn];
int fr[maxn];
queue <int> Q;
vector <pii> listy[maxn];
int pointer[maxn];

inline int merge(int g1, int g2)
{
    if (g1 == -1)
        return g2;
    if (g2 == -1)
        return g1;
    return (listy[g1][pointer[g1]].fi < listy[g2][pointer[g2]].fi ? g1 : g2);

}

int get(int i, int L, int R, int A, int B)
{
    if (A >= R || L >= B)
        return -1;
    if (A == L && B == R)
        return tree[i];
    int M = (L + R) / 2;
    int g1 = get(i * 2, L, M, A, min(M, B));
    int g2 = get(i * 2 + 1, M, R, max(A, M), B);
    return merge(g1, g2);
}

void update(int i, int L, int R, int pos)
{
    if (L + 1 == R)
    {
        tree[i] = (pointer[pos] < (int)listy[pos].size() ? pos : -1);
        return;
    }
    int M = (L + R) / 2;
    if (pos < M)
        update(i * 2, L, M, pos);
    else update(i * 2 + 1, M, R, pos);
    tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
}

void build(int i, int L, int R)
{
//    printf("build %d %d %d\n", i, L, R);
    if (L + 1 == R)
    {
        tree[i] = listy[L].empty() ? -1 : L;
        return;
    }
    int M = (L + R) / 2;
    build(i * 2, L, M);
    build(i * 2 + 1, M, R);
    tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
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
    vi uniq_x;
    fore(j, 1, n)
    {
        scanf("%d%d%d%d", &v[j].a, &v[j].b, &v[j].c, &v[j].d);
        uniq_x.pb(v[j].a);
        uniq_x.pb(v[j].c);
    }
    uniq_x.pb(0);
    sort(uniq_x.begin(), uniq_x.end());
    uniq_x.resize(unique(uniq_x.begin(), uniq_x.end()) - uniq_x.begin());
    fore(j, 1, n)
    {
        v[j].a = lower_bound(uniq_x.begin(), uniq_x.end(), v[j].a) - uniq_x.begin();
        listy[v[j].a].pb(mp(v[j].b, j));
        v[j].c = lower_bound(uniq_x.begin(), uniq_x.end(), v[j].c) - uniq_x.begin();
    }
/*    forn(j, uniq_x.size())
    {
        printf("j = %d size = %d\n", j, listy[j].size());
        for (pii p : listy[j])
            printf("%d %d\n", p.fi, p.se);
    }*/
    forn(j, uniq_x.size())
    {
        sort(listy[j].begin(), listy[j].end());
    }
    fore(j, 0, n)
        d[j] = inf;
    Q.push(0);
    d[0] = 0;
    build(1, 0, uniq_x.size());
    while(!Q.empty())
    {
        int x = Q.front();
        //printf("x = %d\n", x);
        Q.pop();
        while(true)
        {
            int u = get(1, 0, uniq_x.size(), 0, v[x].c + 1);
        //    printf("u = %d\n", u); 
            if (u == -1 || listy[u][pointer[u]].fi > v[x].d)
                break;
            int number = listy[u][pointer[u]].se;
            if (d[number] == inf)
            {
                d[number] = d[x] + 1;
                fr[number] = x;
//                printf("fr[%d] = %d\n", number, x);
                Q.push(number);
            }
            pointer[u]++;
          //  printf("pointer[%d] = %d size = %d\n", u, pointer[u], listy[u].size());
            update(1, 0, uniq_x.size(), u);
        }
    }
    if (d[n] == inf)
    {
        printf("-1");
        exit(0);
    }
    int cur = n;
    vi ans;
    while(cur != 0)
    {
        ans.pb(cur);
        cur = fr[cur];
    }
    printf("%d\n", (int)ans.size());
    for (int j = (int)ans.size() - 1; j >= 0; j--)
        printf("%d ", ans[j]);
}
