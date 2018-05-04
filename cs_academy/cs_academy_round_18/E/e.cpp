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

bool dp[maxn][10];
short int mv[maxn][10];
int a[maxn];

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
    forn(j, n - 1)
        scanf("%d", &a[j]);
    forn(d, 10)
        dp[n - 1][d] = true;
    for (int pos = n - 2; pos >= 0; pos--)
        forn(digit, 10) {
            int lower, upper;
            if (a[pos] == 1) {
                upper = digit - 1;
                lower = 0;
            } else if (a[pos] == 0) {
                lower = digit;
                upper = digit;
            } else {
                lower = digit + 1;
                upper = 9;
            }
            for (int next = upper; next >= lower; next--) {
                if (dp[pos + 1][next]) {
                    dp[pos][digit] = true;
                    mv[pos][digit] = next;
                    break;
                }
            }
        }
    int cur = -1;
    for (int first = 9; first > 0; first--)
        if (dp[0][first]) {
            cur = first;
            break;
        }
    if (cur == -1) {
        printf("-1");
        exit(0);
    }
    forn(pos, n) {
        printf("%d", cur);
        cur = mv[pos][cur];
    }

}
