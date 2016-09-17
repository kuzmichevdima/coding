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

const int MOD = 1e9+7;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    string s;
    int m;
    cin >> s >> m;
    vi z(s.length());
    for (int i=1, l=0, r=0; i < (int)s.length(); i++) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < (int)s.length() && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    int ans = 0;
    fore(k, 0, (min(m, (int)s.length() - 1))) {
        if (k == 0 || (z[k] >= (int)s.length() - k && z[(int)s.length() - k] >= k)) {
            int bound  = (m - k) / s.length();
            int to_add = k == 0 ? bound : bound + 1;
            ans = (ans + to_add % MOD) % MOD;
        }
//        printf("k = %d ans = %d\n", k, ans);
    }
    printf("%d", ans);
}

