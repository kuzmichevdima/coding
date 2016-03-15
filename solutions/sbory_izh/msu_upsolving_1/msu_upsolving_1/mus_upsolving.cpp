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

const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};

const int maxn = 1005;

//bool mark[maxn][maxn];
char a[maxn][maxn];
vector <pii> list;
int n, m, rot, multx, multy, done;
bool fail;

inline pii make_move(pii p, int move)
{
	return mp(p.first + dx[move], p.second + dy[move]);
}

inline bool correct(pii p)
{
	return p.first >= 0 && p.first < n && p.second >= 0 && p.second < m;
}

/*inline bool check_empty(pii p)
{
	return (!correct(p)) || (a[p.first][p.second] == '.');
}*/

pair <pii, pii> step[maxn];

void dfs(pii cur1, pii cur2)
{
	/*if (rot == 0 && multx == -1 && multy == 1)
	{
		printf("dfs (%d %d) (%d %d)\n", cur1.first, cur1.second, cur2.first, cur2.second);
	}*/
	//mark[cur1.first][cur1.second] = true;
	
	if (fail)
		return;
	a[cur1.first][cur1.second] = 'A';
	a[cur2.first][cur2.second] = 'B';
	step[done] = mp(cur1, cur2);
	done++;

	forn(move, 4)
	{
		pii next1 = make_move(cur1, move);
		//pii next2 = make_move(cur2, (move + rot) % 4);
		pii next2 = mp(cur2.first + multx * dx[(move + rot) % 4], cur2.second + multy * dy[(move + rot) % 4]);
		if (correct(next1) && a[next1.first][next1.second] == 'X' &&
			correct(next2) && a[next2.first][next2.second] == 'X')
				dfs(next1, next2);
	}

	
}

bool check_fail()
{
	forn(j, list.size() / 2)
	{
		pii cur1 = step[j].fi;
		pii cur2 = step[j].se;
		forn(move, 4)
		{
			pii next1 = make_move(cur1, move);
			pii next2 = mp(cur2.first + multx * dx[(move + rot) % 4], cur2.second + multy * dy[(move + rot) % 4]);
			char c1 = a[next1.first][next1.second];
			bool empty1 = (!correct(next1)) || (c1 == 'B') || (c1 == '.');
			char c2 = a[next2.first][next2.second];
			bool empty2 = (!correct(next2)) || (c2 == 'A') || (c2 == '.');
			if (empty1 != empty2)
			{
				return true;
				//printf("empty fail!\n");
			}
			if (empty1)
				continue;
			bool same_color1 = (a[next1.first][next1.second] == 'A');
			bool same_color2 = (a[next2.first][next2.second] == 'B');
			if (same_color1 != same_color2)
			{
				return true;
				//printf("same_color fail!\n");
			}
			if (same_color1)
				continue;
			assert(a[next1.first][next1.second] == 'X');
			assert(a[next2.first][next2.second] == 'X');
		}
	}
	return false;
}

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d\n", &n, &m);
	forn(i, n)
	{
		forn(j, m)
		{
			scanf("%c", &a[i][j]);
			if (a[i][j] == 'X')
				list.pb(mp(i, j));
		}
		scanf("\n");
	}
	if (list.size() % 2 == 1)
	{
		printf("NO");
		exit(0);
	}
	fore(opp, 1, list.size() - 1)
		for (rot = 0; rot <= 2; rot++)
			for (multx = 1; multx >= -1; multx -= 2)
				for (multy = 1; multy >= -1; multy -= 2)
				{
					
					forn(j, list.size())
					{
						a[list[j].fi][list[j].se] = 'X';
						//mark[list[j].fi][list[j].se] = false;
					}
					fail = false;
					/*if (list[opp] == mp(3, 4) && rot == 0 && multx == -1 && multy == 1)
					{
						printf("here!\n");
					}*/
					done = 0;
					dfs(list[0], list[opp]);
					/*if (list[opp] == mp(3, 4) && rot == 0 && multx == -1 && multy == 1)
					{
						printf("here!\n");
					}*/
					if (done != list.size() / 2)
						continue;
					bool fail = check_fail();
					if (!fail)
					{
						printf("YES\n");
						forn(i, n)
						{
							forn(j, m)
								printf("%c", a[i][j]);
							printf("\n");
						}
						exit(0);
					}
				}
	printf("NO\n");
	return 0;
}