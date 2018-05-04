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

const int maxn = 1005;

char a[maxn][maxn];

void fail() {
    printf("NO");
    exit(0);
}

void place_hor(int curx, int cury) {
    a[curx][cury] = '<';
    a[curx][cury + 1] = '>';
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, hor, vert;
    scanf("%d%d%d%d", &n, &m, &hor, &vert);
    forn(i, n)
        forn(j, m)
            a[i][j] = '.';
    int startx = 0;
    if (n % 2 == 1) {
        int cury = 0;
        while(cury + 1 < m && hor) {
            place_hor(0, cury);
            hor--;
            cury += 2;
        }
        startx = 1;
    }
    int curx = startx;
    int cury = 0;
    forn(i, hor) {
        if (cury + 1 >= m) {
            fail();
        }
        place_hor(curx, cury);
        curx++;
        if (curx == n) {
            curx = startx;
            cury += 2;
        }
    }
    forn(i, n - 1)
        forn(j, m) {
            if (vert > 0 && a[i][j] == '.' && a[i + 1][j] == '.') {
                a[i][j] = '^';
                a[i + 1][j] = 'v';
                vert--;
            }
        }
    if (vert)
        fail();
    printf("YES\n");
    forn(i, n) {
        forn(j, m)
            printf("%c", a[i][j]);
        printf("\n");
    }
}

