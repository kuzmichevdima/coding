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
const int int_inf = 2e9;
const int maxn = 1e5 + 5;
int n;
int a[maxn];
i64 sum;

struct Segtree {
    vi tree, result;
    Segtree() {
        tree.resize(4 * n, int_inf);
    }
    void upd(int i, int L, int R, int A, int B, int change) {
        if (L >= B || A >= R)
            return;
        if (L == A && R == B) {
            tree[i] = min(tree[i], change);
            return;
        }
        int m = (L + R) / 2;
        upd(i * 2, L, m, A, min(m, B), change);
        upd(i * 2 + 1, m, R, max(A, m), B, change);
    }
    void upd(int A, int B, int change) {
        A = max(A, 0);
        B = min(B, n);
        if (A < B) {
            //printf("upd A = %d B = %d change = %d\n", A, B, change);
            upd(1, 0, n, A, B, change);
        }
    }
    void go(int i, int L, int R, int cur) {
        cur = min(cur, tree[i]);
        if (L + 1 == R) {
            result[L] = cur;
            return;
        }
        int m = (L + R) / 2;
        go(i * 2, L, m, cur);
        go(i * 2 + 1, m, R, cur);
    }
    void get_res() {
        result.resize(n, int_inf);
        go(1, 0, n, int_inf);
    }
};


i64 get(int h) {
    //printf("\n================\nget h = %d\n", h);
    i64 cnst = (i64)h * h;
    Segtree tr_i, tr_minus_i;
    forn(j, n) {
        //tr_i.upd(j, j + h, h - a[j] + j);
        //tr_minus_i.upd(j - h + 1, j, h - a[j] - j);
        tr_minus_i.upd(j, n, a[j] - j - h);
        tr_i.upd(0, j, a[j] + j - h);
    }
    tr_i.get_res();
    tr_minus_i.get_res();
    forn(i, n) {
        //printf("tr_i[%d] = %d tr_minus_i[%d] = %d\n", i, tr_i.result[i], i, tr_minus_i.result[i]);
    }
    i64 result = inf;
    fore(i, h - 1, n - h) if (h <= a[i]) {
        //i64 nnew = pref[i - h] + suff[i + h] + sum - cnst;
        if (i <= tr_i.result[i] && -i <= tr_minus_i.result[i]) {
            i64 nnew = sum - cnst;
            result = min(result, nnew);
        }
    }
    //printf("get h = %d result = %lld\n", h, result);
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
        sum = 0;
        forn(i, n) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        /*forn(i, n)
            pref[i] = i == 0 ? a[0] : pref[i - 1] + a[i];
        for (int i = n - 1; i >= 0; i--)
            suff[i] = i == n - 1 ? a[n - 1] : suff[i + 1] + a[i];*/
        int start = 1;
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
