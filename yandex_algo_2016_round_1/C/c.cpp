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

const int n = 10;
const int bonus[31] = {-1, 100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

int delta[n];

int get_bonus(int x) {
    return x <= 30 ? bonus[x] : 0;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    forn(j, n)
        scanf("%d", &delta[j]);
    for (int place = 1000; place >= 1; place--) {
        int pointer = 1001;
        int score = get_bonus(place);
        bool ok = false;
        forn(pretender, 10) {
            pointer--;
            while(pointer > 0) {
                if (pointer == place) {
                    pointer--;
                    continue;
                }
                if (delta[pretender] + get_bonus(pointer) >= score) {
                    break;
                }
                pointer--;
            }
            if (pointer <= 0) {
                ok = true;
                break;
            }
        }
        if (ok) {
            printf("%d\n", place);
            exit(0);
        }
    }
    printf("0");
}
