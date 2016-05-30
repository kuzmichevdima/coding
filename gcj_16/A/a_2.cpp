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


typedef vector <char> vc;

const char symb[3] = {'P', 'R', 'S'};
const int need[3] = {1, 2, 0};

vc dp[15][3];

int main() {
    int tests;
    scanf("%d", &tests);
        forn(i, 3) {
            dp[0][i].pb(symb[i]);
        }
    fore(level, 1, 12)
            forn(i, 3) {
//                printf("level = %d i = %d\n", level, i);
                vc A = dp[level - 1][i];
                vc B = dp[level - 1][need[i]];
                vc AB = A;
                AB.insert(AB.end(), B.begin(), B.end());
                vc BA = B;
                BA.insert(BA.end(), A.begin(), A.end());
                dp[level][i] = min(AB, BA);
  /*              for (char c : dp[level][i])
                    printf("%c", c);
                printf("\n");*/
            }

    forn(test, tests) {
        printf("Case #%d: ", test + 1);
        int n, P, R, S;
        scanf("%d%d%d%d", &n, &R, &P, &S);
        assert(n <= 12);
        vc ans;
        bool found = false;
        forn(i, 3) {
            int R1 = R;
            int P1 = P;
            int S1 = S;
            for (char c : dp[n][i]) {
                if (c == 'R')
                    R1--;
                if (c == 'P')
                    P1--;
                if (c == 'S')
                    S1--;
            }
            if (S1 == 0 && R1 == 0 && P1 == 0) {
                if (!found || ans > dp[n][i]) {
                    found = true;
                    ans = dp[n][i];
                }
            }
        }
        if (!found)
            printf("IMPOSSIBLE");
        else {
            for (char c : ans)
                printf("%c", c);
        }
        printf("\n");
    }
}
