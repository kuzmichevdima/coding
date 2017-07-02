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

const int maxn = 7005;
const i64 inf = 1e18;
i64 d[maxn][2][3];
vector <pii> edges[3][maxn];

struct State {
    int vertex, rick, bus;
    State(int vertex, int rick, int bus) : vertex(vertex), rick(rick), bus(bus) {}
};

bool operator < (State first, State second) {
    if (first.vertex != second.vertex)
        return first.vertex < second.vertex;
    if (first.rick != second.rick)
        return first.rick < second.rick;
    return first.bus < second.bus;
}

void add(int typ, int v, int u, int t) {
    edges[typ][v].pb(mp(u, t));
    edges[typ][u].pb(mp(v, t));
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(j, m) {
        int v, u, feet, bus, rick;
        scanf("%d%d%d%d%d", &v, &u, &feet, &bus, &rick);
        add(0, v, u, feet);
        add(1, v, u, bus);
        add(2, v, u, rick);
    }
    fore(j, 1, n)
        forn(rick, 2)
            forn(bus, 3)
                d[j][rick][bus] = inf;
    d[1][0][0] = 0;
    set <pair<i64, State> > order;
    order.insert(mp(0, State(1, 0, 0)));
    vector<bool> flag(3);
    flag[0] = true;
    while(!order.empty()) {
        auto tmp = *order.begin();
        State s = tmp.se;
        order.erase(order.begin());
        if (d[s.vertex][s.rick][s.bus] != tmp.fi)
            continue;

        int v = s.vertex;
        if (v == n) {
            cout << d[v][s.rick][s.bus];
            exit(0);
        }
        flag[2] = s.rick < 1;
        flag[1] = s.bus < 2;
        fore(typ, 0, 2) {
            if (!flag[typ])
                continue;
  //          printf("v = %d typ = %d\n", v, typ);
            for (auto p : edges[typ][v]) {
                State nnew = State(p.fi, typ == 2 ? s.rick + 1 : s.rick, typ == 1 ? s.bus + 1 : s.bus);
                i64 newd = d[v][s.rick][s.bus] + p.se;
//                cout << "newd = " << newd << endl;
                if (newd < d[nnew.vertex][nnew.rick][nnew.bus]) {
                    d[nnew.vertex][nnew.rick][nnew.bus] = newd;
                    order.insert(mp(newd, nnew));
                }
            }
        }
    }
    printf("-1");
}
