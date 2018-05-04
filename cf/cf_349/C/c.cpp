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

const int maxn = 1e5;
const int MOD = 1e9+7;

int ans[maxn + 5];
i64 p_25[maxn + 5];
i64 p_26[maxn + 5];
i64 fact[maxn + 5];
i64 rev_25[maxn + 5];
i64 rev_26[maxn + 5];
i64 rev_fact[maxn + 5];
vector <pii> queries[maxn + 5];
i64 sum[maxn + 5];

int binpow(int x, int p) {
    if (p == 0)
        return 1;
    i64 y = binpow(x, p / 2);
    y = y * y % MOD;
    if (p & 1)
        y = y * x % MOD;
    return y;
}

int rev(int x) {
    return binpow(x, MOD - 2);
}

void precalc() {
    p_25[0] = 1;
    p_26[0] = 1;
    fore(i, 1, maxn) {
        p_25[i] = (p_25[i - 1] * 25) % MOD;
        p_26[i] = (p_26[i - 1] * 26) % MOD;
    }
    fact[0] = 1;
    fore(i, 1, maxn) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    fore(i, 0, maxn) {
        rev_25[i] = rev(p_25[i]);
        rev_26[i] = rev(p_26[i]);
        rev_fact[i] = rev(fact[i]);
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
    int m;
    scanf("%d", &m);
    string s;
    cin >> s;
    int q_i = 0;
    vi slen;
    forn(i, m) {
        int typ;
        scanf("%d", &typ);
        if (typ == 1)
            cin >> s;
        else {
            int n;
            scanf("%d", &n);
            queries[s.length()].pb(mp(n, q_i));
            q_i++;
            slen.pb(s.length());
        }
    }
    sort(slen.begin(), slen.end());
    slen.resize(unique(slen.begin(), slen.end()) - slen.begin());
    precalc();
    forn(i, slen.size()) {
        int L = slen[i];
        memset(sum, 0, sizeof(sum));
        fore(x, L, maxn) {
            i64 new_val = p_25[x - L] * rev_26[x] % MOD * fact[x - 1] % MOD * rev_fact[x - L] % MOD;
            sum[x] = (sum[x - 1] + new_val) % MOD;
        }
        for (pii p : queries[L]) {
            int n = p.fi;
            ans[p.se] = p_26[n] * rev_fact[L - 1] % MOD * sum[n] % MOD;
        }
    }
    forn(i, q_i)
        printf("%d\n", ans[i]);
}
