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

const int MOD = 1e9+7;
const int maxn = 1e5 + 5;
int tree[maxn * 4];
i64 fact[maxn];

void add(int & x, int y) {
    x = (x + y) % MOD;
}

int get(int i, int L, int R, int A, int B) {
    if (A >= R || L >= B)
        return 0;
    if (A == L && B == R)
        return tree[i];
    int middle = (L + R) / 2;
    return get(i * 2, L, middle, A, min(middle, B)) +
        get(i * 2 + 1, middle, R, max(middle, A), B);
}

void upd(int i, int L, int R, int pos) {
    if (L + 1 == R) {
        tree[i]--;
        return;
    }
    int middle = (L + R) / 2;
    if (pos < middle)
        upd(i * 2, L, middle, pos);
    else upd(i * 2 + 1, middle, R, pos);
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void build(int i, int L, int R) {
    tree[i] = R - L;
    if (L + 1 == R)
        return;
    int m = (L + R) / 2;
    build(i * 2, L, m);
    build(i * 2 + 1, m, R);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    fact[0] = 1;
    fore(j, 1, maxn - 1)
        fact[j] = fact[j - 1] * j % MOD;
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n;
        scanf("%d", &n);
        build(1, 1, n + 1);
        int answer = 1;
        forn(j, n) {
            int x;
            scanf("%d", &x);
            int g = get(1, 1, n + 1, 1, x);
            //printf("x = %d g = %d\n", x, g);
            add(answer, fact[n - j - 1] * g % MOD);
            upd(1, 1, n + 1, x);
        }
        printf("%d\n", answer);
    }
}
