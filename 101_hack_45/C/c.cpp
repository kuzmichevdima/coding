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

i64 a[maxn];
i64 pref[maxn];
i64 suff[maxn];

i64 gcd(i64 x, i64 y) {
    if (y == 0)
        return x;
    return gcd(y, x % y);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    forn(j, n)
        cin >> a[j];
    if (n == 1) {
        cout << a[0] + 1;
        exit(0);
    }
    pref[0] = a[0];
    fore(j, 1, n - 1)
        pref[j] = gcd(pref[j - 1], a[j]);
    suff[n - 1] = a[n - 1];
    for (int j = n - 2; j >= 0; j--)
        suff[j] = gcd(suff[j + 1], a[j]);
    forn(chosen, n) {
        i64 g;
        if (chosen == 0)
            g = suff[1];
        else if (chosen == n - 1)
            g = pref[n - 2];
        else g = gcd(suff[chosen + 1], pref[chosen - 1]);
        if (a[chosen] % g != 0) {
            cout << g;
            exit(0);
        }
    }
    assert(false);
}
