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

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

int f(int n) {
    if (n == 1)
        return 1;
    int result = 0;
    fore(x, 1, n - 1) {
        if (gcd(x, n - x) == 1)
            result++;
    }
    return result;
}

int g(int n) {
    int result = 0;
    fore(d, 1, n) {
        if (n % d == 0)
            result += f(n / d);
    }
    return result;
}

int F(int n, int k) {
    if (k == 1)
        return f(n);
    if (k % 2 == 0)
        return F(n, k - 1);
    return f(F(n, k - 1));
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    fore(j, 1, 30) {
        int gn = g(j);
        assert(gn == j);
        printf("f(%d) = %d\n", j, f(j));
    }
    printf("%d\n%d\n", F(7, 1), F(200, 6));
}
