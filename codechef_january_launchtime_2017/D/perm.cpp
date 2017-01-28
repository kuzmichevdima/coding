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

vi answer;
int a[maxn];
int n;

bool check(int x) {
    return x != a[x] && (x + 1) != a[x + 1] && a[x] > a[x + 1];
}

void ez_swaps() {
    while(true) {
        bool found = false;
        fore(i, 1, n - 1) {
            if (check(i) && a[i + 1] != i && a[i] != i + 1) {
                found = true;
                swap(a[i], a[i + 1]);
                answer.pb(i);
    //            printf("swap %d\n", i);
            }
        }
        if (!found)
            return;
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        scanf("%d", &n);
        fore(j, 1, n)
            scanf("%d", &a[j]);
        answer.clear();
        while(true) {
            ez_swaps();
    //        printf("ez swaps ended\n");
            bool found = false;
            for (int j = 1; j < n; j++)
                if (check(j)) {
                    swap(a[j], a[j + 1]);
                    answer.pb(j);
//                    printf("super swap %d\n", j - 1);
                    found = true;
                    break;
                }
            if (!found)
                break;
        }
        fore(j, 1, n)
            fprintf(stderr, "%d ", a[j]);
        fprintf(stderr, "\n");
        printf("%d\n", (int)answer.size());
        for (int x : answer)
            printf("%d ", x);
        printf("\n");
    }
}

