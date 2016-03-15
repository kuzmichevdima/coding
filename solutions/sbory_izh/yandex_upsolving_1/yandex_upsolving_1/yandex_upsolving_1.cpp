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
const int max_level = 30;

int prec[max_level + 5][maxn][2];
int a[maxn];
int n;

void precalc()
{
	forn(pos, n)
	{
		prec[0][pos][0] = 0;
		prec[0][pos][1] = a[pos];
	}
	fore(level, 1, max_level)
		fore(pos, 0, n - (1 << level))
			forn(typ, 2)
			{
				prec[level][pos][typ] = prec[level - 1][pos][typ] + prec[level - 1][pos + (1 << (level - 1))][1 - typ];
			}
}

inline int get_type(int x)
{
	int ret = 0;
	while(x > 0)
	{
		if (x & 1)
			ret = 1 - ret;
		x = x >> 1;
	}
	return ret;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	forn(j, n)
		scanf("%d", &a[j]);
	precalc();
	int m;
	scanf("%d", &m);
	
	forn(it, m)
	{
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		x--;
		int bound = y + k - 1;
		int limit = 0;
		while(k >= (1 << (limit + 1)))
			limit++;
		int cur = y;
		int answer = 0;
		while(cur < y + k)
		{
			for (int p = limit; p >= 0; p--) if (cur % (1 << p) == 0)
			{
				if (cur + (1 << p) - 1 <= bound)
				{
					int typ = get_type(cur / (1 << p));
					answer += prec[p][cur - y + x][typ];
					cur += (1 << p);
					break;
				}
			}
		}
		printf("%d\n", answer);
	}
	return 0;
}