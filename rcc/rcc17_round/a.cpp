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

const int maxpr = 4e4;
int a[2];
int cnt[2];
vi primes;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    fore(i, 2, maxpr) {
        bool fail = false;
        for (int j = 2; j * j <= i; ++j)
            if (i % j == 0) {
                fail = true;
                break;
            }
        if (!fail)
            primes.pb(i);
    }
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        scanf("%d%d", &a[0], &a[1]);
        vi v;
        for (int prime : primes) {
            cnt[0] = cnt[1] = 0;
            forn(i, 2)
                while(a[i] % prime == 0) {
                    cnt[i]++;
                    a[i] /= prime;
                }
            if ((cnt[0] + cnt[1]) % 2 == 1)
                v.pb(prime);
        }
        if (a[0] != 1) {
            if (a[1] != 1) {
                if (a[0] != a[1]) {
                    v.pb(a[0]);
                    v.pb(a[1]);
                }
            } else
                v.pb(a[0]);
        } else if (a[1] != 1)
            v.pb(a[1]);
        i64 best = -1, ans1, ans2;
        forn(prof, (1 << v.size())) {
            i64 m1 = 1;
            i64 m2 = 1;
            forn(j, v.size())
                if (prof & (1 << j))
                    m1 *= v[j];
                else m2 *= v[j];
            i64 nnew = m1 + m2;
            if (best == -1 || nnew < best) {
                best = nnew;
                ans1 = m1;
                ans2 = m2;
            }
        }
        cout << ans1 << " " << ans2 << endl;
    }
}

