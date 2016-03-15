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

const int maxn = 1005;
const int inf = 1e9;

int a[maxn][maxn];
int d[maxn];
int n;
bool done[maxn];

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	forn(i, n)
		forn(j, n)
		{
			scanf("%d", &a[i][j]);
		}
	forn(j, n)
	{
		scanf("%d", &a[n][j]);
		a[j][n] = a[n][j];
	}
	
	forn(i, n + 1)
		d[i] = inf;
	int answer = 0;
	d[0] = 0;
	forn(i, n + 1)
	{
		int chosen = -1;
		forn(j, n + 1) if (!done[j])
		{
			if (chosen == -1 || d[chosen] > d[j])
				chosen = j;
		}
		done[chosen] = true;
		answer += d[chosen];
		forn(j, n + 1)
			d[j] = min(d[j], a[chosen][j]);
	}
	printf("%d", answer);
	return 0;
}