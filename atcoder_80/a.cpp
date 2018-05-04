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

int cnt[3];
int n;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    forn(j, n) {
        int x;
        scanf("%d", &x);
        if (x % 4 == 0)
            cnt[2]++;
        else if (x % 2 == 0)
            cnt[1]++;
        else cnt[0]++;
    }
    int prev = 2;
    forn(j, n) {
        bool ok = false;
        fore(chosen, 2 - prev, 2)
            if (cnt[chosen]) {
                cnt[chosen]--;
                prev = chosen;
                ok = true;
                break;
            }
        if (!ok) {
            printf("No");
            exit(0);
        }
    }
    printf("Yes");
}

