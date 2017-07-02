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
const int maxn = 1e5 + 5;
int n;
int a[maxn];

struct Segtree {
    vector<i64> tree, result;
    Segtree() {
        tree.resize(4 * n);
    }
    void upd(int i, int L, int R, int A, int B, int change) {
        if (L >= B || A >= R)
            return;
        if (L == A && R == B) {
            tree[i] += change;
            return;
        }
        int m = (L + R) / 2;
        upd(i * 2, L, m, A, min(m, B), change);
        upd(i * 2 + 1, m, R, max(A, m), B, change);
    }
    void upd(int A, int B, int change) {
        A = max(A, 0);
        B = min(B, n);
        if (A < B)
            upd(1, 0, n, A, B, change);
    }
    void go(int i, int L, int R, i64 cur) {
        cur += tree[i];
        if (L + 1 == R) {
            result[L] = cur;
            return;
        }
        int m = (L + R) / 2;
        go(i * 2, L, m, cur);
        go(i * 2 + 1, m, R, cur);
    }
    void get_res() {
        result.resize(n);
        go(1, 0, n, 0);
    }
};

i64 get(int h) {
    Segtree delta, counters;
    forn(i, n) {
        delta.upd(h + i - a[i], i + h, - (h + i - a[i]));
        counters.upd(h + i - a[i], i + h, +1);
        delta.upd(i - h + 1, h + i - a[i], h + i - a[i]);
        counters.upd(i - h + 1, h + i - a[i], -1);
    }
    delta.get_res();
    counters.get_res();
    i64 result = inf;
    fore(j, h - 1, n - h) {
        i64 nnew = delta.result[j] + (i64)counters.result[j] * j;
        result = min(result, nnew);
    }
    return result;
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
        scanf("%d", &n);
        forn(i, n)
            scanf("%d", &a[i]);
        int start = 0;
        int finish = n / 2 + 1;
        while(finish - start >= 3) {
            int m1 = start + (finish - start) / 3;
            int m2 = finish - (finish - start) / 3;
            i64 g1 = get(m1);
            i64 g2 = get(m2);
            if (g1 < g2)
                finish = m2;
            else start = m1;
        }
        i64 answer = inf;
        fore(j, start, finish)
            answer = min(answer, get(j));
        cout << answer << endl;
    }
}
