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

const int maxn = 5005;

int n;
int a[maxn];
int cnt[maxn];
int ans[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    forn(i, n)
        scanf("%d", &a[i]);
    forn(i, n) {
        memset(cnt, 0, sizeof(cnt));
        pii maxx = mp(0, 0);
        fore(j, i, n - 1) {
            cnt[a[j]]++;
            maxx = max(maxx, mp(cnt[a[j]], -a[j]));
            ans[-maxx.se]++;
        }
    }
    fore(j, 1, n)
        printf("%d ", ans[j]);
}
