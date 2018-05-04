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

const int maxlen = 1e5;

vi imp;
i64 minn[maxlen + 5];
i64 maxx[maxlen + 5];
vi ans;

void go(int lower, int upper, int swaps) {
//    printf("go lower = %d upper = %d swaps = %d\n", lower, upper, swaps);
    if (lower > upper) {
        return;
    }
    if (lower == upper) {
        if (swaps == 0) {
            ans.pb(lower);
        } else
            ans.pb(-1);
        return;
    }
    int len = upper - lower + 1;
    if (minn[len] > swaps || swaps > maxx[len]) {
        ans.pb(-1);
        return;
    }
    swaps -= len - 1;
    fore(middle, lower, lower + (upper - lower) / 2) {
        int len1 = middle - lower;
        int len2 = upper - middle;
        if (minn[len1] + minn[len2] <= swaps && maxx[len1] + maxx[len2] >= swaps) {
            i64 xmin = max(swaps - maxx[len1], minn[len2]);
            i64 xmax = min(swaps - minn[len1], maxx[len2]);
            if (xmin <= xmax) {
                ans.pb(middle);
                go(lower, middle - 1, swaps - xmin);
                go(middle + 1, upper, xmin);
                return;
            }
        }
    }
    ans.pb(-1);
    /*int start = lower;
    int finish = upper;
    while(start < finish) {
        int middle = (start + finish) / 2;
        int len1 = middle - lower;
        int len2 = upper - middle;
        if (maxx[len1] + maxx[len2] >= swaps)
    }*/
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    maxx[1] = minn[1] = 0;
    fore(j, 2, maxlen) {
        maxx[j] = maxx[j - 1] + j - 1;
        int half = (j - 1) / 2;
        minn[j] = j - 1 + minn[half] + minn[j - 1 - half];
        //if (j <= 5)
        //    cout << j << " " << minn[j] << " " << maxx[j] << endl;
    }
    int queries;
    scanf("%d", &queries);
    imp.pb(-1);
    forn(query, queries) {
        ans.clear();
        int n, swaps;
        scanf("%d%d", &n, &swaps);
        go(1, n, swaps);
        for (int x : ans)
            printf("%d ", x);
        printf("\n");
    }
}
