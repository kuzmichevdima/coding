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


const int MOD = 1e9+7;
const int maxn = 1e6+5;
int pref[maxn][26];
i64 cnt[26][26];
int suff[26];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    string s;
    cin >> s;
    forn(i, s.length()) {
        forn(j, 26)
            pref[i][j] = i == 0 ? 0 : pref[i - 1][j];
        pref[i][s[i] - 'a']++;
    }
    i64 ans = 0;
    for (int i = (int)s.length() - 1; i >= 1; i--) {
        int num = s[i] - 'a';
        forn(j, 26) {
            ans += (i64)pref[i - 1][j] * cnt[num][j] % MOD;
        }
//        cout << i << " " << ans << endl;
        forn(j, 26)
            cnt[num][j] += suff[j];
        suff[num]++;
    }
    cout << ans % MOD;
}
