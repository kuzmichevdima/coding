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

const int con = 1e6;
const int maxn = 2e5+5;
const int MOD = 1e9+7;
bool mark[con + 5];
int tree[maxn * 4];
vi primes;
int ans[maxn];
vi list[maxn];
vector <pii> decomp[maxn];
int a[maxn];
vector <pii> queries[maxn];
int mult[maxn];

int bin_pow(int x, int p)
{
    if (p == 0)
        return 1;
    int y = bin_pow(x, p / 2);
    y = (i64)y * y % MOD;
    if (p & 1)
        y = (i64)y * x % MOD;
    return y;
}

void precalc()
{
    fore(i, 2, con) if (!mark[i])
    {
        primes.pb(i);
        for (int j = 2 * i; j <= con; j += i)
            mark[j] = true;
    }
    forn(j, primes.size())
    {
        //mult[j] = (i64)(primes[j]) * bin_pow(primes[j] - 1, MOD - 2) % MOD;

        mult[j] = (i64)(primes[j] - 1) * bin_pow(primes[j], MOD - 2) % MOD;
    }
}

void build(int i, int L, int R)
{
    if (L + 1 == R)
    {
//        printf("i = %d L = %d\n", i, L);
        tree[i] = a[L];
        return;
    }
    int M = (L + R) / 2;
    build(i * 2, L, M);
    build(i * 2 + 1, M, R);
    tree[i] = (i64)tree[i * 2] * tree[i * 2 + 1] % MOD;
}

int get(int i, int L, int R, int A, int B)
{
    if (L >= B || A >= R)
        return 1;
    if (L == A && R == B)
        return tree[i];
    int M = (L + R) / 2;
    return (i64)get(i * 2, L, M, A, min(M, B)) * get(i * 2 + 1, M, R, max(A, M), B) % MOD;
}

void upd(int i, int L, int R, int pos, int val)
{
    if (L + 1 == R)
    {
//        printf("upd i = %d pos = %d a[i] = %d val = %d\n", i, pos, a[i], val);
        tree[i] = (i64)tree[i] * val % MOD;
  //      printf("now tree[i] = %d\n", tree[i]);
        return;
    }
    int M = (L + R) / 2;
    if (pos < M)
        upd(i * 2, L, M, pos, val);
    else upd(i * 2 + 1, M, R, pos, val);
    tree[i] = (i64)tree[i * 2] * tree[i * 2 + 1] % MOD;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    precalc();
    int n;
    scanf("%d", &n);
    fore(j, 1, n)
    {
        scanf("%d", &a[j]);
        int start = a[j];
        int p = 0;
        while(primes[p] * primes[p] <= con)
        {
            if (a[j] % primes[p] == 0)
            {
                list[p].pb(j);
                decomp[j].pb(mp(p, (int)list[p].size() - 1));
                while(a[j] % primes[p] == 0)
                    a[j] /= primes[p];
            }
            p++;
        }
//        printf("a[%d] = %d\n", j, a[j]);
        if (a[j] != 1)
        {
            int pos = lower_bound(primes.begin(), primes.end(), a[j]) - primes.begin();
            assert(primes[pos] == a[j]);
            list[pos].pb(j);
            decomp[j].pb(mp(pos, (int)list[pos].size() - 1));
        }
        a[j] = start;
    }
    int Q;
    scanf("%d", &Q);
    forn(j, Q)
    {
        int L, R;
        scanf("%d%d", &L, &R);
  //      printf("query %d %d\n", L, R);
        queries[L].pb(mp(R, j));
    }
    build(1, 1, n + 1);
    forn(j, primes.size()) if (!list[j].empty())
    {
     //   printf("for prime %d upd at %d value = %d\n", primes[j], list[j][0], mult[j]);
        upd(1, 1, n + 1, list[j][0], mult[j]);
    }
    fore(L, 1, n)
    {
    //    printf("L = %d\n", L);
        for (pii q : queries[L])
        {
//            printf("query [%d;%d] number %d\n", L, q.fi, q.se);
            ans[q.se] = get(1, 1, n + 1, L, q.fi + 1);
        }
        for (pii p : decomp[L])
        {
            int prime_number = p.fi;
            int pos = p.se;
            if (pos + 1 < (int)list[prime_number].size())
            {
    //            printf("now upd at %d val = %d prime = %d\n", list[prime_number][pos + 1], mult[prime_number], primes[prime_number]);
                upd(1, 1, n + 1, list[prime_number][pos + 1], mult[prime_number]);
            }
        }
    }
    forn(j, Q)
        printf("%d\n", ans[j]);
}
