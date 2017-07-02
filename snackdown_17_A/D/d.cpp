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

const i64 inf = 1e18;

i64 answer, sum;
vector <i64> pref;
int n;

void get(i64 x, int lower) {
    i64 nnew = x * (2 * lower - n) - 2 * pref[lower] + sum;
    //printf("x = %lld lower = %d nnew = %lld\n", x, lower, nnew);
    answer = min(answer, nnew);
}

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
        int L, A, B;
        scanf("%d%d%d%d", &n, &L, &A, &B);
        vector<i64> list(n);
        sum = 0;
        forn(j, n) {
            cin >> list[j];
        }
        sort(list.begin(), list.end());
        forn(j, n) {
            list[j] = list[j] - (i64)j * L;
            sum += list[j];
        }
        /*for (i64 x : list)
            cout << "x = " << x << endl;*/
        sort(list.begin(), list.end());
        pref.clear();
        pref.pb(0);
        fore(j, 1, n)
            pref.pb( list[j - 1] + pref.back());
        answer = inf;
        get(A, lower_bound(list.begin(), list.end(), A) - list.begin());
        get(B - L * n, lower_bound(list.begin(), list.end(), B - L * n) - list.begin());
        forn(j, n) {
            i64 x = list[j];
            if (x >= A && x <= B - L * n)
                get(x, j + 1);
        }
        cout << answer << endl;
    }
}
