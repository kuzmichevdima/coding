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

const i64 LIMIT = 1e14;

map <i64, int> M;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    i64 k;
    cin >> n >> k;
    M[0] = 1;
    i64 cur = 0;
    i64 ans = 0;
    forn(j, n) {
        int x;
        scanf("%d", &x);
        cur += x;
        i64 p = 1;
        while(true) {
            i64 need = cur - p;
            if (M.find(need) != M.end())
                ans += M[need];
            p *= k;
            if (k == 1 || p > LIMIT)
                break;
        }
        M[cur]++;
    }
    cout << ans;
}
