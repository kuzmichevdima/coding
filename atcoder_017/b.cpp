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
    i64 n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    i64 diff = b - a;
    forn(x, n) {
        i64 y = n - 1 - x;
        i64 lower = x * c - y * d;
        i64 upper = x * d - y * c;
        //cout << lower << " " << upper << endl;
        if (diff >= lower && diff <= upper) {
            printf("YES");
            exit(0);
        }
    }
    printf("NO");
}

