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
    int tests;
    scanf("%d\n", &tests);
    forn(test, tests) {
        vector<string> v;
        string s;
        getline(cin, s);
        string cur = "";
        for (char c : s) {
            if (c == ' ') {
                v.pb(cur);
                cur = "";
            } else cur += tolower(c);
        }
        v.pb(cur);
        forn(j, v.size()) {
            string tmp = "";
            tmp += toupper(v[j][0]);
            //printf("c = %c\n", c);
            if (j != (int)v.size() - 1)
                v[j] = tmp + '.';
            else v[j] = tmp + v[j].substr(1, v[j].length());
        }
        forn(j, v.size()) {
            if (j != 0)
                cout << " ";
            cout << v[j];
        }

        cout << endl;
    }
}

