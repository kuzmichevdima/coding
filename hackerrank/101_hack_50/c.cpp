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

i64 solve(string s) {
    int n = s.length();
    i64 ans = (n + 1) * n / 2;
    forn(i, n)  {
        string t = s.substr(i, s.length());
        vi pref(t.length());
        int k = 0;
        fore(j, 1, (int)t.length() - 1) {
            while(k > 0 && t[j] != t[k]) {
                k = pref[k - 1];
            }
            if (t[j] == t[k])
                k++;
            pref[j] = k;
        }
        forn(j, t.length()) {
            vi list;
            int cur = pref[j];
            while(cur > 0) {
                list.pb(cur);
                cur = pref[cur - 1];
            }
            reverse(list.begin(), list.end());
            /*printf("i = %d j = %d list:\n", i, j);
            for (int x : list)
                printf("%d\n", x);*/
            int pointer = 0;
            for (int idx = (int)list.size() - 1; idx >= 0; idx--) {
                while(pointer < (int)list.size() && list[pointer] < j + 1 - list[idx])
                    pointer++;
                if (pointer < (int)list.size() && list[pointer] + list[idx] == j + 1)
                    ans += 2;
            }
        }
        //printf("after i = %d ans = %lld\n", i, ans);
    }
    return ans;
}

int ez_solve(string s) {
    int result = (int)s.length() * ((int)s.length() + 1) / 2;
    forn(i, s.length())
        fore(j, 1, s.length() - i) {
            string t = s.substr(i, j);
            fore(l, 1, (int)t.length() - 1)
                if (t.substr(0, l) == t.substr(t.length() - l, l)
                        && t.substr(l, t.length()) == t.substr(0, t.length() - l)) {
                    //printf("i = %d j = %d  l =%d\n", i, j, l);
                    result += 2;
                }
        }
    return result;
}

void first() {
    string s;
    cin >> s;
    i64 ans = solve(s);
    /*int right_ans = ez_solve(s);
    cout << "s = " << s << endl;
    printf("%lld and %d\n", ans, right_ans);
    assert(ans == right_ans);*/
    cout << ans;

}

void second() {
    int cnt = 0;
    while(true) {
        string s = "";
        forn(j, 7)
            s += 'a' + rand() % 4;
        cout << s << endl;
        i64 ans = solve(s);
        int right_ans = ez_solve(s);
        printf("test %d: %lld and %d\n", cnt, ans, right_ans);
        fflush(stdout);
        assert(ans == right_ans);
        cnt++;
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
    first();
 //   second(); 
}

