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

string get(string s) {
    if (s.length() <= 1)
        return s;
    int pos = 0;
    fore(p, 1, (int)s.length() - 1)
        if (s[p] >= s[pos]) {
            pos = p;
        }
    return s[pos] + get(s.substr(0, pos)) + s.substr(pos + 1, -1);
}

int main() {
#ifdef LOCAL
    //freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests; 
    scanf("%d", &tests);
    fore(test, 1, tests) {
        string s;
        cin >> s;
        string ans = get(s);
        cout << "Case #" << test << ": " << ans << endl;
    }
}
