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
    if (x == 1)
        return 1;
//    cout << "f " << x << endl;
    if (M.find(x) != M.end())
        return M[x];
    for (int prime : primes) {
        if ((i64)prime * prime > x)
            return M[x] = x - 1;
        if (x % prime == 0) {
            i64 L = x / prime;
            while(L % prime == 0) {
                L /= prime;
            }
            return M[x] = f(L) * f(prime) * (x / L / prime);
        }
    }
    return M[x] = x - 1;
}

void get() {
    fore(j, 2, limit) {
        if (mark[j])
            continue;
        primes.pb(j);
        for (int k = 2 * j; k <= limit; k += j)
            mark[k] = true;
    }
}

int main() {
#ifdef LOCAL
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    get();
    i64 n, k;
    cin >> n >> k;
    forn(iter, (k + 1) / 2) {
        if (n == 1)
            break;
        n = f(n);
    }
    cout << n;
}

