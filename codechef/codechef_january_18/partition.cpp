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

int n;
const int P = 5;

bool trying(string& s, i64 need) {
    for (int j = n - 1; j >= 0; j--) if (s[j] == '0') {
        if (need >= j + 1) {
            need -= (j + 1);
            s[j] = '1';
        }
    }
    return need == 0;
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
        int x;
        scanf("%d%d", &x, &n);
        i64 total = (i64)n * (n + 1) / 2 - x;
        if (total % 2 == 1) {
            cout << "impossible" << endl;
            continue;
        }
        total /= 2;
        string pattern = "";
        fore(j, 1, n) {
            if (j != x)
                pattern += '0';
            else pattern += '2';
        }
        bool found = false;
        forn(prof, (1 << P)) {
            bool fail = false;
            forn(j, P)
                if ((prof & (1 << j)) && (x == j + 1 || j + 1 > n)) {
                    fail = true;
                    break;
                }
            if (fail)
                continue;
            string s = pattern;
            i64 modified = total;
            forn(j, P)
                if (prof & (1 << j)) {
                    s[j] = '1';
                    modified -= (j + 1);
                }
            bool f = trying(s, modified);
            if (f) {
                cout << s << endl;
                found = true;
                break;
            }
        }
        if (!found)
            cout << "impossible" << endl;
    }
}

