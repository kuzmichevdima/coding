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

const int maxn = 1e5+5;

i64 pref_b[maxn];
int a[maxn];
int b[maxn];
int c[maxn];
i64 eq[maxn];
int n;
i64 M;
i64 strongest[maxn];

void precalc() {
    pref_b[0] = b[0];
    fore(j, 1, n - 1)
        pref_b[j] = pref_b[j - 1] + b[j];
    forn(j, n)
        eq[j] = a[j] - (j == 0 ? 0 : pref_b[j - 1]);
    strongest[0] = eq[0];
    fore(j, 1, n - 1)
        strongest[j] = max(strongest[j - 1], eq[j]);
}

set <int> myset;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    cin >> n >> M;
    //i64 M1 = M;
    forn(j, n)
        scanf("%d%d%d", &a[j], &b[j], &c[j]);
    precalc();
    i64 answer = 0;
    while(true) {
        myset.insert(M);
        int pos = lower_bound(strongest, strongest + n, M) - strongest;
        if (pos == n) {
            answer += n;
            break;
        }
        M = max((i64)0, M + (pos == 0 ? 0 : pref_b[pos - 1]) - c[pos]);
        if (myset.find(M) != myset.end()) {
            cout << -1;
            exit(0);
        }
        answer += (pos + 1);
//        cout << "pos = " << pos << " answer = " << answer << " M = " << M << endl;
    }
    cout << answer;

/*    int answer1 = 0;
    int cur = 0;
    i64 str = M1;
    while(cur < n) {
        answer1++;
        if (str > a[cur]) {
            str += b[cur];
            cur++;
        }
        else {
            str = max((i64)0, str - c[cur]);
            cur = 0;
        }
    }
    cout << "\nanswer1 = " << answer1 << endl;*/
}
