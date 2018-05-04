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

const int maxn = 1e5 + 5;
const int mod = 1e9+7;
i64 fact[maxn];
i64 half_fact[maxn];
int n, k;
int tree[maxn * 4];

void precalc()
{
    fact[1] = 1;
    fore(j, 2, maxn - 1)
    {
        fact[j] = (fact[j - 1] * j) % mod;
        half_fact[j] = (j == 2 ? 1 : half_fact[j - 1] * j % mod);
    }
}

/*int bin_pow(int x, int p)
{
    if (p == 0)
        return 1;
    int y = bin_pow(x, p / 2);
    y = (i64)y * y % mod;
    if (p % 2 == 1)
        return ((i64)y * x) % mod;
    else return y;
}*/

inline void add(int & x, int y)
{
    x = (x + y) % mod;
}

void upd(int i, int l, int r, int pos)
{
    if (l + 1 == r)
    {
        tree[i]++;       
        return;
    }
    int m = (l + r) / 2;
    if (pos < m)
        upd(i * 2, l, m, pos);
    else
        upd(i * 2 + 1, m, r, pos);
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

inline void upd(int pos)
{
    //printf("upd %d\n", pos);
    upd(1, 1, n + 1, pos); 
}

int get(int i, int l, int r, int a, int b)
{
    if (l >= b || a >= r)
        return 0;
    if (l == a && r == b)
    {
        return tree[i];
    }
    int m = (l + r) / 2;
    return get(i * 2, l, m, a, min(m, b)) + get(i * 2 + 1, m, r, max(a, m), b);
}

inline int get(int a, int b)
{
    //printf("get %d %d\n", a, b);
    return get(1, 1, n + 1, a, b);
}

inline void clr()
{
    memset(tree, 0, sizeof(tree));
}

inline int get_inv(vi & v)
{
    clr();
    int res = 0;
    forn(j, n)
    {
        res = (res + get(v[j] + 1, n + 1)) % 2;
        upd(v[j]);
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
/*    freopen("inp", "w", stdout);
    forn(j, 1000)
        printf("%d ", j + 1);
    printf("\n");
    forn(j, 1000)
        printf("%d ", 1000 - j);
    exit(0);*/
    precalc();
    int tests;
    scanf("%d", &tests);
    //int two_inv = bin_pow(2, mod - 2);
   /* vi a(7);
    forn(j, 7)
        a[j] = j + 1;
    n = 7;
    int cnt0 = 0;
    int cnt1 = 0;
    do
    {
        forn(j, 7)
            printf("%d ", a[j]);
        int g = get_inv(a);
        printf("inv = %d cnt = %d total = %d\n", g, (g == 0 ? cnt0 : cnt1), cnt0 + cnt1);
        if (g == 0)
            cnt0++;
        else cnt1++;
    }
    while(next_permutation(a.begin(), a.end()));*/
    forn(T, tests)
    {
        scanf("%d%d", &n, &k);
        vi a(n), b(n);
        forn(j, n)
            scanf("%d", &a[j]);
        forn(j, n)
            scanf("%d", &b[j]);
        if (n == k)
        {
            forn(j, n)
                if (b[j] == a[0])
                {
                    bool fail = false;
                    fore(h, 1, n - 1)
                        if (b[(j + h) % n] != a[h])
                        {
                            fail = true;
                            break;
                        }
                    if (fail)
                        printf("-1\n");
                    else printf("%d\n", b[0]);
                    break;
                }
            continue;
        }
        //printf("here\n");
        
        if (k % 2 == 1)
        {       
            int a_inv = get_inv(a);
            int b_inv = get_inv(b);
            //printf("invers: %d %d\n", a_inv, b_inv);
            if (a_inv != b_inv)
            {
                printf("-1\n");
                continue;
            }
        }
        int ans = 0;
        clr();
        forn(j, n - 1)
        {
            int lower = b[j] - get(1, b[j]) - 1;
            //assert(j == n - 2 || to_add % 2 == 0);
            if (k % 2 == 1)
            {
                i64 to_add;
                if (n - j - 1 == 1)
                    to_add = lower / 2;
                else to_add = (i64)lower * half_fact[n - j - 1];
                add(ans, to_add % mod);
            }
         //   printf("lower = %d to_add = %d\n", lower, to_add);
            else add(ans, (i64)lower * fact[n - j - 1] % mod);
            upd(b[j]);
        }
        /*if (k % 2 == 1)
        {

            printf("before ans = %d\n", ans);
            ans = (i64)ans * two_inv % mod;
            printf("after ans = %d\n", ans);
        }*/
        ans = (ans + 1) % mod;
        printf("%d\n", ans);
    }
}

