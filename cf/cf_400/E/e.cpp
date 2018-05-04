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

const int limit = 1e6;

map <i64, i64> M;
bool mark[limit + 5];
vi primes;

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

int f1(int x) {
    if (x == 1)
        return 1;
    int ans = 0;
    fore(j, 1, x - 1)
        if (gcd(j, x - j) == 1)
            ans++;
    return ans;
}

i64 f(i64 x) {
    i64 result = x;
    for (int d = 2; (i64)d * d <= x; ++d) {
        if (x % d == 0) {
            while(x % d == 0)
                x /= d;
            result -= result / d;
        }
    }
    if (x != 1)
        result -= result / x;
    return result;
}


int main() {
#ifdef LOCAL
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    i64 n, k;
    cin >> n >> k;
    for (i64 it = 0; it < (k + 1) / 2; ++it) {
        if (n == 1)
            break;
        n = f(n);
    }
    int MOD = 1e9+7;
    cout << n % MOD;
}

