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

const int dx[4] = {0, 1, -1, 0};
const int dy[4] = {1, 0, 0, -1};
const int maxn = 505;

bool found;
vi order;
bool mark[2][maxn];
int n, black;
string s[2];

int dfs(int x, int y) {
    mark[x][y] = true;
    for (int move : order) {
        int x1 = x + dx[move];
        int y1 = y + dy[move];
        if (x1 >= 0 && x1 < 2 && y1 >= 0 && y1 < n && !mark[x1][y1] && s[x1][y1] == '#') {
            return dfs(x1, y1) + 1;      
        }
    }
    return 1;
}

void check(int x, int y) {
    // printf("check x = %d y = %d\n", x, y);
    order.resize(4);
    forn(j, 4)
        order[j] = j;
    do {
        memset(mark, false, sizeof(mark));
        int res = dfs(x, y);
        if (res == black) {
            found = true;
            return;
        }
    } while(next_permutation(order.begin(), order.end()));
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        scanf("%d", &n);
        black = 0;
        forn(j, 2) {
            cin >> s[j];
            for (char c : s[j])
                if (c == '#')
                    black++;
        }
        // printf("black = %d\n", black);
        found = false;
        forn(col, n)
            if (s[0][col] == '#' || s[1][col] == '#') {
                if (s[0][col] == '#')
                    check(0, col);
                if (s[1][col] == '#')
                    check(1, col);
                break;
            }
        if (found)
            printf("yes\n");
        else printf("no\n");
    }
}
