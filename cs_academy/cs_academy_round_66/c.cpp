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
int cnt[limit + 5];
int divs[limit + 5];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, t;
    scanf("%d%d", &n, &t);
    forn(i, n) {
        int x;
        scanf("%d", &x);
        cnt[x]++;
    }
    fore(val, 1, t) {
        if (cnt[val]) {
            for (int m = val; m <= t; m += val) {
                divs[m] += cnt[val];
            }
        }
    }
    int maxx = 0;
    fore(m, 1, t) {
        maxx = max(maxx, divs[m]);
    }
    int second = 0;
    fore(m, 1, t)
        if (divs[m] == maxx) {
            second++;
        }
    cout << maxx << " " << second;
}

