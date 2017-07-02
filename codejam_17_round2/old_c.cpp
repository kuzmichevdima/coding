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

const int sz = 55;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};
const int UP = 0;
const int RIGHT = 1;
const int LEFT = 2;
const int DOWN = 3;

vector <pii> cells;
vector <pii> covering[sz * sz][4];
bool banned[sz * sz][4];
int mark[sz][sz];
vector <pii> lasers;
int n, m;
string s[sz];
bool is_laser[sz][sz];

inline void fmark(int cur, int move, int delta) {
    for (auto p : covering[cur][move]) {
        mark[p.fi][p.se] += delta;
    }
}

bool go(int cur) {
    if (cur == (int)lasers.size()) {
        for (auto c : cells)
            if (mark[c.fi][c.se] == 0)
                return false;
        printf("POSSIBLE\n");
        forn(i, n) {
            cout << s[i] << endl;
        }
        return true;
    }
    if (!banned[cur][UP] && !banned[cur][DOWN]) {
        fmark(cur, UP, 1);
        fmark(cur, DOWN, 1);
        s[lasers[cur].fi][lasers[cur].se] = '|';
        if (go(cur + 1))
            return true;
        fmark(cur, UP, -1);
        fmark(cur, DOWN, -1);
    }
    if (!banned[cur][LEFT] && !banned[cur][RIGHT]) {
        fmark(cur, LEFT, 1);
        fmark(cur, RIGHT, 1);
        s[lasers[cur].fi][lasers[cur].se] = '-';
        if (go(cur + 1))
            return true;
        fmark(cur, LEFT, -1);
        fmark(cur, RIGHT, -1);
    }
    return false;
}

int main() {
    int tests;
    scanf("%d", &tests);
    fore(test, 1, tests) {
        cerr << "test " << test << endl;
        scanf("%d%d", &n, &m);
        forn(j, n)
            cin >> s[j];
        lasers.clear();
        forn(i, n)
            forn(j, m) {
                is_laser[i][j] = s[i][j] == '-' || s[i][j] == '|';
                if (is_laser[i][j])
                    lasers.pb(mp(i, j));
                else if (s[i][j] != '.' && s[i][j] != '#')
                    assert(false);
            }
        memset(banned, false, sizeof(banned));
        forn(num, lasers.size()) {
            forn(move, 4) {
                int x = lasers[num].fi;
                int y = lasers[num].se;
                covering[num][move].clear();
                while(true) {
                    x += dx[move];
                    y += dy[move];
                    if (x < 0 || x >= n || y < 0 || y >= m || s[x][y] == '#')
                        break;
                    if (is_laser[x][y])
                        banned[num][move] = true;
                    covering[num][move].pb(mp(x, y));
                }
            }
        }
        cells.clear();
        forn(i, n)
            forn(j, m)
                if (s[i][j] == '.')
                    cells.pb(mp(i, j));
        memset(mark, 0, sizeof(mark));
        printf("Case #%d:", test);
        bool pos = go(0);
        if (!pos)
            printf("IMPOSSIBLE\n");
    }
}

