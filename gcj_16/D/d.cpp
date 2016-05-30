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


bool taken[4];

int n, ans;

int a[4][4];
vi perm;

bool go(int cur) {
    if (cur == n)
        return true;
    bool machine_exists = false;
    forn(machine, n) if (a[perm[cur]][machine] && !taken[machine]) {
        machine_exists = true;
        taken[machine] = true;
        if (!go(cur + 1))
            return false;
        taken[machine] = false;
    }
    return machine_exists;
}

void educate(int i, int j, int cost) {
    if (i == n && j == 0) {
        bool fail = false;
        perm.resize(n);
        forn(j, n)
            perm[j] = j;
        do
        {
            forn(j, n)
                taken[j] = false;
            bool ok = go(0);            
            if (!ok) {
                fail = true;
                break;
            }
        }
        while(next_permutation(perm.begin(), perm.end()));
        if (!fail && cost < ans) {
            /*forn(i, n) {
                forn(j, n)
                    printf("%d ",a[i][j]);
                printf("\n");
            }*/
            ans = cost;
        }
        return;
    }
    int i1, j1;
    if (j == n - 1) {
        i1 = i + 1;
        j1 = 0;
    } else {
        i1 = i;
        j1 = j + 1;
    }
    if (a[i][j] == 0) {
        a[i][j] = 1;
        educate(i1, j1, cost + 1);
        a[i][j] = 0;
    }
    educate(i1, j1, cost);
}

int main() {
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        scanf("%d\n", &n);
        forn(i, n) {
            forn(j, n) {
                char c1;
                scanf("%c", &c1);
                a[i][j] = c1 == '1';
            }
            scanf("\n");
        }
        ans = 100500;
        educate(0, 0, 0);
        assert(ans != 100500);
        printf("Case #%d: %d\n", test + 1, ans);
    }
}
