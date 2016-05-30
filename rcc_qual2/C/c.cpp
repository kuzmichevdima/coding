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

bool found;

string part[6];
int k;
string s;
int a[6];

void go(int num, int L) {
    if (found)
        return;
    if (num == k) {
        if (L != 0)
            return;
        set <string> mys;
        int start = 0;
        bool fail = false;
        forn(j, k) {
            part[j] = s.substr(start, a[j]);
            start += a[j];
            if (mys.find(part[j]) != mys.end()) {
                fail = true;
                break;
            }
            mys.insert(part[j]);
        }
        if (!fail) {
            found = true;
            printf("YES\n");
            forn(j, k)
                cout << part[j] << endl;
        }
        return;
    }
    fore(j, 1, L) {
        a[num] = j;
        go(num + 1, L - j);
    }
}

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
        cin >> s;
        scanf("%d", &k);
        if (s.length() > 14) {
            printf("YES\n");
            int start = 0;
            fore(j, 1, k - 1) {
                cout << s.substr(start, j) << endl;
                start += j;
            }
            cout << s.substr(start) << endl;
            continue;
        }
        found = false;
        go(0, s.length());
        if (!found)
            cout << "NO" << endl;
    }
}
