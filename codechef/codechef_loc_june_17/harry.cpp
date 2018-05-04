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

const int maxn = 2e4+5;

int a[maxn];
int n;

i64 get(int k) {
    i64 res = 0;
    forn(j, n)
        if (a[j] > k)
            res += k;
        else res += a[j];
    return res;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int t;
    scanf("%d", &t);
    forn(test, t) {
        i64 s;
        cin >> n >> s;
        forn(j, n)
            scanf("%d", &a[j]);
        int start = 0;
        int finish = 1e5+1;
        while(start < finish) {
            int middle = (start + finish) / 2;
            if (get(middle) < s)
                start = middle  + 1;
            else finish = middle;
        }
        if (get(start) != s)
            printf("-1\n");
        else printf("%d\n", start);
    }
}

