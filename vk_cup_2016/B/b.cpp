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

set <pair<int, string > > order;
map <string, int> prior;

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
    forn(j, n)
    {
        string s;
        cin >> s;
        if (prior.find(s) != prior.end())
        {
            order.erase(mp(prior[s], s));
        }
        int p = order.empty() ? 0 : order.begin()->fi - 1;
        order.insert(mp(p, s));
        prior[s] = p; 
    }
    for (auto iter = order.begin(); iter != order.end(); iter++)
        cout << iter->se << endl;
}
