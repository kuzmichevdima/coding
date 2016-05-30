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

const int maxn =1e6+5;

int ans[maxn];
bool is_zero[maxn];

void push(int i, bool is_list) {
    tree[i] += to_add[i];
    if (!is_list) {
        to_add[i * 2] += to_add[i];
        to_add[i * 2 + 1] += to_add[i];
    }
    to_add[i] = 0;
    if (is_zero[i]) {
        if (!is_list) {
             is_zero[i * 2] = true;
             is_zero[i * 2 + 1] = true;
        }
        tree[i] = 0;
    }
    is_zero[i] = false;
}

int query(int i, int tl, int tr, int l, int r) {
    if (tl >= r || l >= tr)
        return 0;
    push(i, tl + 1 == tr);
    if (tl == l && tr == r) {
        return tree[i];
    }
    int m = (tl + tr) / 2;
    return query(i * 2, tl, m, l, min(r, m)) + query(i * 2 + 1, m, tr, max(l, m), r);
}

void add(int i, int tl, int tr, int l, int r, int val) {
    if (tl >= r || l >= tr)
        return;
    push(i, tl + 1 == tr);
    if (tl == l && tr == r)
    {
        to_add[i] += val;
        return;
    }
    int m = (tl + tr) / 2;
    add(i * 2, tl, m, l, min(r, m), val);
    add(i * 2 + 1, m, tr, max(l, m), r, val);
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &q);
    forn(j, q) {
        int a, t, x;
        scanf("%d%d%d", &a, &t, &x);
        op[x].push_back(query(a, t, j));
        times.pb(t);
        s.insert(x);
    }
    sort(times.begin(), times.end());
    times.resize(unique(times.begin(), times.end()) - times.begin());
    for (int x : s) {
        for (query q : op[x]) {
            int typ = q.typ;
            int t = lower_bound(times.begin(), times.end(), q.t) - times.begin();
            if (typ == 1) {
                add(1, 0, times.size(), t, times.size(), 1);       
            }
            else if (typ == 2){
                add(1, 0, times.size(), t, times.size(), -1);       
            }
            else ans[q.number] = get(1, 0, times.size(), t, t + 1);
        }
    }
    forn(j, q)
        printf("%d\n", ans[j]);
}
