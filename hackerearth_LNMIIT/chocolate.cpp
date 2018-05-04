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

const int maxn = 2005;
const int mod = 1e6+3;
const int maxpr = 1e6+5;

int tree[maxn * 4];
int a[maxn];
int f[maxpr + 5];

int get(int i, int L, int R, int A, int B) {
    if (L == A && R == B)
        return tree[i];
    if (L >= B || A >= R)
        return 0;
    int M = (L + R) / 2;
    return max(get(i * 2, L, M, A, min(B, M)),
            get(i * 2 + 1, M, R, max(A, M), B));
}

void build(int i, int L, int R) {
    if (L + 1 == R) {
        tree[i] = f[a[L]];
        return;
    }
    int M = (L + R) / 2;
    build(i * 2, L, M);
    build(i * 2 + 1, M, R);
    tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
}

void upd(int i, int L, int R, int pos) {
    if (L + 1 == R) {
        a[L] = f[a[L]];
        tree[i] = f[a[L]];
        return;
    }
    int M = (L + R) / 2;
    if (pos < M)
        upd(i * 2, L, M, pos);
    else upd(i * 2 + 1, M, R, pos);
    tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
}

//int last[maxpr + 5];
bool mark[maxpr + 5];
//vi lst[maxpr + 5];

void precalc() {
    vi primes;
    fore(i, 2, maxpr)
        if (!mark[i]) {
            primes.pb(i);
            for (int j = 2 * i; j <= maxpr; j += i)
                mark[j] = true;
        }
    fore(i, 2, maxpr) {
        int cur = i;
        vi lst;
        for (int d : primes) {
            if (d * d > cur)
                break;
            if (cur % d == 0) {
                while (cur % d == 0)
                    cur /= d;
                lst.pb(d);
            }
        }
        if (cur > 1)
            lst.pb(cur);
        //if (i == 10)
          //  break;
        i64 val = 0;
        for (int prof = 1; prof < (1 << lst.size()); prof++) {
            int x = 1;
            int bits = 0;
            forn(j, lst.size())
                if (prof & (1 << j)) {
                    x *= lst[j];
                    bits++;
                }
            i64 sum = (i64)(i + x) * i / 2 / x;
            //printf("i = %d x = %d sum = %lld\n", i, x, sum);
            if (bits % 2 == 1)
                val += sum;
            else val -= sum;
        }
        f[i] = val % mod;
    }
    //fore(i, 1, 10)
      //  printf("f[%d] = %lld\n", i, f[i]);
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
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n, Q;
        scanf("%d%d", &n, &Q);
        fore(j, 1, n) {
            // assert(a[j] <= maxpr);
            int x;
            scanf("%d", &x);
            a[j] = x;
        }
        build(1, 1, n + 1);
        forn(q, Q) {
            int typ;
            scanf("%d", &typ);
            if (typ == 1) {
                int L, R;
                scanf("%d%d", &L, &R);
                printf("%d\n", get(1, 1, n + 1, L, R + 1));
            } else {
                int pos;
                scanf("%d", &pos);
                upd(1, 1, n + 1, pos);
            }
        }
    }
}

