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
        string s1;
        cin >> s1;
        string s = "";
        for (char c : s1)
            if (c != '=')
                s += c;
        int start = 0;
        int ans = 0;
        forn(i, s.length()) {
            if (s[i] != s[start]) {
                ans = max(ans, i - start);
                start = i;
            }
        }
        ans = max(ans, (int)s.length() - start);
        ans++;
        printf("%d\n", ans);
    }
}
