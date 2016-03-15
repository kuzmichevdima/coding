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
#include <ctime>

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

const int maxn = 22;

bool dp[maxn][1 << maxn];
bool a[maxn][maxn];
int list[maxn][maxn];
int n;
clock_t limit_time;
int sz[maxn];
int iter = 0;
int len[1 << maxn];

int best_len = 0;
int best_vertex, best_mask;

inline void get_answer();

void go(int i, int mask)
{
	if (len[mask] > best_len)
	{
		best_len = len[mask];
		best_vertex = i;
		best_mask = mask;
	}
	iter++;
	if (iter > 300)
	{
		
		if (clock() > limit_time)
			get_answer();
		iter = 0;
	}
	if (dp[i][mask])
		return;
	dp[i][mask] = true;
	forn(e, sz[i])
	{
		iter++;
		int j = list[i][e];
		if (!(mask & (1 << j)))
			go(j, mask | (1 << j));
	}
}

inline void get_answer()
{
	printf("%d\n", best_len - 1);
	int cur_vertex = best_vertex;
	int cur_mask = best_mask;
	vi ans;
	forn(j, best_len)
	{
		ans.pb(cur_vertex);
		forn(prev, n) if ((cur_mask & (1 << prev)) && (a[prev][cur_vertex])
			&& (dp[prev][cur_mask ^ (1 << cur_vertex)]))
		{
			cur_mask ^= (1 << cur_vertex);
			cur_vertex = prev;
			break;
		}
	}
	for (int j = ans.size() - 1; j >= 0; j--)
		printf("%d ", ans[j] + 1);
	exit(0);
}

void precalc()
{
	len[0] = 0;
	fore(mask, 1, (1 << n) - 1)
	{
		forn(j, n) if (mask & (1 << j))
		{
			len[mask] = len[mask ^ (1 << j)] + 1;
			
			break;
		}
	}
}

int main()
{
	limit_time = clock() + 0.35 * CLOCKS_PER_SEC;
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int m;
	scanf("%d%d", &n, &m);
	precalc();
	forn(j, m)
	{
		int fr, to;
		scanf("%d%d", &fr, &to);
		fr--;
		to--;
		a[fr][to] = true;
	}
	forn(i, n)
	{
		sz[i] = 0;
		forn(j, n)
			if (a[i][j])
			{
				list[i][sz[i]] = j;
				sz[i]++;
			}
	}
	forn(i, n)
		go(i, 1 << i);
	get_answer();
	
	return 0;
}