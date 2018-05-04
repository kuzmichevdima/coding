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

vi pos[26];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    string a, b;
    cin >> a >> b;
    forn(j, a.length()) {
        pos[a[j] - 'a'].pb(j);
    }
    int cur = 0;
    int ans = 1;
    for (char c1 : b) {
        int c = c1 - 'a';
        while(true) {
            auto iter = lower_bound(pos[c].begin(), pos[c].end(), cur);
            if (iter == pos[c].end()) {
                if (cur == 0) {
                    printf("-1");
                    exit(0);
                }
                ans++;
                cur = 0;
            } else {
                cur = *iter + 1;
                break;
            }
        }
    }
    printf("%d", ans);
}
