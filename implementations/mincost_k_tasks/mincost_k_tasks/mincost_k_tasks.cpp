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

const int maxn = 205;
const int inf = 1e9;

vector <edge> list[maxn];
int state[maxn];
int d[maxn];
int n, s, t;

deque <int> order;
pii p[maxn];
int cnt;

void add_edge(int a, int b, int u, int c)
{
	edge e1(b, u, c, 0, list[b].size());
	edge e2(a, 0, -c, 0, list[a].size());
	list[a].pb(e1);
	list[b].pb(e2);
}



int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
		scanf("%d", &n);
		fore(i, 1, n)
			fore(j, 1, n)
			{
				int c;
				scanf("%d", &c);
				add_edge(i, j + n, 1, c);
			}
		s = 2 * n + 1;
		t = 2 * n + 2;
		fore(i, 1, n)
			add_edge(s, i, 1, 0);
		fore(j, 1, n)
			add_edge(j + n, t, 1, 0);
		
		
		int flow = 0;
		int cost = 0;
		while(flow < n)
		{
			 fore(j, 1, t)
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
			 int addflow = n - flow;
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
		printf("%d\n", cost);
		//exit(0);
	return 0;
}