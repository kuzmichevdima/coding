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

const int maxprof = (1 << 10);
const int maxw = 1e5+5;

vi sum[maxw], pref[maxw], a[maxw];
int w, h;
int first[maxprof + 5];
bool was[maxprof + 5];

void precalc() {
    forn(row, w) {
        sum[row].resize(h + 1);
        pref[row].resize(h + 1);
        fore(col, 1, h) {
            sum[row][col] = sum[row][col - 1] + (a[row][col - 1] != 0);
            pref[row][col] = pref[row][col - 1] ^ (1 << a[row][col - 1]);
            //printf("sum[%d][%d] = %d pref[%d][%d] = %d\n", row, col, sum[row][col], row, col, pref[row][col]);
        }
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
    scanf("%d%d", &w, &h);
    bool flag = false;
    if (h > w) {
        flag = true;
        forn(i, h)
            a[i].resize(w);
    } else {
        forn(i, w)
            a[i].resize(h);
    }
    forn(i, w)
        forn(j, h)
            if (flag)
                scanf("%d", &a[j][i]);
            else scanf("%d", &a[i][j]);
    if (flag)
        swap(w, h);
    precalc();
    int answer = 1;
    pair<pii, pii> rect;
    forn(L, h)
        fore(R, L, h - 1) {
            int non_zero = -2;
            int cur = 0;
            bool check_similar = (R - L) % 2 == 0;
            memset(was, false, sizeof(was));
            forn(i, maxprof)
                first[i] = w + 1;
            forn(i, 10)
                first[1 << i] = -1;
            first[0] = -1;
            int max_deltaw = 0, chosen;
            forn(row, w) {
                if (sum[row][R + 1] - sum[row][L])
                    non_zero = row;
                cur ^= (pref[row][R + 1] ^ pref[row][L]);
                //printf("row = %d cur = %d first = %d\n", row, cur, first[cur]);
                if (first[cur] <= non_zero && row - first[cur] > max_deltaw) {
                    max_deltaw = row - first[cur];
                    chosen = first[cur] + 1;
                }
                if (!was[cur]) {
                    was[cur] = true;
                    if (first[cur] == w + 1)
                        first[cur] = row;
                    if (check_similar) {
                        forn(i, 10) {
                            int changed = cur ^ (1 << i);
                            if (first[changed] == w + 1)
                                first[changed] = row;
                        }
                    }
                }
            }
            int new_area = max_deltaw * (R - L + 1);
            // printf("L = %d R = %d max_deltaw = %d new_area = %d from %d to %d\n", L, R, max_deltaw, new_area, chosen, chosen + max_deltaw - 1);
            //exit(0);
            if (new_area > answer) {
                answer = new_area;
                rect = mp(mp(chosen, L), mp(chosen + max_deltaw - 1, R));
            }
        }
    if (flag) {
        swap(rect.fi.fi, rect.fi.se);
        swap(rect.se.fi, rect.se.se);
    }
    printf("%d\n%d %d %d %d", answer, rect.fi.fi, rect.fi.se, rect.se.fi, rect.se.se);
}

