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

const int maxn = 2e5+5;

int p[maxn];
bool mark[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    fore(j, 1, n)
        scanf("%d", &p[j]);
    int cnt = 0;
    fore(j, 1, n) if (!mark[j]) {
        int cur = j;
        cnt++;
        while(!mark[cur]) {
            mark[cur] = true;
            cur = p[cur];
        }
    }
    int s = 0;
    forn(j, n) {
        int x;
        scanf("%d", &x);
        s += x;
    }
    int ans = (cnt > 1 ? cnt : 0) + (s % 2 == 0);
    printf("%d", ans);

}
