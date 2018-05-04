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
    int range = 1000000007;
    i64 multiplierOne = 2017;
    i64 multiplierSecond = 2027;
    i64 lastNumber = 0;
    i64 secondLastNumber = 1;
    i64 maxNum = 0;
    vi list;
    int size, queries;
    scanf("%d%d", &size, &queries);
    forn(i, size) {
        i64 newNumber = (lastNumber * multiplierOne + secondLastNumber * multiplierSecond + maxNum) % range + 1;
        maxNum = max(maxNum, newNumber);
        secondLastNumber = lastNumber;
        lastNumber = newNumber;
        list.pb(newNumber);
    }
    sort(list.begin(), list.end());
    forn(j, queries) {
        int x;
        scanf("%d", &x);
        int pos = lower_bound(list.begin(), list.end(), x) - list.begin();
        if (pos < (int)list.size() && list[pos] == x) {
            printf("YES\n");
        } else printf("NO\n");
    }
}

