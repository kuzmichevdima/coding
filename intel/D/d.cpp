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

const int maxn = 50005;

set <int> ans;
int n;
int a[maxn];

bool check(int m) {
    ans.clear();
    for(int j = n - 1; j >= 0; j--) {
        int x = a[j];
        while(x > m)
            x /= 2;
        while(x > 0 && ans.find(x) != ans.end()) {
            x /= 2;    
        }
        if (x == 0)
            return false;
        ans.insert(x);
    }
    return true;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    scanf("%d", &n);
    forn(j, n)
        scanf("%d", &a[j]);
    sort(a, a + n);
    int s = 1;
    int f = 1e9;
    while (s < f) {
        int m = (s + f) / 2;
        if (check(m)) {
            f = m;
        }
        else s = m + 1;
    }
    check(s);
    for (int x : ans)
        printf("%d ", x);
}
