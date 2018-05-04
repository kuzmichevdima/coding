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

int dp[20][2];
void upd(int& x, int y) {
    x = max(x, y);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    i64 n;
    cin >> n;
    vi d;
    while(n) {
        d.pb(n % 10);
        n /= 10;
    }
    reverse(d.begin(), d.end());
    forn(digit, d.size())
        forn(flag, 2)
            dp[digit][flag] = -100500;
    dp[0][false] = 0;
    forn(digit, d.size())
        forn(flag, 2) {
            if (flag) {
                forn(chosen, 10) {
                    upd(dp[digit + 1][true], dp[digit][flag] + chosen);
                }
            } else {
                forn(chosen, d[digit]) {
                    upd(dp[digit + 1][true], dp[digit][flag] + chosen);
                }
                upd(dp[digit + 1][false], dp[digit][flag] + d[digit]);
            }
        }
    cout << max(dp[d.size()][0], dp[d.size()][1]);
}

