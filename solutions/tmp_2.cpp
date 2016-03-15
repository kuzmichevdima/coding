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

int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int d[400];

int OneKnight(int N, std::vector<int> S, std::vector<int> F) {
    int s = (S[0] - 1) * N + S[1] - 1;
    d[s] = 1;
    std::queue <int > Q;
    Q.push(s);
    while(!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        for(int j = 0; j < 8; j++)
        {
            int x = v / N + dx[j];
            int y = v % N + dy[j];
            int T = x * N + y;
            if (x < 0 || x >= N || y < 0 || y >= N || d[T])
                continue;
            d[T] = d[v] + 1;
            Q.push(T);
        }
    }
    return d[(F[0] - 1) * N + F[1] - 1] - 1;

void run(int N, int x1, int y1, int x2, int y2)
{
    vi c1 {x1, y1};
    vi c2 {x2, y2};
    printf("%d", OneKnight(N, c1, c2));
}


/*int d[20][20];

void bfs()
{
    d[0] = 0;
    queue <pii> Q;
    Q.push(mp(0, 0));
    while(!Q.empty())
    {
        pii v = Q.front();
        Q.pop();
        forn(j, 8)
        {
            int newx = v.fi + dx[j];
            int newy = v.se + dy[j];
            if (newx < 0 || newx > 19 || newy < 0 || newy > 19 || d[newx][newy] != -1)
                continue;
            d[newx][newy] = d[v.fi][v.se] + 1;
            Q.push(mp(newx, newy));
        }
    }
    forn(i, 20)
    {
        forn(j, 20)
            printf("%d ", i <= j ? d[i][j] : 0);
        printf("\n");
    }
}*/


int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    run(5, 1, 3, 4, 5);
    //bfs();
}

