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

const int maxn = 1e5+5;

set <int> order;
multiset <i64> values;

int del[maxn];
int a[maxn];
i64 val[maxn];
i64 ans[maxn];
int e[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    fore(i, 1, n)
        scanf("%d", &a[i]);
    forn(i, n) {
        scanf("%d", &del[i]);
    }
    for (int q = n - 1; q >= 0; q--) {
        int x = del[q];
        auto next = order.upper_bound(x);
        auto prev = next;
        if (next == order.begin())
            prev = order.end();
        else {
            prev--;
        }
        if (prev != order.end() && (e[*prev] + 1) != x)
            prev = order.end();
        if (next != order.end() && *next != x + 1)
            next = order.end();
        //printf("position = %d prev = %d next = %d\n", x, prev == order.end() ? -1 : *prev, next == order.end() ? -1 : *next);
        if (prev == order.end()) {
            if (next == order.end()) {
                order.insert(x);
                e[x] = x;
                val[x] = a[x];
                values.insert(val[x]);
            } else {
                order.erase(x + 1);
                values.erase(values.find(val[x + 1]));

                order.insert(x);
                e[x] = e[x + 1];
                val[x] = val[x + 1] + a[x];
                values.insert(val[x]);
            }
        } else {
            if (next == order.end()) {
                e[*prev]++;

                values.erase(values.find(val[*prev]));
                val[*prev] += a[x];
                values.insert(val[*prev]);
            } else {
                e[*prev] = e[*next];
                values.erase(values.find(val[*prev]));
                val[*prev] += val[*next] + a[x];
                order.erase(next);
                values.insert(val[*prev]);
            }
        }
        ans[q] = *values.rbegin();

    }
    fore(q, 1, n)
        cout << ans[q] << endl;
}
