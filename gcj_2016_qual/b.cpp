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
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        string s;
        cin >> s;
        int n = s.length();
        queue <string> Q;
        map <string, int> d;
        string start = "";
        forn(j, n)
            start += '+';
        Q.push(start);
        d[start] = 0;
        while(d.find(s) == d.end()) {
            string v = Q.front();
            Q.pop();
            forn(pos, n) {
                string cp = v;
                fore(j, 0, pos / 2)
                    swap(cp[j], cp[pos - j]);
                fore(j, 0, pos)
                    cp[j] = (cp[j] == '+' ? '-' : '+');
                if (d.find(cp) == d.end()) {
                    d[cp] = d[v] + 1;
                    Q.push(cp);
                }
            }
        }
        printf("Case #%d: %d\n", test, d[s]);
    }
}

