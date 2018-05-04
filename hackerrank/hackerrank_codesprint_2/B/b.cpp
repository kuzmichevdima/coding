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
    scanf("%d", &tests);
    forn(test, tests) {
        string s;
        cin >> s;
        bool found = false;
        fore(len, 1, s.length() / 2) {
            bool fail = false;
            i64 cur = stoll(s.substr(0, len));
            int pos = len;
            while(pos < (int)s.length()) {
                cur++;
                string str = to_string(cur);
                if (s.substr(pos, str.length()) != str) {
                    fail = true;
                    break;
                }
                pos += str.length();
            }
            if (!fail) {
                cout << "YES " << s.substr(0, len) << endl;
                found = true;
                break;
            }
        }
        if (!found)
            cout << "NO" << endl;
    }
}
