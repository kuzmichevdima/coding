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

struct edge
{
	int vertex, u, c, f, back_edge;
	edge(int _vertex, int _u, int _c, int _f, int _back_edge) : vertex(_vertex), u(_u), c(_c), f(_f), back_edge(_back_edge) {}
};

const int maxn = 5005;
const int inf = 1e9;

vector <edge> list[maxn];
int state[maxn];
int d[maxn];
int n, s, t;

deque <int> order;
pii p[maxn];
int balance[maxn];
bool mark[maxn];

void add_edge(int a, int b, int u, int c)
{
	edge e1(b, u, c, 0, list[b].size());
	edge e2(a, 0, -c, 0, list[a].size());
	list[a].pb(e1);
	list[b].pb(e2);
}

void dfs(int v)
{
	mark[v] = true;
	forn(j, list[v].size())
	{
		int next = list[v][j].vertex;
		if ((!mark[next]) && (next <= n))
		{
			dfs(next);
		}
	}
}

int alternative = 1e9;

void go(int v, int cur, int changes)
{
	if (v == n + 1)
	{
		bool fail = false;
		fore(j, 1, n)
			if (balance[j] != 0)
			{
				fail = true;
				break;
			}
		if (!fail)
			alternative = min(alternative, changes);
		return;
	}
	if (cur == list[v].size())
	{
		go(v + 1, 0, changes);
		return;
	}
	if (list[v][cur].c == 1)
	{
		balance[v] -= 2;
		balance[list[v][cur].vertex] += 2;
		go(v, cur + 1, changes + 1);
		balance[v] += 2;
		balance[list[v][cur].vertex] -= 2;

		go(v, cur + 1, changes);
	}
	else go(v, cur + 1, changes);
}

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	//int tests = 1000;
	int tests;
	scanf("%d", &tests);
	forn(test, tests)
	{
		//printf("===========\n");
		int m;
		scanf("%d%d", &n, &m);
		//n = 8;
		//m = 22;
		fore(j, 1, n + 2)
		{
			list[j].clear();
			balance[j] = 0;
			mark[j] = false;
		}
		s = n + 1;
		t = n + 2;
		forn(j, m)
		{
			int fr, to;
			scanf("%d%d", &fr, &to);
			//fr = rand() % n + 1;
			//to = rand() % n + 1;
			add_edge(fr, to, 1, 1);
			balance[fr]++;
			balance[to]--;
		}
		
		fore(j, 1, n)
			if (!list[j].empty())
			{
				dfs(j);
				break;
			}
		bool fail = false;
		fore(j, 1, n)
			if ((!mark[j]) && (!list[j].empty()))
			{
				fail = true;
				break;
				
			}
		fore(i, 1, n)
		{
			if (abs(balance[i]) % 2 == 1)
			{
				fail = true;
				break;
			}
		}
		if (fail)
		{
			printf("-1\n");
			continue;
		}
		int k = 0;
		fore(i, 1, n)
			if (balance[i] > 0)
			{
				add_edge(s, i, balance[i] / 2, 0);
				k += balance[i] / 2;
			}
			else if (balance[i] < 0)
				add_edge(i, t, (-balance[i]) / 2, 0);

		int flow = 0;
		int cost = 0;
		while(flow < k)
		{
			 fore(j, 1, n + 2)
			 {
				 state[j] = 0;
				 d[j] = inf;
			 }
			 state[s] = 1;
			 d[s] = 0;
			 order.push_back(s);
			 while(!order.empty())
			 {
				 int v = order.front();
				 order.pop_front();
				 state[v] = 2;
				 forn(j, list[v].size())
				 {
					 edge e = list[v][j];
					 if (e.f < e.u && d[v] + e.c < d[e.vertex])
					 {
						 d[e.vertex] = d[v] + e.c;
						 
						 p[e.vertex] = mp(v, j);
						 if (state[e.vertex] == 0)
						 {
							 order.push_back(e.vertex);
						 }
						 else if (state[e.vertex] == 2)
						 {
							 order.push_front(e.vertex);
						 }
						 state[e.vertex] = 1;
					 }
				 }
			 }
			 if (d[t] == inf)
				 break;
			 int addflow = k - flow;
			 for (int v = t; v != s; v = p[v].fi)
			 {
			//	 printf("v = %d\n", v);
				 int prev = p[v].fi;
				 addflow = min(addflow, list[prev][p[v].se].u - list[prev][p[v].se].f);
			 }
			// printf("===========\n");
			 for (int v = t; v != s; v = p[v].fi)
			 {
				int prev = p[v].fi;
				list[prev][p[v].se].f += addflow;
				int back_number = list[prev][p[v].se].back_edge;
				list[v][back_number].f -= addflow;
				cost += addflow * list[prev][p[v].se].c;
			 }
			 flow += addflow;
		}
		assert(flow == k);
		printf("%d\n", cost);
		/*int inf = 1e9;
		alternative = inf;
		go(1, 0, 0);
		printf("%d\n", alternative == inf ? -1 : alternative);*/
		/*assert(cost == alternative);
		if (cost != alternative)
		{
			printf("FAIL!!!\n");
			exit(0);
		}*/
		//printf("alternative = %d\n", alternative);
		//exit(0);
	}
	return 0;
}