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

char a[27], b[27];

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
        forn(j, 26)
            a[j] = b[j] = 0;
        string s, t;
        cin >> s >> t;
        bool fail = false;
        forn(j, s.length()) {
            int s1 = s[j] - 'a';
            int t1 = t[j] - 'a';
            if ((a[s1] != 0 && a[s1] != t[j]) || (b[t1] != 0 && b[t1] != s[j])) {
                fail = true;
                break;
            }
            a[s1] = t[j];
            b[t1] = s[j];
        }
        if (!fail) {
            bool found = false;
            forn(j, 26)
                if (a[j] == 0) {
                    found = true;
                    break;
                }
            if (!found)
                fail = s != t;
        }
        if (fail)
            printf("NO\n");
        else printf("YES\n");
    }
}

