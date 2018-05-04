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

const int maxpr = 1000;

int prev[maxpr];
vi primes;
bool mark[maxpr + 5];
int last[maxpr];
int prelast[maxpr];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    fore(j, 2, maxpr)
        if (!mark[j]) {
            primes.pb(j);
            for (int i = 2 * j; i <= maxpr; i += j)
                mark[i] = true;
        }
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        int n;
        scanf("%d", &n);
        forn(j, primes.size())
            last[j] = prelast[j] = -1;
        i64 ans = 0;
        forn(j, n) {
            int x;
            scanf("%d", &x);
            bool fail = false;
            forn(idx, primes.size())
                if (x % primes[idx] == 0) {
                    if (x / primes[idx] % primes[idx] == 0) {
                        fail = true;
                        prelast[idx] = last[idx] = j;
                    } else {
                        prelast[idx] = last[idx];
                        last[idx] = j;
                    }
                }
            int bound = 0;
            forn(j, primes.size())
                bound = max(bound, prelast[j] + 1);
            if (!fail) {
                //printf("pos %d +%d\n", j, j - bound + 1);
                ans += j - bound + 1;
            }
        }
        cout << ans << endl;
    }
}

