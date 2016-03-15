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

int n, d, p;

struct Point
{
	vector <int> c;
	Point()
	{
		forn(j, d)
			c.pb(0);
	}
	void print()
	{
		forn(j, d)
			//printf("%d ", c[j]);
			printf("%d ", c[j] - 1);
	}
};

typedef vector <pair<Point, Point> > myvector;

const int maxn = 30;

myvector nnew, list[maxn];

/*inline void change(int x, int mult, int & y)
{
	if (mult == 1)
		y = 1 << (p - 1) + x;
	else y = 1 << (p - 1) + 1 - x;
	//y = 1 << (p - 1) + mult * x;
}*/

void go(int cur, bool flag)
{
	if (cur == d)
	{
		if (flag)
		{
			forn(j, list[p - 1].size())
			{
				myvector tmp(list[p - 1].size());
				tmp[j] = list[p - 1][j];
				forn(h, d)
				{
					tmp[j].first.c[h] += (1 << (p - 1));
					tmp[j].second.c[h] += (1 << (p - 1));
				}
				list[p].pb(tmp[j]);
			}
		}
		else
		{
			/*printf("add\n");
			forn(j, d)
				printf("%d ", nnew[j]);
			printf("\n");*/
			forn(j, nnew.size())
				list[p].pb(nnew[j]);
		}
		return;
	}
	//mult = 1
	//printf("mult = 1\n");
	forn(j, list[p - 1].size())
	{
		nnew[j].first.c[cur] = -list[p - 1][j].first.c[cur] + (1 << (p));	
		nnew[j].second.c[cur] = -list[p - 1][j].second.c[cur] + (1 << (p)) + 1;
		//printf("cur = %d (%d %d)\n", cur, nnew[j].first.c[cur], nnew[j].second.c[cur]);
	}
	//go(cur + 1, false);
	go(cur + 1, flag);

	//mult = -1
	//printf("mult = -1\n");
	forn(j, list[p - 1].size())
	{
		nnew[j].first.c[cur] = list[p - 1][j].first.c[cur];
		nnew[j].second.c[cur] = list[p - 1][j].second.c[cur];
	//	printf("cur = %d (%d %d)\n", cur, nnew[j].first.c[cur], nnew[j].second.c[cur]);
	}
	go(cur + 1, false);
	//go(cur + 1, flag);
}

int main()
{
	freopen("packing.in", "r", stdin);
	freopen("packing.out", "w", stdout);
	scanf("%d%d", &d, &n);
	//Point zero;
	Point S1, S2;
	forn(j, d)
		S1.c[j] = 1;
	forn(j, d)
		S2.c[j] = 2;
	list[1].pb(mp(S1, S2));
	for (p = 2; p <= n; p++)
	{
		Point corner1;
		forn(j, d)
			corner1.c[j] = (1 << (p - 1));
		Point corner2;
		forn(j, d)
			corner2.c[j] = (1 << (p - 1)) + 1;
		list[p].pb(mp(corner1, corner2));
		nnew.resize(list[p - 1].size());
		go(0, true);
		
	}
	printf("%d\n", list[n].size());
	forn(j, list[n].size())
	{
		list[n][j].first.print();
		list[n][j].second.print();
		printf("\n");
	}
	return 0;
}