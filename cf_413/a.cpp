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
    int n, t, k, d;
    scanf("%d%d%d%d", &n, &t, &k, &d);
    int without = (n / k) * t;
    if (n % k != 0)
        without += t;
    int start = d;
    int finish = 1e6;
    while(start < finish) {
        int middle = (start + finish) / 2;
        int cnt1 = (middle / t) * k;
        int cnt2 = (middle - d) / t * k;
        if (cnt1 + cnt2 >= n)
            finish = middle;
        else start = middle + 1;
    }
    cerr << without << " " << start << endl;
    if (start < without)
        printf("YES");
    else printf("NO");
}

