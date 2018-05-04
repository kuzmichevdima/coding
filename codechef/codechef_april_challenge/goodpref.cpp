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
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int copies;
        string s;
        cin >> s >> copies;
        int full_delta = 0;
        for (char c : s) {
            full_delta += c == 'a' ? 1 : -1;
        }
        //printf("full delta = %d\n", full_delta);
        int cur_delta = 0;
        i64 ans = 0;
        fore(taken, 1, s.length()) {
            cur_delta += s[taken - 1] == 'a' ? 1 : -1;
            if (full_delta == 0) {
                if (0 > -cur_delta) {
                    ans += copies;
                }
                continue;
            }
            //x * full_delta > -cur_delta
            if (full_delta > 0) {
                int s = 0;
                int f = copies - 1;
                while(s < f) {
                    int m = (s + f) / 2;
                    if ((i64)full_delta * m > -cur_delta)
                        f = m;
                    else s = m + 1;
                }
                if ((i64)s * full_delta > -cur_delta)
                    ans += copies - s;
            } else {
                int s = 0;
                int f = copies - 1;
                while(s < f) {
                    int m = (s + f) / 2 + 1;
                    if ((i64)full_delta * m > -cur_delta)
                        s = m;
                    else f = m - 1;
                }
                if ((i64)full_delta * s > -cur_delta)
                    ans += s + 1;
            }
        }
        cout << ans << endl;
    }
    //x * full_delta + 
}

