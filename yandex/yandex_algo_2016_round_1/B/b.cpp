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

const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};
const int n = 9;

int perm[10];
char a[4][4];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    forn(i, 3) {
        forn(j, 3)
            scanf("%c", &a[i][j]);
        scanf("\n");
    }
    forn(i, 9)
        perm[i] = i + 1;
    do {
        bool fail = false;
        forn(i, 9) {
            int row = i / 3;
            int column = i % 3;
            //printf("i = %d row = %d column = %d\n", i, row, column);
            if (a[row][column] != '?')
                if (a[row][column] - '0' != perm[i]) {
                    fail = true;
                    break;
                }
            bool near = (perm[i] == 1);
            forn(move, 4) {
                int newx = row + dx[move];
                int newy = column + dy[move];
                if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3 && perm[newx * 3 + newy] == perm[i] - 1) {
                    near = true;
                    break;
                }
            }
            if (!near) {
                fail = true;
                break;
            }
        }
        if (!fail) {
            forn(i, 3) {
                forn(j, 3)
                    printf("%d", perm[i * 3 + j]);
                printf("\n");
            }
            exit(0);
        }
    } while (next_permutation(perm, perm + n));
}
