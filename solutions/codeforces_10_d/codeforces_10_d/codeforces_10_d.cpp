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

const int maxn = 505;

int move[maxn][maxn];
int a[maxn];
int b[maxn];
int dp[maxn][maxn];
int n, m;

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	fore(j, 1, n)
		scanf("%d", &a[j]);
	scanf("%d", &m);
	fore(j, 1, m)
		scanf("%d", &b[j]);
	fore(last, 0, n)
		fore(fr, 1, m)
		{
			if (dp[last][fr + 1] < dp[last][fr])
			{
				dp[last][fr + 1] = dp[last][fr];
				move[last][fr + 1] = -1;
			}
			fore(chosen, last + 1, n)
				if (a[chosen] == b[fr] && (a[chosen] > a[last] || last == 0))
				{
					if (dp[chosen][fr + 1] < dp[last][fr] + 1)
					{
						dp[chosen][fr + 1] = dp[last][fr] + 1;
						move[chosen][fr + 1] = last;
					}
				}
		}
	int besti = 0;
	fore(i, 1, n)
		if (dp[i][m + 1] > dp[besti][m + 1])
		{
			besti = i;
		}
	printf("%d\n", dp[besti][m + 1]);
	int curi = besti;
	int curj = m + 1;
	vi answer;
	while(dp[curi][curj] != 0)
	{
		if (move[curi][curj] != -1)
		{
			answer.pb(a[curi]);
			curi = move[curi][curj];
		}
		curj--;
	}
	for (int j = answer.size() - 1; j >= 0; j--)
		printf("%d ", answer[j]);
	return 0;
}