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

const int max_val = 1e6;

vi list;
vi primes;

void go(int cur, size_t step, int upd, vi& result) {
    if (step == list.size()) {
        if (upd > result[cur])
            result[cur] = upd;
        return;
    }
    go(cur * list[step], step + 1, upd, result);
    go(cur, step + 1, upd, result);
}

void build(const vi & v, vi& result) {
    result.resize(max_val + 1);
    for (int x : v) {
        list.clear();
        int cur = x;
        for (int pr : primes) {
            if (pr > cur)
                break;
            while (cur % pr == 0) {
                list.pb(pr);
                cur /= pr;
            }
        }
        if (cur > 1 || x == 1)
            list.pb(cur);
        go(1, 0, x, result);
    }
}

void precalc() {
    fore(j, 2, 1e3) {
        bool ok = true;
        for (int d = 2; d * d <= j; ++d)
            if (j % d == 0) {
                ok = false;
                break;
            }
        if (ok)
            primes.pb(j);
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    precalc();
    //int n = 5e5;
    int n;
    scanf("%d", &n);
    vi a(n);
    vi b(n);
    forn(i, n) {
        //a[i] = rand() % (int)1e6 + 1;
        scanf("%d", &a[i]);
    }
    forn(j, n) {
        //b[j] = rand() % (int)1e6 + 1;
        scanf("%d", &b[j]);
    }
    vi aprime, bprime;
    build(a, aprime);
    build(b, bprime);
    int ans = 0;
    for (int val = max_val; val >= 1; val--)
        if (aprime[val] && bprime[val]) {
            ans = aprime[val] + bprime[val];
            break;
        }
    printf("%d", ans);
}

