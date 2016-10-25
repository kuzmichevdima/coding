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

const int maxn = 22;

vi prec[maxn][maxn][maxn];
vi a[maxn];

inline bool check(vi & v) {
    forn(i, v.size())
        if (v[i] != i + 1)
            return false;
    return true;
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
        a[i].resize(m);
        forn(j, m)
            scanf("%d", &a[i][j]);
        forn(first, m)
            fore(second, first, m - 1) {
                prec[i][first][second] = a[i];
                swap(prec[i][first][second][first], prec[i][first][second][second]);
            }
    }
    forn(col_first, m)
        fore(col_second, col_first, m - 1) {
            bool fail = false;
            forn(row, n) {
                vi tmp = a[row];
                swap(tmp[col_first], tmp[col_second]);
                bool row_ok = false;
                forn(pos_first, m) {
                    if (row_ok)
                        break;
                    fore(pos_second, pos_first, m - 1) {
                        vi tmp2 = tmp;
                        swap(tmp2[pos_first], tmp2[pos_second]);
                        if (check(tmp2)) {
                            row_ok = true;
                            break;
                        }
                        vi tmp3 = prec[row][pos_first][pos_second];
                        swap(tmp3[col_first], tmp3[col_second]);
                        if (check(tmp3)) {
                            row_ok = true;
                            break;
                        }
                    }
                }
                if (!row_ok) {
                    fail = true;
                    break;
                }
            }
            if (!fail) {
                printf("YES");
                exit(0);
            }
        }
    printf("NO");
}
