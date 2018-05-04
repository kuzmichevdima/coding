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
    int n;
    scanf("%d", &n);
    set<string> S;
    forn(j, n) {
        string s;
        cin >> s;
        S.insert(s);
    }
    int queries;
    scanf("%d", &queries);
    forn(j, queries) {
        string t;
        cin >> t;
        bool found = false;
        for (const string s : S)
            if (s.substr(0, t.length()) == t) {
                cout << s << endl;
                found = true;
            }
        if (!found) {
            printf("No suggestions\n");
            S.insert(t);
        }
    }
}

