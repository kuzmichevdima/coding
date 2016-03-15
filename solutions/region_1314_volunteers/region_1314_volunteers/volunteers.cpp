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
const int inf = 2e9;

pii bounds[2][maxn];

inline void upd(int side, int v, int value)
{
	bounds[side][v].fi = min(bounds[side][v].fi, value);
	bounds[side][v].se = max(bounds[side][v].se, value);
}

i64 answer;
int n, m, k;

void first_part()
{
	vector <pii> order;
	fore(j, 1, k)
		order.pb(mp(bounds[1][j].fi, -1));
	fore(j, 1, m)
		order.pb(mp(bounds[0][j].se, 1));
	sort(all(order));
	i64 counter = 0;
	for (int j = order.size() - 1; j >= 0; j--)
		if (order[j].se == 1)
			answer -= counter;
		else counter++;
}

void second_part()
{
	vector <pii> order;
	fore(j, 1, k)
		order.pb(mp(bounds[1][j].se, 1));
	fore(j, 1, m)
		order.pb(mp(bounds[0][j].fi, -1));
	sort(all(order));
	i64 counter = 0;
	forn(j, order.size())
		if (order[j].se == -1)
			answer -= counter;
		else counter++;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	fore(j, 1, m)
		bounds[0][j] = mp(inf, -inf);
	fore(j, 1, k)
		bounds[1][j] = mp(inf, -inf);
	fore(j, 1, n)
	{
		forn(side, 2)
		{
			int anc;
			scanf("%d", &anc);
			upd(side, anc, j);
		}
	}
	fore(j, 1, m - 1)
	{
		int anc;
		scanf("%d", &anc);
		upd(0, anc, bounds[0][j].fi);
		upd(0, anc, bounds[0][j].se);
	}
	fore(j, 1, k - 1)
	{
		int anc;
		scanf("%d", &anc);
		upd(1, anc, bounds[1][j].fi);
		upd(1, anc, bounds[1][j].se);
	}
	answer = (i64)m * (i64)k;
	first_part();
	second_part();
	cout << answer;
	return 0;
}