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

const int maxn = 1e5 + 5;

bool in_queue[maxn];
queue <int> order;
int n, m;
vi edges[maxn];
int color[maxn];

int cnt[3];

inline bool check(int u)
{
	memset(cnt, 0, sizeof(cnt));
	forn(h, edges[u].size())
		cnt[color[edges[u][h]]]++;
	return cnt[color[u]] > 1;
	/*forn(c, 3)
		if (cnt[c] > 1)
		{
			return true;
		}
	return false;*/
}

int main()
{
	freopen("coloring.in", "r", stdin);
	freopen("coloring.out", "w", stdout);
	scanf("%d%d", &n, &m);
	forn(j, m)
	{
		int fr, to;
		scanf("%d%d", &fr, &to);
		edges[fr].pb(to);
		edges[to].pb(fr);
	}
	fore(j, 1, n)
		color[j] = 0;
	fore(j, 1, n)
		if (check(j))
		{
			in_queue[j] = true;
			order.push(j);
		}
	while(!order.empty())
	{
		int v = order.front();
		/*printf("iteration v = %d\n", v);
		fore(j, 1, n)
			printf("%d ", color[j]);
		printf("\n");*/
		order.pop();
		in_queue[v] = false;

		bool bad_found = check(v);
		if (!bad_found)
			continue;

		int good = -1;
		forn(c, 3)
		{
			if (cnt[c] <= 1)
				good = c;
		}
		
		color[v] = good;

		forn(j, edges[v].size())
		{
			int u = edges[v][j];
			if (in_queue[u])
				continue;
			if (check(u))
			{
				order.push(u);
				in_queue[u] = true;
			}
		}
	}
	fore(j, 1, n)
		printf("%d ", color[j] + 1);
	return 0;
}