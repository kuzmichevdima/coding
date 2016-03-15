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

vi list[maxn];

int cnt;

inline void add_edge(int x, int y)
{
	assert(x >= 1 && x <= cnt);
	assert(y >= 1 && y <= cnt);
	list[x].pb(y);
	list[y].pb(x);
	
}

int p;

inline int get(int part, int x)
{
	return p + 2 + (part - 2) * p + x;
}

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
	scanf("%d", &p);
	cnt = 1 + p + 1 + p * (p + 1) + p * p;
	printf("%d\n", cnt);
	fore(j, 2, p + 2)
		add_edge(1, j);
	fore(d1, 2, p + 2)
		fore(j, 1, p)
			add_edge(d1, get(d1, j));
	int tmp = cnt - p * p;
	fore(first, 1, p)
	{
		int number1 = get(2, first);
		fore(second, 1, p)
		{
			tmp++;
			add_edge(number1, tmp);
			/*int cur = (first - 1) + second;
			if (cur > p)
				cur -= p;*/
			int cur = second;
			fore(d, 3, p + 2)
			{
				int number2 = get(d, cur);
				add_edge(number2, tmp);
				//cur += second;
				//cur++;
				cur += first;
				if (cur > p)
					cur -= p;
			}
		}
	}
	fore(j, 1, cnt)
	{
		assert(list[j].size() == p + 1);
		forn(h, list[j].size())
			printf("%d ", list[j][h]);
		printf("\n");
	}
	
	return 0;
}