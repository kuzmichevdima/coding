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

const int maxn = 1205;
const int MOD = 1e9+7;
int dp[maxn][maxn];
int longest[maxn];
int a[maxn];
i64 fact[maxn];
i64 rev_fact[maxn];

inline void add(int & x, int y) {
    x = (x + y) % MOD;
}

i64 C(int n, int k) {
    return fact[n] * rev_fact[k] % MOD * rev_fact[n - k] % MOD;
}

int bin_pow(int x, int p) {
    if (p == 0)
        return 1;
    int y = bin_pow(x, p / 2);
    y = (i64)y * y % MOD;
    if (p & 1)
        y = (i64)y * x % MOD;
    return y;
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
    fact[0] = 1;
    fore(j, 1, n) {
        fact[j] = fact[j - 1] * j % MOD;
    }
    fore(j, 0, n) {
        rev_fact[j] = bin_pow(fact[j], MOD - 2);
        //cout << j << " " << rev_fact[j] * fact[j] % MOD << endl;
    }
    forn(i, n)
        scanf("%d", &a[i]);
    longest[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
        longest[i] = a[i] <= a[i + 1] ? longest[i + 1] + 1 : 1;
    fore(i, 1, longest[0])
        fore(active, 0, i)
            dp[i][active] = C(i, active);
    fore(done, 1, n - 1)
        fore(active, 1, longest[done]) if (dp[done][active] != 0) {
            i64 to_add = fact[active] * dp[done][active] % MOD;
            fore(j, 0, min(active, longest[done + active]))
                add(dp[done + active][j], C(active, j) * to_add % MOD);
        }
    printf("%d", dp[n][0]);
}
