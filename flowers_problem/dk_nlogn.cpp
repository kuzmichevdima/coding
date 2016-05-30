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

const int maxn = 2e5+5;

int x[maxn];
int t[maxn];
int n;

int solve() {
    vector <pii> R;
    R.pb(mp(0, 0));
    int cur = 0;
    forn(i, n) {
        if (x[i] >= 0) {
            R.pb(mp(x[i], x[i] < t[i]));
        }
        else cur++;
    }
    sort(R.begin(), R.end());
    //for (pii p : R)
    //    printf("in R %d %d\n", p.fi, p.se);
    vi R_minus(R.size(), 0);
    forn(i, n) if (x[i] < 0) {
        int val = (x[i] + t[i]), pos;
        if (val <= 0) {
            pos = 0;
        }
        else {
            if (val % 2 == 0)
                val /= 2;
            else val = val / 2 + 1;
            pos = lower_bound(R.begin(), R.end(), mp(val, 0)) - R.begin();
        }
        if (pos < (int)R.size()) {
            //printf("R_minus[%d]++\n", pos);
            R_minus[pos]++;
        }
    }
    int result = 0;
    forn(rpos, R.size()) {
        cur -= R_minus[rpos];
        if (R[rpos].se)
            cur++;
        result = max(result, cur);
    }
    if (result % 2 == 0 && result)
        result--;
    return result;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d%d", &x[i], &t[i]);
    }
    int ansR = solve();
    forn(i, n)
        x[i] = -x[i];
    int ansL = solve();
    int ans = max(ansL, ansR);
    printf("%d\n", ans);
}

