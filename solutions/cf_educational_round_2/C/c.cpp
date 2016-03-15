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

int cnt[26];
int cnt1[26];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    string s;
    cin >> s;
    for (char c : s)
        cnt[c - 'a']++;
    if (s.length() % 2 == 0)
    {
        forn(i, 26) if (cnt[i] % 2 == 1)
            for (int j = 25; j > i; j--) if (cnt[j] % 2 == 1)
            {
                cnt[i]++;
                cnt[j]--;
                break;
            }
        s = "";
        forn(i, 26)
            forn(j, cnt[i] / 2)
                s += ('a' + i);
        cout << s;
        reverse(s.begin(), s.end());
        cout << s;
        exit(0);
    }
    string best = "";
    forn(chosen, 26) if (cnt[chosen] % 2 == 1)
    {
        memcpy(cnt1, cnt, sizeof(cnt));
        forn(i, 26) if (cnt[i] % 2 == 1 && i != chosen)
            for (int j = 25; j > i; j--) if (j != chosen && cnt[j] % 2 == 1)
            {
                cnt[i]++;
                cnt[j]--;
                break;
            }
        s = "";
        forn(i, 26)
            forn(j, cnt[i] / 2)
                s += ('a' + i);
        string s1 = s;
        reverse(s1.begin(), s1.end());
        s += ('a' + chosen);
        s += s1;
//        printf("chosen = %d\n", chosen);
  //      cout << s << endl;
        if (best == "" || s < best)
            best = s;
        memcpy(cnt, cnt1, sizeof(cnt));
    }
    cout << best;
}
