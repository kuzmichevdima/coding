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

void fail() {
    printf("-1");
    exit(0);
}

void inc_print(int s, int f) {
    fore(x, s, f)
        printf("%d ", x);
}

void dec_print(int s, int f) {
    if (s >= f)
        for (int x = s; x >= f; --x) {
            printf("%d ", x);
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
    //a+b-1 <= n,
    //n-b,...,a,1,2,..a-1, n, n-1,...,n-b+1
    //increasing - a, 2
    //decr-n-b-a+2, b
    //corner cases - a = 1, b = 1
    //if b >= n - b - a + 2
    //a+1, ..., n-b+1, n,n-1, .., n-b+2, 1, 2, ..,a
    //incr - n-a-b+2, a
    //if a >= n - a - b + 2
    //b < n - b - a + 2
    //a < n - a - b + 2
    //3(a + b) < 2 * n +4
    //decr - b
    //
    //a,a+1,...,n-b, 1,2,..a-1, n, n-1,...,n-b+1
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    if (a + b - 1 > n) {
        fail();
    }
    if (a == 1) {
        if (b != n)
            fail();
        forn(i, n)
            printf("%d ", n - i);
        exit(0);
    }
    if (b == 1) {
        if (a != n)
            fail();
        forn(i, n)
            printf("%d ", i + 1);
        exit(0);
    }
    if (a >= n - b - a + 2) {
        inc_print(a + 1, n - b + 1);
        dec_print(n, n - b + 2);
        inc_print(1, a);
        exit(0);
    }
    if (b >= n - b - a + 2) {
        dec_print(n - b, a);
        inc_print(1, a - 1);
        dec_print(n, n - b + 1);
        exit(0);
    }
    dec_print(n - b + 1, a + 1);
    dec_print(n, n - b + 2);
    inc_print(1, a);


}

