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

set <int> s1, s2;

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
    i64 ans = 0;
    forn(j, n) {
        int x;
        scanf("%d", &x);
        if (!s1.empty() && x > *s1.rbegin()) {
//            printf("add %d to second half\n", x);
            s2.insert(x);
            if (s2.size() > s1.size()) {
                s1.insert(*s2.begin());
                s2.erase(s2.begin());
            }
        } else {
  //          printf("add %d to first half\n", x);
            s1.insert(x);
            if (s1.size() > s2.size() + 1) {
                s2.insert(*s1.rbegin());
                s1.erase(*s1.rbegin());
            }
        }
    //    cout << "ans+= " << *s1.rbegin() << endl;
        ans += *s1.rbegin();
    }
    cout << ans;
}
