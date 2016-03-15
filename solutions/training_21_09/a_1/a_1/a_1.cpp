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

const int maxn = 3005;

struct elem
{
	i64 first;
	i64 second;
	elem(){}
	elem(i64 _first, i64 _second) : first(_first), second(_second) {}
};

bool operator < (elem e1, elem e2)
{
	return e1.first * e2.second < e2.first * e1.second;
}

elem operator * (elem e, i64 x)
{
	return elem(e.first * x, e.second);
}

inline i64 abss(i64 x)
{
	return (x < 0 ? -x : x);
}

i64 gcd(i64 x, i64 y)
{
	if (x == 0 || y == 0)
		return x + y;
	if (x > y)
		return gcd(x % y, y);
	else return gcd(y % x, x);
}

elem get(i64 x, i64 y)
{
	i64 g = gcd(abss(x), y);
	return elem(x / g, y / g);
}

elem operator + (elem e1, elem e2)
{
	return get(e1.first * e2.second + e1.second * e2.first, e1.second * e2.second);
}

map <elem, int> m;

int dp[maxn][2];
pii fr[maxn][2];
elem answer[maxn];
vector <pii> list;
int a[maxn];
elem diff[maxn];

int main()
{
	freopen("arithmetic.in", "r", stdin);
	freopen("arithmetic.out", "w", stdout);
	int P, Q, n;
	scanf("%d%d%d", &n, &P, &Q);
	fore(j, 1, n)
		scanf("%d", &a[j]);
	dp[1][0] = P;
	fr[1][0] = mp(-1, -1);
	dp[1][1] = Q;
	fr[1][1] = mp(1, 0);
	fore(i, 2, n)
		forn(state, 2)
		{
			dp[i][state] = dp[i - 1][state] + P;
			fr[i][state] = mp(-1, -1);
			if (state == 0)
				continue;
			m.clear();
			for (int prev = i; prev >= 1; prev--)
			{
				int to_change;
				if (prev == i)
					to_change = 0;
				else
				{
					elem b = get(a[i] - a[prev], i - prev);
					int mb = m[b];
					to_change = i - prev - 1 - mb;
					m[b]++;
				}
				forn(prev_state, 2)
				{
					int nnew = dp[prev - 1][prev_state] + to_change * P + Q;
					if (nnew < dp[i][state])
					{
						dp[i][state] = nnew;
						fr[i][state] = mp(prev, prev_state);
					}
				}
			}
		}
	printf("%d\n", dp[n][1]);
	int cur_pos = n;
	int cur_state = 1;
	while(cur_pos > 0)
	{
		pii f = fr[cur_pos][cur_state];
		if (f.fi == -1)
		{
			cur_pos--;
		}
		else
		{
			list.pb(mp(f.first, cur_pos));
			cur_pos = f.fi - 1;
			cur_state = f.second;
		}
	}
	assert(!list.empty());
	reverse(all(list));
	forn(j, list.size())
	{
		if (list[j].first == list[j].second)
		{
			diff[j] = elem(0, 1);
		}
		else
		{
			diff[j] = get(a[list[j].se] - a[list[j].fi], list[j].se - list[j].fi);
		}
		fore(pos, list[j].fi, list[j].se)
		{
			answer[pos] = elem(a[list[j].fi], 1) + diff[j] * (pos - list[j].fi);
		}
	}

	forn(j, list.size())
	{
		int limit = (j == 0 ? 1 : list[j - 1].se + 1);
		for (int pos = list[j].fi - 1; pos >= limit; pos--)
		{
			answer[pos] = answer[list[j].fi] + diff[j] * (-list[j].fi + pos);
		}
	}
	fore(pos, list.back().se + 1, n)
	{
		answer[pos] = answer[list.back().se] + diff[list.size() - 1] * (pos - list.back().se);
	}
	printf("%d\n", list.size());
	forn(j, list.size())
	{
		int left_bound = (j == 0 ? 1 : list[j - 1].se + 1);
		int right_bound = (j == list.size() - 1 ? n : list[j].se);
		printf("%d ", right_bound - left_bound + 1);
		fore(pos, left_bound, right_bound)
			if (answer[pos].se == 1)
				printf("%lld ", answer[pos].fi);
			else printf("%lld/%lld ", answer[pos].fi, answer[pos].se);
		printf("\n");
	}
	return 0;
}