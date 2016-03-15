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

const int inf = 2e9;
const int maxn = 505;
const int maxm = 20005;


vi edges[maxn];
int current[maxn];
vi list;
int f[maxm];
int c[maxm];
int n, m;
int d[maxn];

int dfs(int v, int cur_flow)
{
	if (v == n)
	{
		return cur_flow;
	}
	fore(j, current[v], edges[v].size() - 1)
	{
		int id = edges[v][j];
		int u = list[id];
		if (d[u] == d[v] + 1 && c[id] > f[id])
		{
			int tmp = min(cur_flow, c[id] - f[id]);
			int ret = dfs(u, tmp);
			if (ret != 0)
			{
				f[id] += ret;
				f[id ^ 1] = -f[id];
				return ret;
			}
			else current[v]++;
		}
		else current[v]++;
	}
	return 0;
}

queue <int> order;

void bfs()
{
	d[1] = 0;
	fore(j, 2, n)
		d[j] = inf;
	order.push(1);
	while(!order.empty())
	{
		int v = order.front();
		order.pop();
		forn(j, edges[v].size())
		{
			int id = edges[v][j];
			int u = list[id];
			if (c[id] > f[id] && d[u] == inf)
			{
				d[u] = d[v] + 1;
				order.push(u);
			}
		}
	}
}

int main()
{
	freopen("inp", "r", stdin);
	scanf("%d%d", &n, &m);
	forn(j, m)
	{
		int fr, to, c1;
		scanf("%d%d%d", &fr, &to, &c1);
		edges[fr].pb(list.size());
		c[list.size()] = c1;
		list.pb(to);

		edges[to].pb(list.size());
		c[list.size()] = 0;
		list.pb(fr);
	}
	i64 answer = 0;
	while(true)
	{
		bfs();
		if (d[n] == inf)
			break;
		fore(j, 1, n)
			current[j] = 0;
		while(true)
		{
			int to_add = dfs(1, inf);
			if (to_add == 0)
				break;
			answer += to_add;
		}
	}
	cout << answer;

	return 0;
}
