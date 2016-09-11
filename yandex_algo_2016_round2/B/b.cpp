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

int get(int x, int bit) {
    if (x == -1)
        return 0;
    int x1 = x % (1 << (bit + 1));
    int tmp = (1 << bit);
    int cnt1 = (x1 >= tmp ? x1 - tmp + 1 : 0);
    int cnt0 = x1 + 1 - cnt1;
    return cnt1 - cnt0;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int l, r;
    scanf("%d%d", &l, &r);
    int answer = 0;
    forn(bit, 30) {
        int r1 = get(r, bit);
        int l1 = get(l - 1, bit);
        int delta = r1 - l1;
        if (delta > 0)
            answer += (1 << bit);
    }
    cout << answer;
}
