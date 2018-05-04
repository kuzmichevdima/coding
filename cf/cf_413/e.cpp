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

const int maxn = 2e5+5;
const i64 inf = 1e18;
typedef vector<i64> vi64;

i64 sum = 0;
multiset <int> S1, S2;
int cost[maxn];
bool liked1[maxn];
bool liked2[maxn];

inline void add(int x) {
    S2.insert(x);
}

inline i64 get(int cnt) {
    if (cnt > (int)S1.size() + (int)S2.size())
        return inf;
    while((int)S1.size() < cnt) {
        int x = *S2.begin();
        S2.erase(S2.begin());
        S1.insert(x);
        sum += x;
    }
    while(cnt < (int)S1.size()) {
        int val = *S1.rbegin();
        sum -= val;
        S1.erase(S1.find(val));
        S2.insert(val);
    }
    return sum;
}

inline void prec(vi & v, vi64 & result) {
    result.pb(0);
    for (int x : v)
        result.pb(result.back() + x);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    fore(j, 1, n)
        scanf("%d", &cost[j]);
    int l;
    scanf("%d", &l);
    forn(j, l) {
        int x;
        scanf("%d", &x);
        liked1[x] = true;
    }
    scanf("%d", &l);
    forn(j, l) {
        int x;
        scanf("%d", &x);
        liked2[x] = true;
    }
    vi only1, only2, both, nobody;
    fore(j, 1, n) {
        if (liked1[j]) {
            if (liked2[j]) {
                both.pb(cost[j]);
            } else {
                only1.pb(cost[j]);   
            }
        } else {
            if (liked2[j])
                only2.pb(cost[j]);
            else nobody.pb(cost[j]);
        }
    }
    sort(both.begin(), both.end());
    sort(only1.begin(), only1.end());
    sort(only2.begin(), only2.end());
    sort(nobody.begin(), nobody.end());

    vi64 sum_both, sum_only1, sum_only2;
    prec(both, sum_both);
    prec(only1, sum_only1);
    prec(only2, sum_only2);

    for (int x : nobody)
        add(x);
    fore(j, k, (int)only1.size() - 1)
        add(only1[j]);
    fore(j, k, (int)only2.size() - 1)
        add(only2[j]);
    i64 ans = inf;
    fore(x, 0, min(m, (int)both.size())) {
        int first_part = x;
        if (k - x > (int)only1.size() || k - x > (int)only2.size())
            continue;
        if (k - x > 0)
            first_part += 2 * (k - x);
        //printf("x = %d first_part = %d\n", x, first_part);
        if (first_part <= m) {
            i64 nnew = sum_both[x];
            if (k - x > 0)
                nnew += sum_only1[k - x] + sum_only2[k - x];
            i64 addit = get(m - first_part);
            if (addit != inf) {
                nnew += addit;
                ans = min(ans, nnew);
            }
        }
        if (k - x - 1 >= 0 && k - x - 1 < (int)only1.size())
            add(only1[k - x - 1]);
        if (k - x - 1 >= 0 && k - x - 1 < (int)only2.size())
            add(only2[k - x - 1]);
    }
    if (ans == inf)
        ans = -1;
    cout << ans;
}

