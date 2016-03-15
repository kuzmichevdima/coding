#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

#define vi vector <int>
#define pii pair <int, int>

#define TASKNAME "bring"

typedef long long i64;
typedef long long li;
typedef long long lint;
//typedef pair <int, int> pii;
//typedef vector <int> vi;

using namespace std;

queue <pii> order;

const int maxn = 55;
const int maxt = 115;
const int inf = 1e9;

struct Edge
{
	pii vertex;
	int f, c, rev_edge;
	inline int diff()
	{
		return c - f;
	}
	//Edge(pii _vertex, int _f, int _c, int _rev_edge) : vertex(_vertex), f(_f), c(_c), rev_edge(_rev_edge) {}
	Edge(int _x, int _y, int _c, int _f, int _rev_edge) : vertex(mp(_x, _y)), f(_f), c(_c), rev_edge(_rev_edge) {}
};

int d[maxn][maxt];
int S, T;
vector <Edge> edges[maxn][maxt];

int n, m;
pair <pii, int> p[maxn][maxt];

void bfs(int t_max)
{
	order.push(mp(S, 0));
	fore(i, 1, n)
		fore(j, 0, t_max)
			d[i][j] = inf;
	d[S][0] = 0;
	while(!order.empty())
	{
		pii v = order.front();
		order.pop();
		forn(j, edges[v.fi][v.second].size())
		{
			Edge u = edges[v.fi][v.second][j];
			if (u.diff() > 0)
			{
				int newd = d[v.first][v.second] + 1;
				if (d[u.vertex.fi][u.vertex.se] > newd)
				{
					d[u.vertex.first][u.vertex.second] = newd;
					order.push(u.vertex);
				}
			}
		}
	}
}

bool dfs(pii v, int t_max)
{
	if (v == mp(T, t_max))
		return true;
	int tmp = d[v.first][v.second] + 1;
	forn(j, edges[v.fi][v.second].size()) if (edges[v.fi][v.second][j].diff() > 0)
	{
		Edge u = edges[v.fi][v.second][j];
		int du = d[u.vertex.fi][u.vertex.second];
		if (du != tmp)
			continue;
		p[u.vertex.fi][u.vertex.se] = mp(v, j);
		bool f = dfs(u.vertex, t_max);
		if (f)
			return true;
	}
	return false;
}

bool dfs2(pii v, int t_max)
{
	if (v == mp(T, t_max))
		return true;
	forn(j, edges[v.fi][v.second].size()) if (edges[v.fi][v.second][j].f > 0)
	{
		Edge u = edges[v.fi][v.second][j];
		p[u.vertex.fi][u.vertex.se] = mp(v, j);
		bool f = dfs2(u.vertex, t_max);
		if (f)
			return true;
	}
	return false;
}

int K;
vector <pii> ans[maxn];

inline bool check(int t_max)
{
	fore(i, 1, n)
		fore(j, 0, t_max)
			forn(h, edges[i][j].size())
				edges[i][j][h].f = 0;
	int total = 0;
	
	while(true)
	{
		bfs(t_max);
		if (d[T][t_max] == inf)
			break;
		
		while(dfs(mp(S, 0), t_max))
		{
			pii cur = mp(T, t_max);
			int flow = inf;
			
			while(cur != mp(S, 0))
			{
				pair <pii, int> prev = p[cur.fi][cur.se];
				flow = min(flow, edges[prev.first.first][prev.first.second][prev.second].diff());
				int prevt = prev.first.se;
				
				cur = prev.first;
				
			}
			cur = mp(T, t_max);
			while(cur != mp(S, 0))
			{
				pair <pii, int> prev = p[cur.fi][cur.se];
				Edge * e = &edges[prev.first.first][prev.first.second][prev.second];
				e->f += flow;
				int rev = e->rev_edge;
				edges[e->vertex.first][e->vertex.second][rev].f -= flow;
				cur = prev.first;
			}
			total += flow;
		}
	}
	return total >= K;
}

int main()
{
	freopen(TASKNAME ".in", "r", stdin);
	freopen(TASKNAME ".out", "w", stdout);
	scanf("%d%d%d%d%d", &n, &m, &K, &S, &T);
	forn(j, m)
	{
		int fr, to;
		scanf("%d%d", &fr, &to);
		forn(t, maxt - 2)
		{
			int t1 = edges[to][t + 1].size();
			int t2 = edges[fr][t].size();
			edges[fr][t].pb(Edge(to, t + 1, 1, 0, t1));
			edges[to][t + 1].pb(Edge(fr, t, 0, 0, t2));
		}
	}
	fore(j, 1, n)
		forn(t, maxt - 2)
		{
			int t1 = edges[j][t + 1].size();
			int t2 = edges[j][t].size();
			//int tmp = edges[j][t].size();
			edges[j][t].pb(Edge(j, t + 1, 100500, 0, t1));
			edges[j][t + 1].pb(Edge(j, t, 0, 0, t2));
		}
	//bool f = check(4);
	//bool f2 = check(3);
	//exit(0);
	int start = 1;
	int finish = 110;
	while(start < finish)
	{
		int middle = (start + finish) / 2;
		if (check(middle))
			finish = middle;
		else start = middle + 1;
	}
	printf("%d\n", start);
	check(start);
	int cnt = 0;
	while(dfs2(mp(S, 0), start))
	{
		pii cur = mp(T, start);
		int flow = inf;
		cnt++;
		while(cur != mp(S, 0))
		{
			pair <pii, int> prev = p[cur.fi][cur.se];
			flow = min(flow, edges[prev.first.first][prev.first.second][prev.second].f);
			int prevt = prev.first.se;
			
				if (prev.first.first != cur.fi)
					ans[prevt].pb(mp(cnt, cur.first));
			
			cur = prev.first;
			
		}
		cur = mp(T, start);
		while(cur != mp(S, 0))
		{
			pair <pii, int> prev = p[cur.fi][cur.se];
			Edge * e = &edges[prev.first.first][prev.first.second][prev.second];
			e->f -= flow;
			int rev = e->rev_edge;
			edges[e->vertex.first][e->vertex.second][rev].f += flow;
			cur = prev.first;
		}
	}
	forn(t, start)
	{
		printf("%d ", ans[t].size());
		forn(j, ans[t].size())
			printf("%d %d ", ans[t][j].fi, ans[t][j].se);
		printf("\n");
	}
}