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

const int maxn = 1e6;
int cnt[maxn + 5];
bool mark[maxn];
bool bad[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    fore(p, 2, 1e3) {
        if (!mark[p]) {
            for (int j = p * p; j <= maxn; j += p * p)
                bad[j] = true;
            for (int j = 2 * p; j <= maxn; j+= p)
                mark[j] = true;
        }
    }
    cnt[0] = 0;
    fore(j, 1, maxn) {
        cnt[j] = cnt[j - 1] + !bad[j];
    }
    int tests;
    scanf("%d", &tests);
    forn(t, tests) {
        int L, R;
        scanf("%d%d", &L, &R);
        int ans = cnt[R] - (L == 0 ? 0 : cnt[L - 1]);
        printf("%d\n", ans);
    }
}

