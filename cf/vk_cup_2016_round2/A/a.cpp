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

const int maxn = 1e5+5;

set <int> S;

int a[maxn];

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
    string str;
    cin >> str;
    forn(j, n)
        scanf("%d", &a[j]);
    int cur = 0;
    while (true) {
        if (S.find(cur) != S.end()) {
            cout << "INFINITE";
            exit(0);
        }
        S.insert(cur);
        if (str[cur] == '>')
            cur += a[cur];
        else cur -= a[cur];
        if (cur < 0 || cur >= n) {
            cout << "FINITE";
            exit(0);
        }
    }
}
