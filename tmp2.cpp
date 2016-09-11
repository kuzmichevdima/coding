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

const int MOD = 1e9+7;
const int maxn = 202;
typedef int myarray[maxn][maxn][101];

inline void add(int & x, int y) {
    x += y;
    if (x >= MOD)
        x -= MOD;
}

int n;
int ans;

/*void add_ans(myarray & a) {
    forn(i, n)
        fore(j, i, n - 1)
            add(ans, a[i][j][0]);
}*/

myarray dp0, dp1, dp2;

int prec[maxn];

int a[maxn];

void solve() {
    fore(len, 1, n - 2) {
        for (int i = n - 1; i >= 0; i--)
            for (int j = i + len - 1; j < n; j++)
                forn(diff, 101) if (dp0[i][j][diff] != 0) {
                    /*if (i > 0) {
                        add(dp0[i - 1][j][diff], dp0[i][j][diff]);
                    }
                    if (j < n - 1) {
                        add(dp0[i][j + 1][diff], dp0[i][j][diff]);
                    }*/
                        add(dp0[i][j][diff], dp0[i + 1][j][diff]);
                        add(dp0[i][j][diff], dp0[i][j - 1][diff]);
                    add(dp0[i][j][diff], MOD - dp0[i + 1][j - 1][diff]);
                    if (i > 0 && j < n - 1 && a[i - 1] == a[j + 1]) {
                        printf("len = %d i = %d j = %d diff = %d dp0 = %d new digits = %d\n", len, i, j, diff, dp0[i][j][diff], a[i - 1]);
                        int new_diff = (diff * 10 + a[j + 1] + a[i - 1] * prec[len + 2]) % 101;
//                        dp2[i - 1][j + 1][new_diff] = (dp2[i - 1][j][new_diff] + dp2[i][j + 1][new_diff] - dp2[i][j][new_diff] + MOD) % MOD;
                        add(dp2[i - 1][j + 1][new_diff], dp0[i][j][diff]);
                        if (new_diff == 0) {
                            printf("adding %d\n", dp0[i][j][diff]);
                            add(ans, dp0[i][j][diff]);
                        }
                    }
  //                  printf("len = %d i = %d j = %d diff = %d dp0 = %d\n", len, i, j, diff, dp0[i][j][diff]);
                }
        //add_ans(dp0);
        memcpy(dp0, dp1, sizeof(dp0));
        memcpy(dp1, dp2, sizeof(dp1));
        memset(dp2, 0, sizeof(dp2));
    }
//    add_ans(dp0);
  //  add_ans(dp1);
}

int ez_ans = 0;

void ez(int pos, string s, int m) {
    if (pos == n) {
        if (m != 0 || s == "")
            return;
        string s1 = s;
        reverse(s1.begin(), s1.end());
        if (s1 == s) {
            ez_ans++;
            cout << "s = " << s << endl;
        }
        return;
    }
    ez(pos + 1, s + (char)('0' + a[pos]), (m * 10 + a[pos]) % 101);
    ez(pos + 1, s, m);
}

int main() {
    freopen("inp", "r", stdin);
    scanf("%d\n", &n);
    forn(j, n) {
        char c;
        scanf("%c", &c);
        a[j] = c - '0';
    }
    prec[1] = 1;
    fore(j, 2, n)
        prec[j] = prec[j - 1] * 10 % 101;
    forn(i, n) {
        dp0[i][i][a[i]] = 1;
        if (a[i] == 0)
            ans++;
    }
    forn(i, n)
        fore(j, i + 1, n - 1) if (a[i] == a[j]) {
            dp1[i][j][(a[i] * 10 + a[i]) % 101] = 1;
            if (a[i] == 0)
                add(ans, 1);
        }
    //printf("befor solve ans = %d\n", ans);
    solve();
    printf("%d\n", ans);
    ez(0, "", 0);
    printf("ez_ans = %d\n", ez_ans);
}
