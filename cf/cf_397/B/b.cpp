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
    string s;
    cin >> s;
    vi first(26);
    forn(p, s.length()) {
        char c = s[p];
        if (first[c - 'a'] == 0)
            first[c - 'a'] = p + 1;
    }
    forn(i, 26)
        fore(j, i + 1, 25)
            if (first[j] < first[i] && first[j] != 0) {
                printf("NO");
                exit(0);
            }
    int maxx = -1;
    forn(i, 26)
        if (first[i] != 0)
            maxx = i;
    forn(i, maxx)
        if (first[i] == 0) {
            printf("NO");
            exit(0);
        }
    printf("YES");
}
