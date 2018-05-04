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

#define se second
#define fi first
#define mp make_pair
#define pb push_back
typedef pair <int, int> pii;

const int maxn = 500005;
const int inf = 1e9;

int start[maxn];
int tree[maxn * 4];
vector <int> list;
vector <int> edges[maxn];

void dfs(int v)
{
	list.pb(v);
	start[v] = list.size();
	for (int j = 0; j < edges[v].size(); j++)
	{
		int u = edges[v][j];
		if (start[u] == 0)
		{
			dfs(u);
			list.push_back(v);
		}
	}
}

void build(int i, int L, int R)
{
	//printf("i = %d L = %d R = %d\n", i, L, R);
	if (L + 1 == R)
	{
		tree[i] = list[L - 1];
		return;
	}
	int m = (L + R) / 2;
	build(i * 2, L, m);
	build(i * 2 + 1, m, R);
	tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
}

int get_min(int i, int tl, int tr, int L, int R)
{
	
	if (tl >= R || L >= tr)
		return inf;
	if (tl == L && tr == R)
		return tree[i];
	//printf("i = %d tl = %d tr = %d L = %d R = %d\n", i, tl, tr, L, R);
	int m = (tl + tr) / 2;
	int g1 = get_min(i * 2, tl, m, L, min(R, m));
	int g2 = get_min(i * 2 + 1, m, tr, max(L, m), R);
	return min(g1, g2);
}


int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int queries;
	scanf("%d\n", &queries);
	vector <pii> query;
	for (int j = 0; j < queries; j++)
	{
		int x, y;
		char c1;
		scanf("%c%c%c%d%d\n", &c1, &c1, &c1, &x, &y);
		if (c1 == 'D')
		{
			edges[x].pb(y);
		}
		else
		{
			query.pb(mp(x, y));
		}
	}
	dfs(1);
	/*for (int j = 0; j < list.size(); j++)
		printf("%d ", list[j]);
	printf("\n");*/
	build(1, 1, list.size() + 1);
	for (int j = 0; j < query.size(); j++)
	{
		int v = start[query[j].fi];
		int u = start[query[j].se];
		int ans = get_min(1, 1, list.size() + 1, min(v, u), max(v, u) + 1);
		printf("%d\n", ans);
	}
	return 0;
}