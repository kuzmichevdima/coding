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

char better(char c1, char c2) {
    if (c1 == 'R' && c2 == 'S') return c1;
    if (c1 == 'S' && c2 == 'P') return c1;
    if (c1 == 'P' && c2 == 'R') return c1;
    return c2;
}

typedef vector <char> vc;

int main() {
    int tests;
    scanf("%d", &tests);

    forn(test, tests) {
        printf("Case #%d: ", test + 1);
        int n, R, P, S;
        scanf("%d%d%d%d", &n, &R, &P, &S);
        vc a;
        forn(p, P)
            a.pb('P');
        forn(r, R)
            a.pb('R');
        forn(s, S)
            a.pb('S');
        bool found = false;
        do
        {
            vc b = a;
            bool fail = false;
            forn(it, n) {
                vc c;
                for (int pos = 0; pos + 1 < (int)b.size(); pos += 2) {
                    if (b[pos] == b[pos + 1]) {
                        fail = true;
                        break;
                    }
                    c.pb(better(b[pos], b[pos + 1]));
                }
                if (fail)
                    break;
                b = c;
            }
            if (!fail) {
                for (auto c : a)
                    printf("%c", c);
                found = true;
                break;
            }
        }
        while(next_permutation(a.begin(), a.end()));
        if (!found)
            printf("IMPOSSIBLE");
        printf("\n");
    }
}
