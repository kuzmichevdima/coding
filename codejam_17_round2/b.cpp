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

const int maxn = 1005;

int p[maxn];
bool used[maxn];
vi v1, v2;

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    forn(opp, v2.size())
        if (v1[v] != v2[opp]) {
            if (p[opp] == -1 || dfs(p[opp])) {
                p[opp] = v;
                return true;
            }
        }
    return false;
}

int main() {
    int tests;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        cerr << "test " << test << endl;
        int n, c, tickets;
        scanf("%d%d%d", &n, &c, &tickets);
        assert(c == 2);
        v1.clear();
        v2.clear();
        forn(j, tickets) {
            int pos, num;
            scanf("%d%d", &pos, &num);
            if (num == 1)
                v1.pb(pos);
            else v2.pb(pos);
        }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        if (v1.size() < v2.size())
            swap(v1, v2);
        forn(j, v2.size())
            p[j] = -1;
        forn(j, v1.size()) {
            memset(used, false, sizeof(used));
            dfs(j);
        }
        int ans1 = v1.size();
        int ans2 = 0;
        forn(j, v2.size())
            if (p[j] == -1) {
                if (v2[j] == 1)
                    ans1++;
                else ans2++;
            }
        printf("Case #%d: %d %d\n", test, ans1, ans2);
    }
}

