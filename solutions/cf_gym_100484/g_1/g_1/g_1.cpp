#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <queue>
#include <memory.h>
#include <cmath>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)
#define all(x) (x).begin(), (x).end()
#define se second
#define fi first
#define mp make_pair
#define pb push_back
#define op operator
typedef vector <int> vi;
typedef pair<int, int> pii;
typedef long long i64;

const int maxn = 10005;

int color[maxn];
vi list[maxn];
vi edges[maxn];
int cnt, n;
int d[maxn];
pii p[maxn];
pii fr[maxn];
bool done[maxn];

const int inf = 2e9;

void dfs(int v)
{
	list[cnt].pb(v);
	color[v] = cnt;
	forn(j, edges[v].size())
	{
		int u = edges[v][j];
		if (color[u] == -1)
			dfs(u);
	}
}

inline int sqr(int x)
{
	return x * x;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	fore(j, 1, n)
	{
		scanf("%d%d", &p[j].fi, &p[j].se);
		color[j] = -1;
	}
	int m;
	scanf("%d", &m);
	forn(j, m)
	{
		int t1, t2;
		scanf("%d%d", &t1, &t2);
		edges[t1].pb(t2);
		edges[t2].pb(t1);
	}
	fore(j, 1, n) if (color[j] == -1)
	{
		dfs(j);
		cnt++;
	}
	d[0] = 0;
	fore(j, 1, cnt - 1)
		d[j] = inf;
	while(true)
	{
		int chosen = -1;
		forn(choice, cnt) if (!done[choice])
			if (chosen == -1 || d[choice] < d[chosen])
			{
				chosen = choice;
			}
		if (chosen == -1)
			break;
		if (chosen != 0)
			printf("%d %d\n", fr[chosen].fi, fr[chosen].se);
		done[chosen] = true;
		forn(vertex, list[chosen].size())
		{
			int v = list[chosen][vertex];
			fore(another, 1, n)
			{
				int c = color[another];
				if (!done[c])
				{
					int nnew = sqr(p[v].fi - p[another].fi) + sqr(p[v].se - p[another].se);
					if (nnew < d[c])
					{
						d[c] = nnew;
						fr[c] = mp(v, another);
					}
				}
			}
		}
	}
	return 0;
}