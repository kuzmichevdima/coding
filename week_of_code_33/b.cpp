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
        string s;
        cin >> s;
        int start = -1;
        int answer = 0;
        forn(i, s.length()) {
            if (s[i] == '0') {
                if (start == -1)
                    start = i;
                if (i + 1 != (int)s.length() && s[i + 1] != '0') {
                    if (start != 0 && s[start - 1] == '1' && s[i + 1] == '1')
                        answer++;
                }
            } else {
                start = -1;
            }
        }
        printf("%d\n", answer);
    }
}

