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
        string s, t;
        cin >> s >> t;
        vector <bool> in_B(26);
        for (char c : t)
            in_B[c - 'a'] = true;
        vi cnt(26);
        for (char c : s)
            cnt[c - 'a']++;
        bool A_win = false;
        forn(j, 26)
            if (cnt[j] >= 2 && !in_B[j]) {
                A_win = true;
                break;
            }
        vector <bool> in_A(26);
        for (char c : s)
            in_A[c - 'a'] = true;
        int uniq_in_A = 0;
        forn(j, 26)
            if (in_A[j] && !in_B[j])
                uniq_in_A++;
        bool flag = uniq_in_A > 0;
        forn(j, 26)
            if (in_B[j] && !in_A[j]) {
                flag = false;
                break;
            }
        A_win |= flag;
        if (A_win)
            printf("A\n");
        else printf("B\n");
    }
}

