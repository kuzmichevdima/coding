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
    int n;
    string s;
    cin >> n >> s;
    if (s[3] >= '6')
        s[3] = '0';
    int m = (s[0] - '0') * 10 + s[1] - '0';
    if (n == 24) {
        if (m >= 24) {
            s[0] = '0';
        }
    } else {
        if (m == 0) {
            s[1] = '1';
        } else if (m > 12) {
            s[0] = '0';
        }
    }
    cout << s;
}
