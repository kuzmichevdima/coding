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

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    if (k == 0) {
        cout << (i64)n * n;
        exit(0);
    }
    i64 ans = 0;
    fore(b, k + 1, n) {
        //how many <= N and has rem. >= k when divided by b
        //k..b-1, b + k..b+b-1, 2b + k, ...
        //tb-1 <= n, n + 1 >= tb
        int t = (n + 1) / b;
        ans += (i64)(b - k) * t;
        int start = t * b + k;
        if (n >= start)
            ans += (n - start + 1);
        //cout << "b = " << b << " ans = " << ans <<  " start = " << start << " t = " << t << endl;
    }
    cout << ans;
}

