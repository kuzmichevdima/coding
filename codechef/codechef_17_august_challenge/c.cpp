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
        int n, m;
        scanf("%d%d", &n, &m);
        vi min_sal(n);
        forn(i, n)
            scanf("%d", &min_sal[i]);
        vi offer(m), slots(m);
        forn(j, m)
            scanf("%d%d", &offer[j], &slots[j]);
        vector<string> a(n);
        forn(i, n)
            cin >> a[i];
        int employed = 0;
        i64 total_sal = 0;
        vi used(m);
        forn(i, n) {
            int best = -1;
            forn(comp, m)
                if (slots[comp] && a[i][comp] == '1' && offer[comp] >= min_sal[i] && (best == -1 || offer[comp] > offer[best])) {
                    best = comp;
                }
            if (best != -1) {
                slots[best]--;
                used[best] = true;
                total_sal += offer[best];
                employed++;
            }
        }
        int unused_cnt = 0;
        forn(j, m)
            if (!used[j])
                unused_cnt++;
        cout << employed << " " << total_sal << " " << unused_cnt << endl;
    }
}

