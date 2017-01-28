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

const int maxn = 1000;

int a[maxn];
int tests;

int main() {
    scanf("%d", &tests);
    forn(test, tests) {
        int n;
        scanf("%d", &n);
        forn(j, n)
            scanf("%d", &a[j]);
        sort(a, a + n);
        int cur_max = n - 1;
        int cur_min = 0;
        int ans = 0;
        while(cur_max >= cur_min) {
            int chosen = a[cur_max];
            int cnt = 50 / chosen;
            if (50 % chosen != 0)
                cnt++;
            if (cnt > cur_max - cur_min + 1)
                break;
            cur_max--;
            cur_min += cnt - 1;
            ans++;
        }
        printf("Case #%d: %d\n", test + 1, ans);
    }
}

