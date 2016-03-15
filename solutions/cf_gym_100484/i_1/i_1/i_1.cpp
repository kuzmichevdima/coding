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

struct elem
{
	int fr, to, w;
	elem(){}
};

const int maxn = 55;
const int inf = 1e9;

elem list[maxn];
map <string, int> mymap;
vector <pii> edges[maxn];
i64 cnt_opt[maxn];
int d_opt[maxn];

int n;

void paths(int start, int finish, int & d_finish, i64 & cnt_finish)
{
	vector <int> d(n, inf);
	vector <bool> used(n, false);
	vector <i64> cnt(n, 0);
	d[start] = 0;
	cnt[start] = 1;
	while(true)
	{
		int chosen = -1;
		forn(choice, n) if ((!used[choice]) && (d[choice] != inf))
			if (chosen == -1 || d[choice] < d[chosen])
			{
				chosen = choice;
			}
		if (chosen == -1 || chosen == finish)
			break;
		used[chosen] = true;
		forn(j, edges[chosen].size())
		{
			int u = edges[chosen][j].fi;
			int nnew = d[chosen] + edges[chosen][j].se;
			if (d[u] > nnew)
			{
				d[u] = nnew;
				cnt[u] = cnt[chosen];
			}
			else if (d[u] == nnew)
			{
				cnt[u] += cnt[chosen];
			}
		}
	}
	d_finish = d[finish];
	cnt_finish = cnt[finish];
}

int get()
{
	string s;
	cin >> s;
	if (mymap.find(s) == mymap.end())
	{
		mymap[s] = n;
		edges[n].clear();
		n++;
		return n - 1;
	}
	else return mymap[s];
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int tests;
	scanf("%d", &tests);
	forn(test, tests)
	{
		mymap.clear();
		n = 0;
		int m;
		scanf("%d", &m);
		int s = get();
		forn(j, m)
		{
			list[j].fr = get();
			list[j].to = get();
			//...edges clear!
			scanf("%d", &list[j].w);
			edges[list[j].fr].pb(mp(list[j].to, list[j].w));
		}
		forn(dest, n)
		{
			paths(s, dest, d_opt[dest], cnt_opt[dest]);
		}
		printf("Case #%d: ", test + 1);
		forn(edge, m)
		{
			int d_fr;
			i64 cnt_fr;
			paths(s, list[edge].fr, d_fr, cnt_fr);
			//if (d_fr == inf)
			//	continue;
			double answer = 0.0;
			forn(final, n) if (d_opt[final] != inf)
			{
				int d_final;
				i64 cnt_final;
				paths(list[edge].to, final, d_final, cnt_final);
				if (d_final != inf && d_fr + list[edge].w + d_final == d_opt[final])
				{
					answer += (1.0 / (double)(n - 1)) * (double)cnt_fr * (double)cnt_final / (double)cnt_opt[final];
				}
			}
			if (d_fr == inf)
				answer = 0.0;
			printf("%.10lf ", answer);
		}
		printf("\n");
		
	}
	return 0;
}