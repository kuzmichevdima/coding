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

const int maxn = 105;

int mark[maxn][maxn];
vector <pair<int, pii> > cur;
vector <vector<pair<int, pii> > > answer;

void add(int person, int x, int y) {
    //printf("add person = %d first = %d second = %d\n", person, x, y);
    assert(x != y);
    mark[person][x]++;
    mark[person][y]++;
    cur.pb(mp(person, mp(x, y)));
}

void fl() {
    answer.pb(cur);
    cur.clear();
}

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
        int n;
        scanf("%d", &n);
        memset(mark, 0, sizeof(mark));
        answer.clear();
        for (int dish = 1; dish <= n - 1; dish += 2)
            for (int person = 1; person <= n - 1; person += 2) {
                if (dish == n - 2 && n % 2 == 1) {
                    if (person == n - 2) {
                        add(person, dish, dish + 1);
                        add(person + 1, dish + 1, dish + 2);
                        add(person + 2, dish + 2, dish);
                        fl();

                        add(person, dish + 1, dish + 2);
                        add(person + 1, dish + 2, dish);
                        add(person + 2, dish, dish + 1);
                        fl();

                        add(person, dish + 2, dish);
                        add(person + 1, dish, dish + 1);
                        add(person + 2, dish + 1, dish + 2);
                        fl();
                    } else {
                        add(person, dish, dish + 1);
                        add(person + 1, dish, dish + 1);
                        fl();

                        add(person, dish + 1, dish + 2);
                        add(person + 1, dish + 1, dish + 2);
                        fl();

                        add(person, dish + 2, dish);
                        add(person + 1, dish + 2, dish);
                        fl();
                    }
                } else {
                    if (person == n - 2 && n % 2 == 1) {
                        add(person, dish, dish + 1);
                        add(person + 1, dish, dish + 1);
                        fl();
                        add(person + 1, dish, dish + 1);
                        add(person + 2, dish, dish + 1);
                        fl();
                        add(person + 2, dish, dish + 1);
                        add(person, dish, dish + 1);
                        fl();
                    } else {
                        forn(iter, 2) {
                            add(person, dish, dish + 1);
                            add(person + 1, dish, dish + 1);
                            fl();
                        }
                    }
                }
            }
        for (int dish = 1; dish <= n; dish++)
            for (int j = 1; j <= n; ++j)
                assert(mark[dish][j] == 2);
        printf("%d\n", (int)answer.size());
        for (auto x : answer) {
            printf("%d\n", (int)x.size());
            for (auto y : x)
                printf("%d %d %d\n", y.first, y.second.fi, y.se.se);
        }
    }
}

