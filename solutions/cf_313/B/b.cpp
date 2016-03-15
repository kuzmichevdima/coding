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

string get(string s)
{
    if (s.length() % 2 == 1)
        return s;
    string part1 = get(s.substr(0, s.length() / 2));
    string part2 = get(s.substr(s.length() / 2, s.length() / 2));
    return part1 > part2 ? part2 + part1 : part1 + part2;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    string s1, s2;
    cin >> s1 >> s2;
    string basic1 = get(s1);
    string basic2 = get(s2);
    if (basic1 == basic2)
        printf("YES");
    else printf("NO");
}
