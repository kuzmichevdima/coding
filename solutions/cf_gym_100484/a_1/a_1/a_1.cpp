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

const int maxn = 1e4 + 5;
const int maxk = 105;

bool dp[maxn][maxk];
int a[maxn];

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	fore(j, 1, n)
	{
		scanf("%d", &a[j]);
		if (a[j] >= 0)
			a[j] = a[j] % k;
		else a[j] = k - (-a[j]) % k;
	}
	dp[0][0] = true;
	fore(step, 0, n - 1) 
		fore(cur, 0, k - 1) if (dp[step][cur])
		{
			dp[step + 1][(cur + a[step + 1]) % k] = true;
			dp[step + 1][(cur - a[step + 1] + k) % k] = true;
		}
	if (dp[n][0])
		printf("Divisible");
	else printf("Not divisible");

	return 0;
}