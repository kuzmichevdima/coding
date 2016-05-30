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
    int n;
    scanf("%d", &n);
    vi a(n);
    forn(j, n)
        scanf("%d", &a[j]);
    i64 ans = 0;
    forn(i, n) {
        int cur = a[i];
        fore(j, i, n - 1) {
            cur = min(cur, a[j]);
            ans = max(ans, (i64)cur * (j - i + 1));
        }
    }
    cout << ans << endl;
}

