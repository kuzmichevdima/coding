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

const int maxn = 1e4+5;

bool dp[maxn][4];
string s;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    cin >> s;
    int n = s.length();
    dp[n - 1][2] = dp[n - 1][3] = true;
    for (int covered = n - 2; covered >= 4; covered--) {
        fore(last, 2, 3) {
            fore(next, 2, 3) {
                if (dp[covered + next][next] && s.substr(covered - last + 1, last) != s.substr(covered + 1, next)) {
                    dp[covered][last] = true;
                }
            }
        }
            
    }
    set <string> ans;
    fore(start, 5, n - 2)
        fore(len, 2, 3)
            if (dp[start + len - 1][len])
                ans.insert(s.substr(start, len));
    printf("%d\n", (int)ans.size());
    for (string s : ans)
        cout << s << endl;
}
