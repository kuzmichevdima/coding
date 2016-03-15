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

inline int get(int x, int y)
{
	if (x >= y)
	{
		for (int k = 30; k >= 0; k--)
			if (y & (1 << k))
			{
				return (x - (1 << k)) / (1 << k);
			}
	}
	else
	{
		for (int k = 30; k >= 0; k--)
			if (x & (1 << k))
			{
				return - ((y - (1 << k)) / (1 << k));
			}
	}
}

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	/*fore(h, 1, 20)
	{
		fore(w, 1, 20)
			printf("%d ", get(w, h));
		printf("\n");
	}*/
	int tests;
	scanf("%d", &tests);
	forn(test, tests)
	{
		int n;
		scanf("%d", &n);
		i64 sum = 0;
		forn(j, n)
		{
			int w, h;
			scanf("%d%d", &w, &h);
			//sum += (i64)get(w, h);
			sum += (i64)get(h, w);
		}
		if (sum > 0)
			printf("Alice\n");
		else printf("Bob\n");
	}
	return 0;
}