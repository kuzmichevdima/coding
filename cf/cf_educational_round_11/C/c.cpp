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

const int maxn = 3e5+5;

int a[maxn];
int s[maxn];

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
    forn(i, n) {
        scanf("%d", &a[i]);
        if (i == 0) {
            s[0] = a[0] == 0;
        }
        s[i] = s[i - 1] + (a[i] == 0);
    }
    int best = -1;
    pii seg;
    forn(i, n) {
        int pos = upper_bound(s, s + n, (i == 0 ? 0 : s[i - 1]) + k) - s;
        if (pos - i > best) {
            best = pos - i;
            seg = mp(i, pos - 1);
        }
    }
    printf("%d\n", best);
    forn(j, n) {
        if (j >= seg.fi && j <= seg.se)
            printf("1 ");
        else printf("%d ", a[j]);
    }
}
