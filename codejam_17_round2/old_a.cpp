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

int cnt[5];
vi v;

void add(int x) {
    v.pb(x);
    cnt[x]--;
}

int main() {
    int tests;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        int n, p;
        scanf("%d%d", &n, &p);
        memset(cnt, 0, sizeof(cnt));
        forn(j, n) {
            int x;
            scanf("%d", &x);
            cnt[x % p]++;
        }
        int ans = cnt[0];
        v.clear();
        if (cnt[0] != n) {
            if (p == 2) {
                int s = 0;
                forn(j, cnt[1]) {
                    v.pb(1);
                    if (s % 2 == 0)
                        ans++;
                    s++;
                }
            } else {
                if (cnt[2] != 0) {
                    add(2);
                }
                else {
                    add(1);
                }
                int s = 0;
                while(true) {
                    if (s % 3 == 0)
                        ans++;
                    s += v.back();
                    if (s % 3 == 0 || s % 3 == 1) {
                        if (cnt[2] > 0) {
                            add(2);
                        } else if (cnt[1] > 0) {
                            add(1);
                        } else break;
                    } else {
                        if (cnt[1] > 0)
                            add(1);
                        else if (cnt[2] > 0)
                            add(2);
                        else break;
                    }
                }
            }
        }
        printf("Case #%d: %d\n", test, ans);
    }
}

