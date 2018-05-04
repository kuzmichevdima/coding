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

int main() {
    int n;
    scanf("%d\n", &n);
    forn(i, n) {
        forn(j, n) {
            char c;
            scanf("%c", &c);
            a[i][j] = c == '.';
        }
        scanf("\n");
    }
    int best = 0;
    forn(i, n)
        forn(j, n) if (a[i][j]) {
            int limit = min(min(i, j), min(n - i - 1, n - j - 1));
            if (limit <= best)
                continue;
            int s = 0;
            int f = limit;
            while (s < f) {
                int m = (s + f) / 2 + 1;
                bool ok = true;
                forn(x, n)
                    forn(y, n) if (!a[x][y] && ((i - x) * (i - x) + (j - y) * (j - y) <= m * m)) {
                        ok = false;
                        break;
                    }
                if (ok)
                    s = m;
                else f = m - 1;
            }
            best = max(best, s);
        }
    printf("%d", best);
}

