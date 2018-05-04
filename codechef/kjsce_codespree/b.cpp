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

#define UP 1
#define DOWN 0

const int maxn = 1e6+5;
i64 dp[maxn][2];
i64 a[maxn][2];
int diff[maxn];
int first, n;

i64 ez() {
    i64 result = -1;
    a[0][0] = first;
    forn(prof, (1 << (n - 1))) {
        forn(j, n - 1)
            if ((prof & (1 << j)) || first - diff[j] < 0) {
                a[j + 1][0] = first + diff[j];
                //printf("+ ");
            }
            else {
                
                a[j + 1][0] = first - diff[j];
             //   printf("- ");
            }
        i64 nnew = 0;
        forn(j, n - 1)
            nnew += abs(a[j][0] - a[j + 1][0]);
        //cout << nnew << " " << first - diff[0] << endl;
        /*forn(j, n)
            cout << a[j][0] << " ";
        cout << endl;*/
        if (nnew > result) {
            result = nnew;
        }
    }
    return result;
}

//const int mod = 1e9;

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
        //n = rand() % 25 + 1;
        //first = rand() % mod;
        scanf("%d%d", &n, &first);
        forn(j, n - 1)
            scanf("%d", &diff[j]);
            //diff[j] = rand() % mod;
        //printf("n = %d first = %d\n", n, first);
        /*forn(j, n - 1)
            printf("diff[%d] = %d\n", j, diff[j]);*/
        a[0][UP] = a[0][DOWN] = first;
        fore(i, 1, n - 1) {
            a[i][DOWN] = (i64)first - diff[i - 1];
            a[i][UP] = (i64)first + diff[i - 1];
        }
        dp[0][DOWN] = dp[0][UP] = 0;
        //printf("n = %d\n", n);
        fore(i, 1, n - 1) {
            forn(j, 2) {
                if (j == DOWN && a[i][DOWN] < 0) {
                    dp[i][DOWN] = -1;
                    continue;
                }
                dp[i][j] = dp[i - 1][UP] + abs((i64)a[i - 1][UP] - a[i][j]);
                if (a[i - 1][DOWN] >= 0)
                    dp[i][j] = max(dp[i][j], dp[i - 1][DOWN] + abs((i64)a[i - 1][DOWN] - a[i][j]));
                //cout << "dp[" << i << "][" << j << " " << dp[i][j] << endl;
            }
        }
        i64 dp_ans = max(dp[n - 1][DOWN], dp[n - 1][UP]);
        /*i64 ez_ans = ez();
        printf("dp ans %lld ez ans %lld\n", dp_ans, ez_ans);
        assert(dp_ans == ez_ans);*/
        cout << dp_ans << endl;
    }
}

