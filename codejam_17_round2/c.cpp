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

const int maxc = 55;
const int maxpr = 33;

bool dp[maxc][maxpr];
pii fr[maxc][maxpr];
string s[maxc];
vector <pii> valid[maxc];
bool is_laser[maxc][maxc];

int main() {
    int tests;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        int n, m;
        scanf("%d%d", &n, &m);
        forn(i, n)
            cin >> s[i];
        forn(i, n)
            forn(j, m)
                is_laser[i][j] = s[i][j] == '-' || s[i][j] == '|';
        forn(col, m) {
            valid[col].clear();
            forn(horiz, 1 << n)  {
                bool fail = false;
                int second = 0;
                forn(row, n)
                    if ((horiz & (1 << row)) && (!is_laser[row][col])) {
                        fail = true;
                    }
                if (fail)
                    continue;
                forn(row, n) if (((horiz & (1 << row)) == 0) && (is_laser[row][col])) {
                    int x = row + 1;
                    while(x < n && s[x][col] != '#') {
                        if (is_laser[x][col]) {
                            fail = true;
                            break;
                        }
                        second += (1 << x);
                        x++;
                    }
                    x = row - 1;
                    while(x >= 0 && s[x][col] != '#') {
                        if (is_laser[x][col]) {
                            fail = true;
                            break;
                        }
                        second += (1 << x);
                        x--;
                    }

                }
                if (!fail) {
                    valid[col].pb(mp(horiz, second));
                  //  printf("col = %d horiz = %d second = %d\n", col, horiz, second);
                }
            }
        }

        memset(dp, false, sizeof(dp));
        dp[0][0] = true;
        forn(col, m)
            forn(prof, (1 << n)) if (dp[col][prof]) {
                //printf("col = %d prof = %d\n", col, prof);
                int prof1 = prof;
                bool fail = false;
                vi v;
                forn(row, n)
                    if (is_laser[row][col]) {
                        if (prof & (1 << row)) {
                            fail = true;
                            break;
                        }/* else {
                            v.pb(row);          
                        }*/
                    } else if (s[row][col] == '#' && (prof1 & (1 << row)))
                        prof1 ^= (1 << row);
                if (fail)
                    continue;
                for(pii p : valid[col]) {
                    int horiz = p.fi;
                    int cur = prof | p.se;
                    bool ok = true;
                    forn(row, n)
                        if (s[row][col] == '.' && ((cur & (1 << row)) == 0)) {
                            ok = false;
                            break;
                        }
                    if (ok) {
                        int next = prof1 | horiz;
                        printf("col = %d prof = %d next = %d horiz = %d\n", col, prof, next, horiz);
                        dp[col + 1][next] = true;
                        fr[col + 1][next] = mp(prof, horiz);
                    }
                }
            }
        bool found = false;
        printf("Case #%d: ", test);
        forn(last, (1 << n))
            if (dp[m][last]) {
                int prof = last;
                for (int col = m - 1; col >= 0; col--) {
//                    printf("prof = %d\n", prof);
                    int horiz = fr[col + 1][prof].se;
                    forn(row, n)
                        if (horiz & (1 << row)) {
                            if (s[row][col] == '|')
                                s[row][col] = '-';
                        } else  
                            if (s[row][col] == '-')
                                s[row][col] = '|';
                    prof = fr[col + 1][prof].fi;
                }
                printf("POSSIBLE\n");
                forn(i, n)
                    cout << s[i] << endl;
                found = true;
                break;
            }
        if (!found)
            printf("IMPOSSIBLE\n");
    }
}

