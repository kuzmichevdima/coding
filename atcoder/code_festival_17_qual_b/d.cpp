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

int ans = 0;
string part;

bool check(int middle) {
    return middle >= 1 && middle <= (int)part.length() - 2 && part[middle] == '0' && part[middle - 1] == '1' && part[middle + 1] == '1';
}

void change(int middle) {
    part[middle - 1] = part[middle + 1] = '0';
    part[middle] = '1';
    ans++;
}

void work_with() {
    cerr << part << " ";
    /*int lower = 1;
    int upper = (int)part.length() - 2;
    while(upper >= 1 || lower <= (int)part.length() - 2) {
        if (check(lower)) {
            change(lower);
            lower--;
            continue;
        } else lower++;
        if (check(upper)) {
            change(upper);
            upper++;
            continue;
        } else upper--;
    }*/
    while(part.size() && part[(int)part.length() - 1] == '0')
        part = part.substr(0, (int)part.length() - 1);
    int lower = 0;
    while(lower < (int)part.length() && part[lower] == '1')
        lower++;
    if (lower == (int)part.length())
        return;
    int upper = 0;
    while(upper < (int)part.length() && part[(int)part.length() - upper - 1] == '1')
        upper++;
    int cnt = 0;
    for (char c : part)
        if (c == '1')
            cnt++;
    ans += cnt - min(lower, upper);
    cerr << ans << endl;
}

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
    string s;
    cin >> s;
    part = "";
    for (char c : s) {
        part += c;
        if (part.length() >= 2 && part.substr(part.length() - 2, 2) == "00") {
            work_with();
            part = "";
        }
    }
    work_with();
    printf("%d", ans);
}

