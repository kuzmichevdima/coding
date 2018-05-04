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
    int n, m;
    scanf("%d%d", &n, &m);
    vi a(n), b(m);
    forn(i, n) {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end());
    forn(i, m) {
        scanf("%d", &b[i]);
    }
    sort(b.begin(), b.end());
    int ans0 = 0;
    int ans1 = 0;
    forn(i, min(a.size(), b.size())) {
        if (a[a.size() - i - 1] > b[b.size() - i - 1])
            ans0++;
        else ans1++;
    }
    printf("%d %d", ans0, ans1);
}

