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

const int maxn = 55;

bool a[maxn][maxn];

void fail() {
    printf("No");
    exit(0);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(i, n) {
        string s;
        cin >> s;
        forn(j, m)
            a[i][j] = (s[j] == '#');
    }
    /*forn(i, n) {
        forn(j, m)
            printf("%d", a[i][j]);
        printf("\n");
    }*/
    //vector<bool> checked(n, false);
    forn(i, n)
        forn(j, n) {
            if (i == j)
                continue;
            bool flag = false;
            bool eq = true;
            forn(col, m) {
                if (a[i][col] && a[j][col]) {
                    flag = true;
                }
                eq &= (a[i][col] == a[j][col]);
            }
            //printf("i = %d j = %d flag = %d eq = %d\n", i, j, flag, eq);
            if (flag & !eq) {
                fail();
            }
        }
    printf("Yes");
}

